- 二维变换
- 齐次坐标
- 组合变换
- 三维变换
- 观测（Viewing）变换

## 二维变换

使用矩阵表示表换。

- 线性变换：旋转，缩放，切变（原点不变）  
  $\left[\begin{array}{l}x^{\prime} \\ y^{\prime}\end{array}\right]=\left[\begin{array}{ll}a & b \\ c & d\end{array}\right]\left[\begin{array}{l}x \\ y\end{array}\right]$
- 仿射变换：线性变换**接上**平移  
  $\left[\begin{array}{l}x^{\prime} \\ y^{\prime}\end{array}\right]=\left[\begin{array}{ll}a & b \\ c & d\end{array}\right]\left[\begin{array}{l}x \\ y\end{array}\right]+\left[\begin{array}{l}t_{x} \\ t_{y}\end{array}\right]$

## 齐次坐标

平移不能以**矩阵连乘**的形式表示，因此引入齐次坐标（用 $N + 1$ 维来代表 $N$ 维坐标）：增加第三个轴（$w$ 轴）
- 二维点：$(x, y, 1)^{\mathsf{T}}$
- 二维向量：$(x, y, 0)^{\mathsf{T}}$

$\left[\begin{array}{l}x^{\prime} \\ y^{\prime} \\ w^{\prime}\end{array}\right]=\left[\begin{array}{ccc}1 & 0 & t_{x} \\ 0 & 1 & t_{y} \\ 0 & 0 & 1\end{array}\right] \cdot\left[\begin{array}{l}x \\ y \\ 1\end{array}\right]=\left[\begin{array}{c}x+t_{x} \\ y+t_{y} \\ 1\end{array}\right]$

这样平移也可以用矩阵相乘的方式表示。

- 向量和点为什么在 $w$ 轴上有区别？
  - 向量具有平移不变性，经上述矩阵相乘后结果不变
  - 
    - 向量 + 向量 = 向量
    - 点 - 点 = 向量
    - 点 + 向量 = 点（点沿着向量移动）
    - 点 + 点 = 两个点的中点（相加后 $w = 2$，对相加后三个维度都除以 $2$ 即新的点）

## 组合变换

$A_{n}\left(\ldots A_{2}\left(A_{1}(\mathbf{x})\right)\right)=\mathbf{A}_{n} \cdots \mathbf{A}_{2} \cdot \mathbf{A}_{1} \cdot\left[\begin{array}{l}x \\ y \\ 1\end{array}\right]$

## 三维变换

- 旋转的表示：欧拉角、四元数
- 罗德里格斯旋转公式：给定转轴和旋转角度后，旋转一个向量的算法（此处默认转轴过原点）

## 观测变换（Viewing Transformation）

> 对应虎书第七章，会夹杂一些渲染管线的概念，方便理解

> [!TIP|label:Think about how to take a photo]
> - Find a good place and arrange people (model transformation)
> - Find a good "angle" to put the camera (view transformation)
> - Cheese! (projection transformation)
> 
> 一个物体从三维坐标映射到屏幕空间上，要经过一系列的坐标系变换，见下图。物体经历了从物体空间到世界空间（模型变换，Model Transformation），再从世界空间到相机空间（相机变换，Camera Transformation 或视图变换，View Transformation），再到裁剪空间（投影变换，Projection Transformation，是 Vertex Shader 的输出），最后到屏幕空间（视口变换，Vierport Transformation），这通常被当作是渲染管线的几何阶段。其中三维到二维的变换发生在视口变换过程中。**值得注意的是，图元的坐标变换到屏幕空间后，通常也会保留 $z$ 和 $w$ 分量**，因为渲染管线几何阶段后的光栅化阶段要进行深度测试。
> 
> 此过程的详细说明可参考 [Learn OpenGL](https://learnopengl-cn.github.io/01%20Getting%20started/08%20Coordinate%20Systems/)。（关注透视除法：裁剪空间做透视除法后转为 NDC）
> 

![](_images/0304-00.png ':class=resizedImage')

### 视图/相机变换

![](_images/0304-01.png ':class=resizedImage')

定义相机：
- 位置，Position $\vec{e}$
- 观察方向，Look-at direction $\hat{g}$
- 上方向，Up direction $\hat{t}$

一般约定把相机放在“标准位置”上——The origin, up at Y, look at -Z，所以需要把相机变换到标准位置上（物体也跟着变换）。需要先平移到原点再作旋转，变换矩阵见课件 P15 & 16。可以从基变换的角度理解（闫老师不推荐这个角度），p16 左下角的矩阵可看作是一个基向量组。下图摘自：https://zhuanlan.zhihu.com/p/356261083

![](_images/0304-02.png ':size=300')

### ⭐ 投影变换

![](_images/0304-03.png ':class=resizedImage')

#### 正交投影（Orthographic Projection）

正交投影是平行投影的一种形式，所有投影线都与投影平面正交。若两向量的点积为 0，则称它们是正交的。

我们通常用投影变换把正交视域体（Orthographic View Volume）变换到规范视域体（Canonical View Volume）：
1. 将正交视域体的中心平移到原点
2. 再将平移后长方体的缩放到规范视域体 $(-1, -1, -1)$ 到 $(1, 1, 1)$。不同 API 有不同的规范视域体。

![](_images/0304-05.png ':class=resizedImage')

边界平面如下：

$$
x = l \equiv \text{left plane},\\
x = r \equiv \text{right plane},\\
y = b \equiv \text{bottom plane},\\
y = t \equiv \text{top plane},\\
z = n \equiv \text{near plane},\\
z = f \equiv \text{far plane}
$$

得出，正交投影矩阵如下：

$$
\begin{aligned}
M_{Ortho} &= \left[\begin{array}{cccc}\frac{2}{r-l} & 0 & 0 & 0 \\ 0 & \frac{2}{t-b} & 0 & 0 \\ 0 & 0 & \frac{2}{n-f} & 0 \\ 0 & 0 & 0 & 1\end{array}\right]\left[\begin{array}{cccc}1 & 0 & 0 & -\frac{l+r}{2} \\ 0 & 1 & 0 & -\frac{b+t}{2} \\ 0 & 0 & 1 & -\frac{f+n}{2} \\ 0 & 0 & 0 & 1\end{array}\right] \\ &=\left[\begin{array}{cccc}\frac{2}{r-l} & 0 & 0 & \frac{l+r}{l-r} \\ 0 & \frac{2}{t-b} & 0 & \frac{b+t}{b-t} \\ 0 & 0 & \frac{2}{n-f} & \frac{f+n}{f-n} \\ 0 & 0 & 0 & 1\end{array}\right]
\end{aligned}
$$

OpenGL 使用右手坐标系和列向量，因此上述矩阵是 OpenGL 使用的正交投影矩阵。关于 DirectX 正交投影矩阵的转换，参考[文章](https://zhuanlan.zhihu.com/p/359128442)。

> [!NOTE]
> 
> 这个变换并不是真正的投影，而是把物体或图元从相机空间变换到裁剪空间，是在为投影做准备，它能够保留深度信息，方便后续光栅化阶段进行深度测试。若无需考虑深度信息，可直接去掉 $z$ 轴来简单地表示正交投影：
> 
> $M_{Ortho}=\left[\begin{array}{cccc}1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 0 & 0 \\ 0 & 0 & 0 & 1\end{array}\right]$

#### 透视投影（Perspective Projection）

透视投影也可以和上述简单正交投影一样去掉 $z$ 轴，$x$ 和 $y$ 轴按比例计算。但这并不符合我们的需求，因此讲透视投影变换分为两步：
1. “挤压”平截头体（最终效果是往远平面压缩），让其成为一个长方体，如下图：
![](_images/0304-06.png ':class=resizedImage')
2. 对长方体进行正交投影

在 $yOz$ 平面上，透视投影可以用下图来表示：

![](_images/0304-07.png ':class=resizedImage')

可以看到平截头体内的点 $(x, y, z)$ 被投影到近平面上的 $(x^{\prime}, y^{\prime}, z^{\prime})$。对于这个变换，我们可以得到以下几条规律：
1. 变换后，平截头体内的点的 $x$ 和 $y$ 坐标进行了线性缩放，$x^{\prime}=\frac{n}{z}x, y^{\prime}=\frac{n}{z}y$
2. 变换后，近平面上所有点的坐标不变
3. 变换后，远平面上所有点的 $z$ 坐标不变

根据规律 $1$，可以得出 $M_{Persp \rightarrow Ortho}\left[\begin{array}{c}x \\ y \\ z \\ 1\end{array}\right]=\left[\begin{array}{c}\frac{n}{z}x \\ \frac{n}{z}y \\ ? \\ 1\end{array}\right]=\left[\begin{array}{c}nx \\ ny \\ ? \\ z\end{array}\right]$，所以，$M_{Persp \rightarrow Ortho}=\left[\begin{array}{cccc}n & 0 & 0 & 0 \\ 0 & n & 0 & 0 \\ ? & ? & ? & ? \\ 0 & 0 & 1 & 0\end{array}\right]$

根据规律 $2$，可以得出 $M_{Persp \rightarrow Ortho}\left[\begin{array}{c}x \\ y \\ n \\ 1\end{array}\right]=\left[\begin{array}{c}x \\ y \\ n \\ 1\end{array}\right]=\left[\begin{array}{c}nx \\ ny \\ n^2 \\ n\end{array}\right]$，所以，$M_{Persp \rightarrow Ortho}=\left[\begin{array}{cccc}n & 0 & 0 & 0 \\ 0 & n & 0 & 0 \\ 0 & 0 & ? & ? \\ 0 & 0 & 1 & 0\end{array}\right]$

根据规律 $3$，可以得出 $M_{Persp \rightarrow Ortho}\left[\begin{array}{c}x \\ y \\ f \\ 1\end{array}\right]=\left[\begin{array}{c}\frac{n}{f}x \\ \frac{n}{f}y \\ f \\ 1\end{array}\right]=\left[\begin{array}{c}nx \\ ny \\ f^2 \\ f\end{array}\right]$，所以，$M_{Persp \rightarrow Ortho}=\left[\begin{array}{cccc}n & 0 & 0 & 0 \\ 0 & n & 0 & 0 \\ 0 & 0 & {n+f} & -nf \\ 0 & 0 & 1 & 0\end{array}\right]$

结合正交投影矩阵，可得到透视投影矩阵 $M_{Persp}=M_{Ortho} M_{Persp \rightarrow Ortho}=\left[\begin{array}{cccc}\frac{2}{r-l} & 0 & 0 & \frac{l+r}{l-r} \\ 0 & \frac{2}{t-b} & 0 & \frac{b+t}{b-t} \\ 0 & 0 & \frac{2}{n-f} & \frac{f+n}{f-n} \\ 0 & 0 & 0 & 1\end{array}\right]\left[\begin{array}{ccccc}n & 0 & 0 & 0 \\ 0 & n & 0 & 0 \\ 0 & 0 & n+f & -nf \\ 0 & 0 & 1 & 0\end{array}\right]=\left[\begin{array}{cccc}\frac{2n}{r-l} & 0 & \frac{l+r}{l-r} & 0 \\ 0 & \frac{2n}{t-b} & \frac{b+t}{b-t} & 0 \\ 0 & 0 & \frac{n+f}{n-f} & \frac{2nf}{f-n} \\ 0 & 0 & 1 & 0 \end{array}\right]$

由于 $r = -l, t = -b$，所以 $M_{Persp}=\left[\begin{array}{cccc}\frac{n}{r} & 0 & 0 & 0 \\ 0 & \frac{n}{t} & 0 & 0 \\ 0 & 0 & \frac{n+f}{n-f} & \frac{2nf}{f-n} \\ 0 & 0 & 1 & 0 \end{array}\right]$

另外一种透视投影矩阵的表示方式是通过视角（Fovy）和宽高比（Aspect）来表示。由于 $aspect = \frac{w}{h} = \frac{r}{t}$，$t = n\tan{\frac{\theta}{2}}$

所以 $M_{Persp}=\left[\begin{array}{cccc}\frac{1}{aspect \tan{\frac{\theta}{2}}} & 0 & 0 & 0 \\ 0 & \frac{1}{\tan{\frac{\theta}{2}}} & 0 & 0 \\ 0 & 0 & \frac{n+f}{n-f} & \frac{2nf}{f-n} \\ 0 & 0 & 1 & 0 \end{array}\right]$，**$M_{Persp}$ 把物体从相机空间变换到裁剪空间。之后进行裁剪和透视除法，此时物体的坐标被称为 NDC，位于规范视域体内**。

> 以上过程还参考了知乎[文章](https://zhuanlan.zhihu.com/p/359128442)。

## 补充

- 旋转变换矩阵的逆矩阵和转置矩阵相等（称为正交矩阵）

$R_{\theta}=\left(\begin{array}{cc}\cos \theta & -\sin \theta \\ \sin \theta & \cos \theta\end{array}\right)$

$R_{-\theta}=\left(\begin{array}{cc}\cos \theta & \sin \theta \\ -\sin \theta & \cos \theta\end{array}\right)=R_{\theta}^{\top}$