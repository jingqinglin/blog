## OpenGL

OpenGL 一般被认为是一个 API，包含了一系列可以操作图形、图像的函数。然而，OpenGL 本身并不是一个 API，它仅仅是一个由 Khronos 组织制定并维护的规范。OpenGL 规范严格规定了每个函数该如何执行，以及它们的输出值。至于内部具体每个函数是如何实现的，将由 OpenGL 库的开发者（通常是显卡的生产商）自行决定。

### 核心模式与立即渲染模式

- 立即渲染模式（Immediate mode，也就是固定渲染管线）：这个模式下绘制图形很方便。OpenGL 的大多数功能都被库隐藏起来，开发者很少能控制 OpenGL 如何进行计算的自由。
- 核心模式（Core-profile）：开发者迫切希望能有更多的灵活性。随着时间推移，规范越来越灵活，开发者对绘图细节有了更多的掌控。当使用 OpenGL 的核心模式时，OpenGL 迫使我们使用现代的函数。现代函数的优势是更高的灵活性和效率，然而也更难于学习。立即渲染模式从 OpenGL 实际运作中抽象掉了很多细节，因此它在易于学习的同时，也很难让人去把握 OpenGL 具体是如何运作的。现代函数要求使用者真正理解 OpenGL 和图形编程，它有一些难度，然而提供了更多的灵活性，更高的效率，更重要的是可以更深入的理解图形编程。

### 状态机

OpenGL 自身是一个巨大的状态机（State Machine）：一系列的变量描述 OpenGL 此刻应当如何运行。OpenGL 的状态通常被称为 OpenGL **上下文**（Context）。我们通常使用如下途径去更改 OpenGL 状态：设置选项，操作缓冲。最后，我们使用当前 OpenGL 上下文来渲染。

假设当我们想告诉 OpenGL 去画线段而不是三角形的时候，我们通过改变一些上下文变量来改变 OpenGL 状态，从而告诉 OpenGL 如何去绘图。

当使用 OpenGL 的时候，我们会遇到一些状态设置函数（State-changing Function），这类函数将会改变上下文。以及状态使用函数（State-using Function），这类函数会根据当前 OpenGL 的状态执行一些操作。只要你记住 OpenGL 本质上是个大状态机，就能更容易理解它的大部分特性。

### 对象

在 OpenGL 中一个对象是指一些选项的集合，它代表 OpenGL 状态的一个子集。比如，我们可以用一个对象来代表绘图窗口的设置，之后我们就可以设置它的大小、支持的颜色位数等等。可以把对象看做一个 C 风格的结构体（Struct）：

```c
struct object_name {
    float  option1;
    int    option2;
    char[] name;
};
```

## 创建窗口

本节的内容是教我们如何配置 OpenGL。**OpenGL 自身并不包含任何执行窗口任务或者处理用户输入的函数**，但有许多库提供给我们一个窗口和上下文用来渲染，最流行的几个库有 GLUT，SDL，SFML 和 GLFW，教程里使用 GLFW。

### GLFW

GLFW 是一个专门针对 OpenGL 的 C 语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户**创建 OpenGL 上下文**，**定义窗口参数**以及**处理用户输入**，这正是我们需要的。

教程里从编译 GLFW 开始写起，此处为了方便直接下载预编译版本。在 GLFW 的[下载页](https://www.glfw.org/download.html)中，下载 Windows pre-compiled binaries 下 32 位的版本。我们其中的会用到 include 和 lib。

![](_images/learnopengl-getting-started-1.png ':class=image-40')

### 链接

教程使用 Visual Studio，由于 VS 过于庞大，此处选择 CodeLite + MinGW 作为 C 语言环境。

我们需要把 GLFW 库链接进工程。这可以通过在链接器的设置里指定我们要使用 glfw3.lib 来完成，但是由于我们将第三方库放在另外的目录中，我们的工程还不知道在哪寻找这个文件。于是我们首先需要将我们放第三方库的目录添加进设置。

将 GLFW 的 include 文件夹和 lib 文件夹（我使用 32 位的 MinGW）加进项目的 include 和 libraries 路径中：

![](_images/learnopengl-getting-started-2.png ':class=image-70')
![](_images/learnopengl-getting-started-3.png ':class=image-70')

要链接一个库我们必须告诉链接器它的文件名，库名字是 glfw3.lib。在 GLFW 的[说明文档](https://www.glfw.org/docs/latest/build_guide.html#build_link_win32)中提到：When using MinGW to link an application with the static version of GLFW, you must also explicitly link with `gdi32`。因此我们还要把 gdi32.dll 加入链接器。

![](_images/learnopengl-getting-started-4.png ':class=image-70')

### GLAD

到这里还没有结束，我们仍然还有一件事要做。因为 OpenGL 只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于 OpenGL 驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。所以任务就落在了开发者身上，开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。取得地址的方法因平台而异，在 Windows 上会是类似这样：

可以看到代码非常复杂，而且很繁琐，我们需要对每个可能使用的函数都要重复这个过程。幸运的是，有些库能简化此过程，其中 GLAD 是目前最新，也是最流行的库。

GLAD 使用了一个在线服务。打开 GLAD 的在线服务，将语言（Language）设置为 C/C++，在 API 选项中，选择 3.3 以上的 OpenGL（gl）版本。之后将模式（Profile）设置为 Core，并且保证生成加载器（Generate a loader）的选项是选中的。现在可以先忽略拓展（Extensions）中的内容。都选择完之后，点击生成（Generate）按钮来生成库文件。

![](_images/learnopengl-getting-started-5.png ':class=image-70')

GLAD 提供了一个 zip 压缩文件，包含两个头文件目录，和一个 glad.c 文件。将头文件目录也添加到项目的 include 路径中，**并添加 glad.c 文件到你的工程中**。

![](_images/learnopengl-getting-started-6.png ':class=image-20')

接着，我们将头文件添加到项目里，再编译，应该不会出现错误了。

```c
// 头文件顺序不能变，glad.h 要放在顶部
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```

## 你好，窗口