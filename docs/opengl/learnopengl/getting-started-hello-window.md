本节会用 OpenGL 渲染一个窗口。

首先创建 `main` 函数。

```c
int main()
{
    // 初始化 GLFW
    glfwInit();
    // 配置 GLFW
    // 主版本号和次版本号都设为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return 0;
}
```

接下来我们创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被 GLFW 的其他函数频繁地用到。

```c
// 窗口的宽、高、标题名称
GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
// 将窗口的上下文设置为当前线程的主上下文
glfwMakeContextCurrent(window);
```

### GLAD

GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何 OpenGL 的函数之前我们需要初始化 GLAD。

```c
// 给 GLAD 传入用来加载系统相关的 OpenGL 函数指针地址的函数 glfwGetProcAddress
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
}
```

### 视口

在我们开始渲染之前还有一件重要的事情要做，我们必须告诉 OpenGL 渲染窗口的尺寸大小，即视口（Viewport，<font size="2" color="#c0c0c0">就是窗口中用来显示图形的一块矩形区域，它可以和窗口等大，也可以比窗口大或者小</font>），这样 OpenGL 才只能知道怎样根据窗口大小显示数据和坐标。我们可以通过调用 glViewport 函数来设置窗口的维度。

```c
// 前两个参数控制视口左下角的位置，第三个和第四个参数控制视口的宽度和高度
glViewport(0, 0, 800, 600);
```

然而，当用户改变窗口的大小的时候，视口也应该被调整。我们可以对窗口注册一个回调函数（Callback Function），它会在每次窗口大小被调整的时候被调用。回调函数如下：

```c
// 这个帧缓冲大小函数需要一个 GLFWwindow 作为它的第一个参数，以及两个整数表示窗口的新维度
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
```

我们还需要注册这个回调函数，告诉 GLFW 我们希望每当窗口调整大小的时候调用这个函数：

```c
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

当窗口被第一次显示的时候 `framebuffer_size_callback` 也会被调用。*我们还可以将我们的函数注册到其它很多的回调函数中。比如说，我们可以创建一个回调函数来处理手柄输入变化，处理错误消息等。我们会在创建窗口之后，渲染循环初始化之前注册这些回调函数。*

### 准备好你的引擎

我们不希望只绘制一个图像之后应用程序就立即退出并关闭窗口。我们希望程序在我们主动关闭它之前不断绘制图像并能够接受用户输入。因此，需要在程序中添加一个 while 循环，我们可以把它称之为**渲染循环**（Render Loop），它能在我们让 GLFW 退出前一直保持运行。下面几行的代码就实现了一个简单的渲染循环：

```c
// 循环开始前检查 GLFW 是否被要求退出
while(!glfwWindowShouldClose(window))
{
    glfwSwapBuffers(window);
    glfwPollEvents();    
}
```

- `glfwPollEvents` 函数检查有没有触发什么事件（比如键盘输入、鼠标移动等），更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
- `glfwSwapBuffers` 交换在迭代期间用于渲染的颜色缓冲区（它是一个储存着 GLFW 窗口每一个像素颜色值的大缓冲），并将其显示为屏幕输出。

> [!NOTE|label:双缓冲（Double Buffer）]
> 应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的，这会导致渲染的结果很不真实。为了规避这些问题，我们应用双缓冲渲染窗口应用程序。**前**缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在**后**缓冲上绘制。当所有的渲染指令执行完毕后，我们**交换**（Swap）前缓冲和后缓冲，这样图像就立即呈显出来，之前提到的不真实感就消除了。

### 最后一件事

当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源。我们可以在 `main` 函数的最后调用 `glfwTerminate` 函数来完成。编译并运行，可以看到如下窗口：

![](_images/learnopengl-getting-started-7.png ':class=image-45')

程序的完整源代码可以在[这里](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/1.1.hello_window/hello_window.cpp)找到。

### 输入

我们希望能在 GLFW 中实现一些输入控制，这可以通过使用 GLFW 的几个输入函数来完成。我们将会使用 GLFW 的 `glfwGetKey` 函数，它需要一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下。

```c
void processInput(GLFWwindow *window)
{
    // 检查用户是否按下了 escape 键，若没有按下返回 GLFW_RELEASE
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
```

接着在渲染循环中调用 `processInput`：

```c
while (!glfwWindowShouldClose(window))
{
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

### 渲染

我们要把所有的渲染（Rendering）操作放到渲染循环中，因为我们想让这些渲染指令在每次渲染循环迭代的时候都能被执行。代码将会是这样的：

```c
// 渲染循环
while(!glfwWindowShouldClose(window))
{
    // 输入
    processInput(window);

    // 渲染指令
    ...

    // 检查并调用事件，交换缓冲
    glfwPollEvents();
    glfwSwapBuffers(window);
}
```

我们用以下代码测试渲染指令：

```c
// 设置清空屏幕所用的颜色
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 清除颜色缓冲，之后整个颜色缓冲都会被填充为 glClearColor 里所设置的颜色
glClear(GL_COLOR_BUFFER_BIT);
```

> [!TIP]
> `glClearColor` 函数是一个**状态设置**函数，而 `glClear` 函数则是一个**状态使用**的函数，它使用了当前的状态来获取应该清除成什么颜色