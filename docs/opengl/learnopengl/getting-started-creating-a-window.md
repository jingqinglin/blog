本节的内容是教我们如何配置 OpenGL。**OpenGL 自身并不包含任何执行窗口任务或者处理用户输入的函数**，但有许多库提供给我们一个窗口和上下文用来渲染，最流行的几个库有 GLUT，SDL，SFML 和 GLFW，教程里使用 GLFW。

## GLFW

GLFW 是一个专门针对 OpenGL 的 C 语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户**创建 OpenGL 上下文**，**定义窗口参数**以及**处理用户输入**，这正是我们需要的。

教程里从编译 GLFW 开始写起，此处为了方便直接下载预编译版本。在 GLFW 的[下载页](https://www.glfw.org/download.html)中，下载 Windows pre-compiled binaries 下 32 位的版本。我们其中的会用到 include 和 lib。

![](_images/learnopengl-getting-started-1.png ':class=image-40')

## 链接

教程使用 Visual Studio，由于 VS 过于庞大，此处选择 CodeLite + MinGW 作为 C 语言环境。

我们需要把 GLFW 库链接进工程。这可以通过在链接器的设置里指定我们要使用 glfw3.lib 来完成，但是由于我们将第三方库放在另外的目录中，我们的工程还不知道在哪寻找这个文件。于是我们首先需要将我们放第三方库的目录添加进设置。

将 GLFW 的 include 文件夹和 lib 文件夹（我使用 32 位的 MinGW）加进项目的 include 和 libraries 路径中：

![](_images/learnopengl-getting-started-2.png ':class=image-70')
![](_images/learnopengl-getting-started-3.png ':class=image-70')

要链接一个库我们必须告诉链接器它的文件名，库名字是 glfw3.lib。在 GLFW 的[说明文档](https://www.glfw.org/docs/latest/build_guide.html#build_link_win32)中提到：When using MinGW to link an application with the static version of GLFW, you must also explicitly link with `gdi32`。因此我们还要把 gdi32.dll 加入链接器。

![](_images/learnopengl-getting-started-4.png ':class=image-70')

## GLAD

我们仍然还有一件事要做。因为 OpenGL 只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于 OpenGL 驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。所以任务就落在了开发者身上，开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。取得地址的方法因平台而异，在 Windows 上会是类似这样：

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