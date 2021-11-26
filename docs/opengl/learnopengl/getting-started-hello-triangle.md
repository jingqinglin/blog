> [!COMMENT]
> 在学习此节之前，建议将这三个单词先记下来：
> - 顶点数组对象：Vertex Array Object，VAO
> - 顶点缓冲对象：Vertex Buffer Object，VBO
> - 索引缓冲对象：Element Buffer Object，EBO 或 Index Buffer Object，IBO

OpenGL 中，任何事物都在 3D 空间中，而屏幕和窗口却是 2D 像素数组，这导致 OpenGL 的大部分工作都是关于把 3D 坐标转变为适应你屏幕的 2D 像素。3D 坐标转为 2D 坐标的处理过程是由 OpenGL 的**图形渲染管线**（Graphics Pipeline，也译为管线）管理的。图形渲染管线可以被划分为两个主要部分：第一部分把你的 3D 坐标转换为 2D 坐标，第二部分是把 2D 坐标转变为实际的有颜色的像素。

图形渲染管线可以被划分为几个阶段，每个阶段将会把前一个阶段的输出作为输入。所有这些阶段都是高度专门化的（它们都有一个特定的函数），并且很容易*并行*执行。正是由于并行执行的特性，当今大多数显卡都有成千上万的小处理核心，它们在 GPU 上为每一个阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做**着色器**（Shader）。

下图为图形渲染管线的每个阶段的抽象展示。蓝色部分代表的是我们可以注入自定义的着色器的部分（*有些着色器允许开发者自己配置，这就允许我们用自己写的着色器来替换默认的。这样我们就可以更细致地控制图形渲染管线中的特定部分了*）。

![管线各阶段](_images/learnopengl-getting-started-8.png ':class=resizedImage')

按照上图，我们概括性地解释一下渲染管线的每个部分：

1. 首先，我们以数组的形式传递 3 个 3D 坐标作为图形渲染管线的输入，用来表示一个三角形，这个数组叫做顶点数据（Vertex Data）；顶点数据是一系列顶点的集合。一个**顶点**（Vertex）是一个 3D 坐标的数据的集合。而顶点的数据是用**顶点属性**（Vertex Attribute）表示的，它可以包含任何我们想用的数据，但是简单起见，我们假定每个顶点的顶点属性只由一个 3D 位置和一些颜色值组成。

> [!NOTE]
> 为了让 OpenGL 知道我们的坐标和颜色值构成的到底是什么，OpenGL 需要你去指定这些数据所表示的渲染类型。我们是希望把这些数据渲染成一系列的点？一系列的三角形？还是仅仅是一条长长的线？做出的这些提示叫做**图元**（Primitive），任何一个绘制指令的调用都将把图元传递给 OpenGL。这是其中的几个：`GL_POINTS`、`GL_TRIANGLES`、`GL_LINE_STRIP`。

2. 图形渲染管线的第一个部分是**顶点着色器**（Vertex Shader），它把一个单独的顶点作为输入。顶点着色器主要的目的是把 3D 坐标转为另一种 3D 坐标（后面会解释），同时顶点着色器允许我们对顶点属性进行一些基本处理。
3. **图元装配**（Primitive Assembly）阶段将顶点着色器输出的所有顶点作为输入（如果是 `GL_POINTS`，那么就是一个顶点），并所有的点*装配*成指定图元的形状；本节例子中是一个三角形。
4. 图元装配阶段的输出会传递给**几何着色器**（Geometry Shader）。几何着色器把图元形式的一系列顶点的集合作为输入，它可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状。例子中，它生成了另一个三角形。
5. 几何着色器的输出会被传入**光栅化阶段**（Rasterization Stage），这里它会把图元映射为最终屏幕上相应的像素，生成供片段着色器（Fragment Shader）使用的片段（Fragment，*OpenGL 中的一个片段是 OpenGL 渲染一个像素所需的所有数据*）。在片段着色器运行之前会执行**裁切**（Clipping）。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。
6. **片段着色器**的主要目的是计算一个像素的最终颜色。通常，片段着色器包含 3D 场景的数据（比如光照、阴影、光的颜色等等），这些数据可以被用来计算最终像素的颜色。
7. 在所有对应颜色值确定以后，最终的对象将会被传到最后一个阶段，我们叫做 **Alpha 测试**和**混合**（Blending）阶段。这个阶段检测片段的对应的深度（和模板）值（后面会讲），用它们来判断这个像素是其它物体的前面还是后面，决定是否应该丢弃。这个阶段也会检查 alpha 值（alpha 值定义了一个物体的透明度）并对物体进行混合（Blend）。所以，即使在片段着色器中计算出来了一个像素输出的颜色，在渲染多个三角形的时候最后的像素颜色也可能完全不同。

对于大多数场合，我们只需要配置顶点和片段着色器就行了。几何着色器是可选的，通常使用它默认的着色器就行了。

## 顶点输入

> 关键词：标准化设备坐标、顶点缓冲对象

开始绘制图形之前，我们必须先给 OpenGL 输入一些顶点数据。在 OpenGL 中指定的所有坐标都是 3D 坐标（x、y 和 z），且仅当 3D 坐标在 3 个轴（x、y 和 z）上都为 - 1.0 到 1.0 的范围内时才处理它。所有**标准化设备坐标**（Normalized Device Coordinates）范围内的坐标才会最终呈现在屏幕上。

由于我们希望渲染一个三角形，所以要指定三个顶点，每个顶点都有一个 3D 位置。我们会将它们以标准化设备坐标的形式定义为一个 `float` 数组。

```cpp
float vertices[] = {
    // z 坐标设置为 0.0，这样三角形每一点的深度都是一样的，从而使它看上去像是 2D 的
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
```

> [!NOTE|label:标准化设备坐标（Normalized Device Coordinates）]
> 一旦顶点坐标在顶点着色器中处理过，它们就应该是**标准化设备坐标**了，标准化设备坐标是一个 x、y 和 z 值在 - 1.0 到 1.0 的一小段空间。任何落在范围外的坐标都会被丢弃/裁剪。下面会看到我们定义的在标准化设备坐标中的三角形（忽略 z 轴）：
>
> ![](_images/learnopengl-getting-started-9.png ':class=resizedImage')
>
> 标准化设备坐标接着会变换为**屏幕空间坐标**（Screen-space Coordinates），这是使用你通过 `glViewport` 函数提供的数据，进行**视口变换**（Viewport Transform）完成的。所得的屏幕空间坐标又会被变换为片段输入到片段着色器中。

定义好顶点数据以后，我们会把它作为输入发送给顶点着色器。它会在 GPU 上创建**内存**<sup>[1]</sup>用于储存我们的顶点数据，还要配置 OpenGL 如何解释这些内存，并且指定其如何发送给显卡。顶点着色器接着会处理我们在内存中指定数量的顶点。

<font size="2">注<sup>[1]</sup>：我们通过**顶点缓冲对象**（Vertex Buffer Objects, VBO）管理这个内存，它会在 GPU 内存（通常被称为显存）中储存大量顶点。使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上。</font>

顶点缓冲对象是我们在 OpenGL 教程中第一个出现的 OpenGL 对象。就像 OpenGL 中的其它对象一样，这个缓冲有一个独一无二的 ID，所以我们可以使用 `glGenBuffers` 函数和一个缓冲对象 ID（`unsigned int VBO`）生成一个 VBO 对象：

```cpp
unsigned int VBO;
// 第一个参数指定缓冲对象的数量，第二个参数存储缓冲对象 ID
glGenBuffers(1, &VBO);
```

OpenGL 有很多缓冲对象类型，顶点缓冲对象的缓冲类型是 `GL_ARRAY_BUFFER`。OpenGL 允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。我们可以使用 `glBindBuffer` 函数把新创建的缓冲绑定到 `GL_ARRAY_BUFFER` 目标上。此后使用的任何（在 `GL_ARRAY_BUFFER` 目标上的）缓冲调用都会用来配置当前绑定的缓冲（`VBO`）。

```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);
```
然后我们可以调用 `glBufferData` 函数，它会把之前定义的顶点数据复制到缓冲的内存中：

```cpp
// 第二个参数指定传输数据的大小（以字节为单位），第三个参数是发送的数据
// 第四个参数指定了显卡如何管理给定的数据。GL_STATIC_DRAW ：数据不会或几乎不会改变；
// GL_DYNAMIC_DRAW：数据会被改变很多；GL_STREAM_DRAW ：数据每次绘制时都会改变。
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```
三角形的位置数据不会改变，每次渲染调用时都保持原样，所以它的使用类型最好是 `GL_STATIC_DRAW`。现在我们已经把顶点数据储存在显卡的内存中，用 `VBO` 这个顶点缓冲对象管理。下面我们会创建一个顶点和片段着色器来真正处理这些数据。

## 顶点着色器

现代 OpenGL 需要我们至少设置一个顶点和一个片段着色器。

我们需要做的第一件事是用着色器语言 GLSL (OpenGL Shading Language）编写顶点着色器，然后编译这个着色器，这样我们就可以在程序中使用它了。下面是一个非常基础的 GLSL 顶点着色器的代码：

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

GLSL 看起来很像 C 语言。我们使用 `in` 关键字声明顶点着色器中的所有输入顶点属性（Input Vertex Attribute）（我们这里只用到了一个顶点属性，即 `position` 属性）。由于每个顶点都有一个 3D 坐标，我们就创建一个 `vec3` 输入变量 `aPos`。我们通过 `layout (location = 0)` 设定了输入变量的位置值（Location），即输入数据的位置 0 代表顶点的 `position` 属性。

> [!TIP]
> 我们也可以定义多个顶点属性，如位置、颜色、纹理坐标，如下代码：
>
> ```glsl
> layout (location = 0) in vec3 aPos;
> layout (location = 1) in vec4 aCol;
> layout (location = 2) in vec2 aCoord;
> ```

为了设置顶点着色器的输出，我们必须把位置数据赋值给预定义的 `gl_Position` 变量，它是 `vec4` 类型的。由于我们的输入是一个 3 分量的向量，我们必须把它转换为 4 分量的。（后面会解释为什么把 `w` 分量设置为 `1.0f`）。

> [!NOTE|label:向量（vector）]
> 在 GLSL 中一个向量有最多 4 个分量，每个分量值都代表空间中的一个坐标，它们可以通过 `vec.x`、`vec.y`、`vec.z` 和 `vec.w` 来获取。注意 `vec.w` 分量不是用作表达空间中的位置的，而是用在所谓透视除法（Perspective Division）上。

当前这个顶点着色器可能是我们能想到的最简单的顶点着色器了，因为我们对输入数据什么都没有处理就把它传到着色器的输出了。但在真实的程序里输入数据通常都不是标准化设备坐标，所以我们必须先把它们转换至 OpenGL 的可视区域内。


## 编译顶点着色器

我们已经写了一个顶点着色器代码，并暂时将其存储在 C 言语代码文件顶部的字符串常量中：

```cpp
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
```

但是为了能够让 OpenGL 使用它，我们必须在运行时动态编译它。

```cpp
// 创建一个着色器对象来存储顶点着色器，还是用 ID 来引用
unsigned int vertexShader;
// 把着色器类型以参数形式提供给 glCreateShader 以创建着色器
vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 把着色器源码附加到着色器对象上，然后编译它
// 第二参数指定了传递的源码字符串数量，第三个参数是顶点着色器源码
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

关于如何检查编译时错误：https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/#_4

## 片段着色器

片段着色器所做的是计算像素最后的颜色输出。

片段着色器只需要一个输出变量，这个变量是一个 4 分量向量（第四个变量是 alpha 值），它表示的是最终的输出颜色，代码如下：

```glsl
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
```

编译片段着色器的过程与顶点着色器类似：

```cpp
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

两个着色器都编译了，剩下的事情是把两个着色器对象链接到一个用来渲染的**着色器程序**（Shader Program）中。

### 着色器程序

> 区分：着色器对象、着色器程序对象

**着色器程序对象**（Shader Program Object）是多个着色器合并之后的最终链接版本。如果要使用刚才编译的着色器我们必须把它们**链接**（Link）为一个着色器程序对象：

```cpp
unsigned int shaderProgram;
// 创建一个着色器程序，并返回程序对象 ID 引用
shaderProgram = glCreateProgram();
// 把编译后的着色器附加到程序对象上，并链接它们
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
// 把着色器对象链接到程序对象以后，删除着色器对象
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

然后在渲染循环中渲染对象的时候用 `glUseProgram(shaderProgram)` 激活这个着色器程序。

> [!WARNING|label:进度|icon:fas fa-percentage]
> 我们已经把输入顶点数据发送给了 GPU，并指示了 GPU 如何在顶点和片段着色器中处理它。但 OpenGL 还不知道它该如何解释内存中的顶点数据，以及它该如何将顶点数据链接到顶点着色器的属性上。我们需要告诉 OpenGL 怎么做。

## 链接顶点属性

我们必须手动指定输入数据的哪一个部分对应顶点着色器的哪一个顶点属性。所以，在渲染前我们要指定 OpenGL 该如何解释顶点数据。

我们的顶点缓冲数据会被解析为下面这样子：

![](_images/learnopengl-getting-started-10.png ':class=resizedImage')

```cpp
// 函数告诉 OpenGL 该如何解析顶点数据
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
// 以顶点属性位置值作为参数，启用顶点属性
glEnableVertexAttribArray(0);
```

`glVertexAttribPointer` 函数的参数非常多：
- 第一个参数指定我们要配置的顶点属性。我们在顶点着色器中使用 `layout (location = 0)` 定义了顶点属性 `position` 的位置值（Location），它可以把顶点属性的位置值设置为 `0`。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入 `0`。
- 第二个参数指定顶点属性的大小。顶点属性是一个 `vec3`，它由 3 个值组成，所以大小是 3。
- 第三个参数指定数据的类型，这里是 `GL_FLOAT`（GLSL 中 `vec*` 都是由浮点数值组成的）。
- 下个参数定义我们是否希望数据被标准化。如果我们设置为 `GL_TRUE`，所有数据都会被映射到 0 到 1 之间。我们把它设置为 `GL_FALSE`。
- 第五个参数叫做步长，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在 3 个 float 之后，我们把步长设置为 `3 * sizeof (float)`。我们也可以设置为 0 来让 OpenGL 决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔。
- 最后一个参数的类型是 `void*`，它表示位置数据在缓冲中起始位置的偏移量。由于位置数据在数组的开头，所以这里是 0。我们会在后面详细解释这个参数。

自此，所有东西都已经设置好了。在 OpenGL 中绘制一个物体，代码会像是这样：

```cpp
// 0. 复制顶点数组到缓冲中供 OpenGL 使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 1. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// 2. 当我们渲染一个物体时要使用着色器程序
glUseProgram(shaderProgram);
// 3. 绘制物体
someOpenGLFunctionThatDrawsOurTriangle();
```

每当我们绘制一个物体的时候都必须重复这一过程。但是如果有超过 5 个顶点属性，上百个不同物体，那么绑定缓冲对象、为每个物体配置所有顶点属性就变得很麻烦。

> [!TIP]
> 对 `glVertexAttribPointer` 的调用将变量 VBO 注册为顶点属性的绑定顶点缓冲对象，因此调用之后我们可以安全地取消绑定。即在 `glVertexAttribPointer` 函数后加 `glBindBuffer(GL_ARRAY_BUFFER, 0)`

### 顶点数组对象

!> 比较难理解

**顶点数组对象**（Vertex Array Object, VAO）可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个 VAO 中。这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的 VAO 就行了。这使在不同顶点数据和属性配置之间切换变得非常简单，只需要绑定不同的 VAO 就行了。

![](_images/learnopengl-getting-started-11.png ':class=resizedImage')

一个顶点数组对象会储存以下这些内容：
- `glEnableVertexAttribArray` 和 `glDisableVertexAttribArray` 的调用
- 通过 `glVertexAttribPointer` 设置的顶点属性配置
- 通过 `glVertexAttribPointer` 调用与顶点属性关联的顶点缓冲对象


创建一个 VAO：

```cpp
unsigned int VAO;
glGenVertexArrays(1, &VAO);
```

要想使用 VAO，需要使用 `glBindVertexArray` 绑定 VAO。接着我们应该绑定/配置相应的 VBO 和属性指针...（这个过程可以通过看完整代码来熟悉）

```cpp
// ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
// 1. 绑定 VAO
glBindVertexArray(VAO);
// 2. 把顶点数组复制到缓冲中供 OpenGL 使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
// 4. 绘制物体
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();
```

VAO 存储了顶点属性配置和应使用哪个 VBO。一般当我们打算绘制多个物体时，首先要生成/配置所有的 VAO（和所需的 VBO 及属性指针），然后储存它们供后面使用。当我们打算绘制物体的时候就拿出相应的 VAO，绑定它，绘制完物体后，再解绑 VAO。

### 我们一直期待的三角形

OpenGL 给我们提供了 `glDrawArrays` 函数，它使用当前激活的着色器，之前定义的顶点属性配置，和 VBO 的顶点数据（通过 VAO 间接绑定）来绘制图元。

```cpp
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
// 第二个参数指定了顶点数组的起始索引，最后一个参数指定绘制多少个顶点
glDrawArrays(GL_TRIANGLES, 0, 3);
```

编译后，是这样的：

![](_images/learnopengl-getting-started-12.png ':class=resizedImage')

完整的程序源码可以在[这里](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.1.hello_triangle/hello_triangle.cpp)找到。

## 索引缓冲对象

假设我们不再绘制一个三角形而是绘制一个矩形。我们可以绘制两个三角形来组成一个矩形。然而一个矩形只有 4 个而不是 6 个顶点，这样就产生 50% 的额外开销。

```cpp
float vertices[] = {
    // 第一个三角形
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, 0.5f, 0.0f,  // 左上角
    // 第二个三角形
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
```

解决方案是只储存不同的顶点，并设定绘制这些顶点的顺序，这样子我们只要储存 4 个顶点就能绘制矩形了。而**索引缓冲对象**的工作方式正是这样的。和顶点缓冲对象一样，EBO 也是一个缓冲，它专门储存索引，OpenGL 调用这些顶点的索引来决定该绘制哪个顶点。我们定义顶点和绘制出矩形所需的索引：

```cpp
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};
```

```cpp
unsigned int EBO;
// 创建索引缓冲对象
glGenBuffers(1, &EBO);
// 传递了 GL_ELEMENT_ARRAY_BUFFER 当作缓冲目标
// 并把 EBO 绑定到 GL_ELEMENT_ARRAY_BUFFER 目标上
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
// 把索引复制到缓冲里
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

要注意的是，我们传递了 `GL_ELEMENT_ARRAY_BUFFER` 当作缓冲目标。最后一件要做的事是用 `glDrawElements` 来替换 `glDrawArrays` 函数，来指明我们从索引缓冲渲染：

```cpp
// 第一个参数指定绘制模式，第二个参数打算绘制顶点的个数
// 第三个参数是索引的类型，最后一个参数可以指定 EBO 中的偏移量
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

`glDrawElements` 从当前绑定到 `GL_ELEMENT_ARRAY_BUFFER` 目标的 EBO 中获取索引。这意味着我们必须在每次要用索引渲染一个物体时绑定相应的 EBO，这还是有点麻烦。不过顶点数组对象（VAO）同样可以保存索引缓冲对象的绑定状态。VAO 绑定时正在绑定的索引缓冲对象会被保存为 VAO 的元素缓冲对象。绑定 VAO 的同时也会自动绑定 EBO。

![](_images/learnopengl-getting-started-13.png ':class=resizedImage')

最后的初始化和绘制代码现在看起来像这样：

```cpp
// ..:: 初始化代码 :: ..
// 1. 绑定顶点数组对象
glBindVertexArray(VAO);
// 2. 把我们的顶点数组复制到一个顶点缓冲中，供 OpenGL 使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 复制我们的索引数组到一个索引缓冲中，供 OpenGL 使用
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
// 4. 设定顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)
glBindVertexArray(0);
```

源码在[这里](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp)。

> [!TIP]
> 当 VAO 激活时不要解绑 EBO

## 练习

值得一做的练习：

1. 添加更多顶点到数据中，使用 `glDrawArrays`，尝试绘制两个彼此相连的三角形：[参考解答](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.3.hello_triangle_exercise1/hello_triangle_exercise1.cpp)
2. 创建相同的两个三角形，但对它们的数据使用不同的 VAO 和 VBO：[参考解答](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.4.hello_triangle_exercise2/hello_triangle_exercise2.cpp)
3. 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色：[参考解答](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.5.hello_triangle_exercise3/hello_triangle_exercise3.cpp)