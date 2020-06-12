在 [Hello Triangle](opengl/learnopengl/getting-started-hello-triangle.md) 中提到，着色器（Shader）是运行在 GPU 上的小程序。这些小程序为图形渲染管线的某个特定部分而运行。从基本意义上来说，着色器只是一种把输入转化为输出的程序。着色器也是一种非常独立的程序，因为它们之间不能相互通信；它们之间唯一的沟通只有通过输入和输出。

## GLSL

着色器是使用一种叫 GLSL 的类 C 语言写成的。GLSL 是为图形计算量身定制的，它包含一些针对向量和矩阵操作的有用特性。一个典型的着色器有下面的结构：

```glsl
// 声明版本
#version version_number
// 输入和输出变量
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

int main()
{
  // 处理输入并进行一些图形操作
  ...
  // 输出处理过的结果到输出变量
  out_variable_name = weird_stuff_we_processed;
}
```

> [!TIP]
> 顶点着色器的时候，每个输入变量也叫顶点属性，我们能声明的顶点属性是有上限的。OpenGL 确保至少有 16 个包含 4 分量的顶点属性可用。

## 数据类型

GLSL 中包含 C 等其它语言大部分的默认基础数据类型：`int`、`float`、`double`、`uint` 和 `bool`。GLSL 也有两种容器类型，它们会在这个教程中使用很多，分别是向量（Vector）和矩阵（Matrix），矩阵会在之后讨论。

### 向量

GLSL 中的向量是一个可以包含有 1、2、3 或者 4 个分量的容器。它们可以是下面的形式：

| 类型    | 含义                                |
| ------- | ----------------------------------- |
| `vecn`  | 包含 n 个 `float` 分量的默认向量    |
| `bvecn` | 包含 n 个 `bool` 分量的向量         |
| `ivecn` | 包含 n 个 `int` 分量的向量          |
| `uvecn` | 包含 n 个 `unsigned int` 分量的向量 |
| `dvecn` | 包含 n 个 `double` 分量的向量       |

大多数时候我们使用 `vecn`，因为 float 足够满足大多数要求了。

一个向量的分量可以通过 `vec.x` 这种方式获取，这里 `x` 是指这个向量的第一个分量。你可以分别使用 `.x`、`.y`、`.z` 和 `.w` 来获取它们的第 1、2、3、4 个分量。GLSL 也允许你对颜色使用 `rgba`，或是对纹理坐标使用 `stpq` 访问相同的分量。

向量这一数据类型也允许一些有趣而灵活的分量选择方式，叫做**重组**。重组允许这样的语法：

```glsl
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
```

我们也可以把一个向量作为一个参数传给不同的向量构造函数：

```glsl
vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);
```

## 输入与输出

我们希望每个着色器都有输入和输出，这样才能进行数据交流和传递。GLSL 定义了 `in` 和 `out` 关键字专门来实现这个目的。每个着色器使用这两个关键字设定输入和输出，只要一个输出变量与下一个着色器阶段的输入匹配，它就会传递下去。但在顶点和片段着色器中会有点不同。

顶点着色器应该接收的是一种特殊形式的输入，它的输入特殊在，它从顶点数据中直接接收输入。为了定义顶点数据该如何管理，我们使用 `location` 这一元数据指定输入变量，这样我们才可以在 CPU 上配置顶点属性。

另一个例外是片段着色器，它需要一个 `vec4` 颜色输出变量，因为片段着色器需要生成一个最终输出的颜色。如果你在片段着色器没有定义输出颜色，OpenGL 会把你的物体渲染为黑色（或白色）。

所以，如果我们打算从一个着色器向另一个着色器发送数据，我们必须在发送方着色器中声明一个输出，在接收方着色器中声明一个类似的输入。当类型和名字都一样的时候，OpenGL 就会把两个变量链接到一起，它们之间就能发送数据了（这是在链接程序对象时完成的）。修改上一节的代码，让顶点着色器为片段着色器决定颜色：

```glsl
// 顶点着色器
#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为 0

out vec4 vertexColor; // 为片段着色器指定一个颜色输出

void main()
{
    gl_Position = vec4(aPos, 1.0); // 注意我们如何把一个 vec3 作为 vec4 的构造器的参数
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色
}
```

```glsl
// 片段着色器
#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）

void main()
{
    FragColor = vertexColor;
}
```

结果是这样的：

![](_images/learnopengl-getting-started-14.png ':class=image-45')

我们成功地从顶点着色器向片段着色器发送数据。让我们更上一层楼，看看能否从应用程序中直接给片段着色器发送一个颜色！

## Uniform

Uniform 是一种从 CPU 中的应用向 GPU 中的着色器发送数据的方式，但 uniform 和顶点属性有些不同。首先，uniform 是全局的（Global），它可以被着色器程序的任意着色器在任意阶段访问。第二，无论你把 uniform 值设置成什么，uniform 会一直保存它们的数据，直到它们被重置或更新。

我们可以在一个着色器中添加 uniform 关键字至类型和变量名前来声明一个 GLSL 的 uniform。

```glsl
#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; // 在 OpenGL 程序代码中设定这个变量

void main()
{
    // 把片段着色器的输出颜色设置为 ourColor
    FragColor = ourColor;
}
```

接着，为 `ourColor` 赋值：

```c
// 获取运行的秒数
float timeValue = glfwGetTime();
// 使用 sin 函数让颜色在 0.0 到 1.0 之间改变
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
// 查询 uniform ourColor 的位置值
int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
// 在当前激活的着色器程序中设置 uniform
glUseProgram(shaderProgram);
// 设置 uniform 值
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
```

