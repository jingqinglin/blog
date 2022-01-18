
> [!NOTE|label:为什么需要光线追踪？]
> - 光栅化不能很好地处理**全局效果**
>   - （软）阴影
>   - 尤其当光线反射不止一次的时候
> - 光栅化速度快，但质量相对较低
> - 光线追踪很精确，但速度很慢
>   - 光栅化用于实时渲染；光线追踪多用于离线渲染
>   - 一帧约 10k 个 CPU 小时（~10K CPU core hours to render one frame in production）

## 基本光线追踪算法

### 光线投射

> 第一步 Ray Casting

1. 通过每像素投射一束光线来生成图像（从眼睛/相机出发）
2. 通过向光源发送光线来检查阴影

![](_images/1316-01.png ':class=resizedImage')


### 递归光线追踪

> 第二步 Recursive (Whitted-Style) Ray Tracing，Whitted 是人名

![](_images/1316-02.png ':class=resizedImage')

如上图：
- 光线会弹射多次
- 在每一个弹射的点都计算着色的值，最后累加即为像素的值，每个点都会有系数否则可能过曝（除非被光源挡住，如图右上方的点）

以上为基本原理，后面开始解决原理中包含的具体技术问题。

### 光线-表面相交

> Ray-Surface Intersection

#### 光线方程

> Ray Equation

$\mathbf{r}(t)=\mathbf{o}+t \mathbf{d} \quad 0 \leq t<\infty$

#### 光线与球体相交

![](_images/1316-03.png ':class=resizedImage')

$(\mathbf{o}+t \mathbf{d}-\mathbf{c})^{2}-R^{2}=0$，$t$ 是未知数，即解一元二次方程。

#### 光线与三角形网格相交

判断光线与物体是否相交：

- 简单的做法：与模型上的每个三角形一一求交点
  - 太慢了
- 改进的方法 1：光线与三角形所在平面求交，再判断交点是否在三角形内（用点法式来表示平面 $a\left(x-x_{0}\right)+b\left(y-y_{0}\right)+c\left(z-z_{0}\right)=0$），相当于解一元一次方程
- 改进的方法 2：Möller Trumbore 算法
  - 利用重心坐标表示平面内的点，$\overrightarrow{\mathbf{O}}+t \overrightarrow{\mathbf{D}}=\left(1-b_{1}-b_{2}\right) \overrightarrow{\mathbf{P}}_{0}+b_{1} \overrightarrow{\mathbf{P}}_{1}+b_{2} \overrightarrow{\mathbf{P}}_{2}$
  - $t, b_1, b_2$ 是未知数，$\overrightarrow{\mathbf{P}}_{0}...$ 是三角形顶点，三维空间中可以列出三个方程式，因此相当于解三元一次方程（克莱姆法则），若三个未知数均为非负，则交点位于三角形内。该方程组的解在课件 13-29 中，作业 5 用到了

## 加速求交

如上述“简单的做法”中所述，与每个三角形求交太慢了

- 包围盒（Bounding Volumes）
  - 若光线未击中包围盒，也不会击中物体
  - 常用**轴对齐包围盒**（Axis-Aligned Bounding Box）
  - 盒子是三对“对面”的交集，下图为其中一对对面  
![](_images/1316-04.png ':class=resizedImage')

如何判断光线和盒子是否有交点：
- 关键点：
  - 光线进入**所有**“对面”时，代表光线进入了包围盒
  - 只要光线离开任意一对“对面”，代表光线离开了包围盒
- 每对“对面”，计算 $t_{min}$ 和 $t_{max}$，代表光线从发射到进入和离开该“对面”的时间
- 对于三维盒子，$t_{enter} = \max(t_{min})$，$t_{exit} = \min(t_{max})$
- 若 $t_{enter} < t_{exit}$，说明光线在盒子内停留了，有交点
- $t$ 为负时的情况：（iff 当且仅当）
![](_images/1316-05.png ':class=resizedImage')

> [!NOTE|label:为什么使用轴对齐？]
> 通用的方法是上述“改进的方法 1”  
> ![](_images/1316-06.png ':class=resizedImage')

### 如何使用 AABB 加速光线追踪

- 均匀网格
- 空间划分

#### 均匀空间划分

> Uniform Spatial Partitions

- 把空间均匀划分成格子，再与光线路径上的格子求交，若格子被标记则有可能与物体发生碰撞。*之前的求交方法都是光线和物体或其包围盒一一求交*
> ![](_images/1316-07.png ':class=resizedImage')
- 划分的格子数量不能太多也不能太少
- 某些类型的场景不适合此方法，如大空间中放置一个小物体。因此改进的思路是不均匀划分

#### 不均匀空间划分

> ![](_images/1316-08.png ':class=resizedImage')

- 八叉树（Oct-Tree），三维均匀切分，切分的层数与空间内物体密度有关，上图为二维空间实际上是四叉树
- ⭐ KD-Tree
  - 每次只沿某一个轴划分，不一定是均匀划分
  - 物体只储存在叶子结点
  - 指向子结点的指针
  - 遍历 KD-Tree：图示在课件 14-P21
    - 光线从树的根结点（可看作整个场景）开始遍历，若与某个结点有交点，则继续遍历其所有子结点；若无交点，则无需遍历其子结点。若遍历到叶结点，则与叶结点内的所有物体求交
  - KD—Tree 现在用得较少，原因有：
    - 一个物体存在多个叶子结点中
    - 三角形三个顶点都不在 Box 内，三角形却有一部分在 Box 内，求解困难
- BSP-Tree

#### 物体划分

> Object Partitions & Bounding Volume Hierarchy (BVH) 层次包围盒

- 以物体为单位划分空间

**BVH 构建**

```pdf
graphics/BVH.pdf
```

- 物体也存于叶子结点
- 包围盒可能会有重叠
- 每个物体只属于一个包围盒
- 怎么划分结点？
  - 选择一个轴
  - 启示 1：永远选择结点内最长的轴
  - 启示 2：划分后两边的三角形数量差最小，即 Top k 问题，可用快速选择
- 终止标准
  - 当结点包含很少元素时停止

**BVH 遍历**

> ![](_images/1316-26.png ':class=resizedImage')

## 辐射度量学

> Radiometry。从这里开始其他图形课几乎不会提及

用一系列物理量精确地定义光，包括光与物体表面如何作用、光的传播方法等等。高级的光线追踪建立在此基础上。

辐射通量，强度，辐照度，辐亮度（Radiant flux, intensity, irradiance, radiance）

### Radiant Energy and Flux

- Radiant Energy：电磁辐射的**能量**。$Q[\mathrm{J}=\text{Joule}]$。*图形学里基本不用*
- Radiant Flux（辐射通量）：单位时间内发射、反射、发射或接收的能量，即**功率**。*图形学里一般用这个概念*
  - 表达式：$\begin{aligned}\Phi \equiv \frac{\mathrm{d} Q}{\mathrm{d}t}\end{aligned}$
  - 单位：$[\mathrm{W}=\text{Watt}][\mathrm{lm}=\text{lumen}]$，lumen 译为流明

### Radiant Intensity

> 辐射强度

辐射（发光）强度是点光源发射的每单位立体角（Solid Angle）的**功率**。
- 表达式：$\begin{aligned}I(\omega) \equiv \frac{\mathrm{d} \Phi}{\mathrm{d} \omega}\end{aligned}$
- 单位：$\begin{aligned}\left[\frac{\mathrm{W}}{\mathrm{sr}}\right]\left[\frac{\mathrm{lm}}{\mathrm{sr}}=\mathrm{cd}=\text{candela}\right]\end{aligned}$

![](_images/1316-09.png ':class=resizedImage')

- 立体角
  - 球面的面积除以半径的平方，$\begin{aligned}\Omega=\frac{A}{r^{2}}\end{aligned}$
  - 整个球的立体角是 $4\pi$ steradians
  - **微分立体角**，课件 14-P49


### Radiant Irradiance

> 辐照度

辐照度是入射到表面点上的单位面积**功率**。表面要和光线垂直，否则要做投影再计算，遵循朗伯余弦定理。
- 表达式：$\begin{aligned}E(\mathbf{x}) \equiv \frac{\mathrm{d} \Phi(\mathbf{x})}{\mathrm{d} A}\end{aligned}$
- 单位：$\begin{aligned}\left[\frac{\mathrm{W}}{\mathrm{m}^{2}}\right]\left[\frac{\mathrm{lm}}{\mathrm{m}^{2}}=\mathrm{lux}\right]\end{aligned}$
- 辐照度可用来解释着色部分提及的光衰减

### Radiant Radiance

> 辐亮度

辐亮度是一个表面在每单位立体角、每单位投影面积上发射、反射、传输或接收的功率。

![](_images/1316-10.png ':class=resizedImage')

- 表达式：$\begin{aligned}L(\mathrm{p}, \omega) \equiv \frac{\mathrm{d}^{2} \Phi(\mathrm{p}, \omega)}{\mathrm{d} \omega \mathrm{d} A \cos \theta}\end{aligned}$
- 单位：$\begin{aligned}\left[\frac{\mathrm{W}}{\mathrm{sr}~\mathrm{m}^{2}}\right]\left[\frac{\mathrm{cd}}{\mathrm{m}^{2}}=\frac{\mathrm{lm}}{\mathrm{sr}~\mathrm{m}^{2}}=\text{nit}\right]\end{aligned}$
- Radiance: Irradiance per unit solid angle（入射辐亮度）
- Radiance: Intensity per projected unit area（出射辐亮度）

Irradiance 和 Radiance 在图形学中用得多。

## 光线传播

> Light Transport

> 双向反射分布函数（Bidirectional Reflectance Distribution Function, BRDF）

双向反射分布函数（BRDF）描述了从某个入射方向反射到每个出射方向的光量，可理解为入射光在不同出射方向的能量分布。

![](_images/1316-11.png ':class=resizedImage')

$\begin{aligned}f_{r}\left(\omega_{i} \rightarrow \omega_{r}\right)=\frac{\mathrm{d} L_{r}\left(\omega_{r}\right)}{\mathrm{d} E_{i}\left(\omega_{i}\right)}=\frac{\mathrm{d} L_{r}\left(\omega_{r}\right)}{L_{i}\left(\omega_{i}\right) \cos \theta_{i} \mathrm{d} \omega_{i}}\left[\frac{1}{\mathrm{sr}}\right]\end{aligned}$

### 反射方程

对一个着色点，积分所有入射方向的 BRDF（因为 BRDF 是某个入射方向的）

$\begin{aligned}L_{r}\left(\mathrm{p}, \omega_{r}\right)=\int_{H^{2}} f_{r}\left(\mathrm{p}, \omega_{i} \rightarrow \omega_{r}\right) L_{i}\left(\mathrm{p}, \omega_{i}\right) \cos \theta_{i} \mathrm{d} \omega_{i}\end{aligned}$

Challenge: Recursive Equation
- 入射光可能不止是光源，可以是来自其他物体的反射光

### 渲染方程

在反射方程中添加一个发射项使其具有通用性。

$\begin{aligned}L_{o}\left(p, \omega_{o}\right)=L_{e}\left(p, \omega_{o}\right)+\int_{\Omega^{+}} L_{i}\left(p, \omega_{i}\right) f_{r}\left(p, \omega_{i}, \omega_{o}\right)\left(n \cdot \omega_{i}\right) \mathrm{d} \omega_{i}\end{aligned}$

- 考虑了着色点自己会发光的情况
- 和 Blinn-Phong 模型一样，假设所有向量都指向外
- $H^2$ 和 $\Omega^{+}$ 的范围只考虑半球

> [!NOTE|label:理解渲染方程]
> 单个点光源：
> 
> ![](_images/1316-12.png ':class=resizedImage')
> 
> 多个点光源：相加
> 
> ![](_images/1316-13.png ':class=resizedImage')
> 
> 面光源：积分
> 
> ![](_images/1316-14.png ':class=resizedImage')
> 
> 其他考虑物体反射的光线：式子未变，但是等式右边出现了未知量，需要先计算
> 
> ![](_images/1316-15.png ':class=resizedImage')
> 
> （数学部分 Hard）该方程的第二类标准型 Fredholm 积分方程为：$\begin{aligned}I(u)=\theta(u)+\int l(v)K(u,v)dv\end{aligned}$，可以离散成一个简单的矩阵方程 $L = E + KL$，弹幕提到 $L$ 是矩阵级数 Neumann 级数收敛值、$K$ 是有界线性算子
> 
> ![](_images/1316-16.png ':class=resizedImage')  
> ![](_images/1316-17.png ':class=resizedImage')

## 概率论回顾

- 随机变量 $X$：可能取很多数值的变量
- 概率密度函数 $X \sim p(x)$：取不同数值的概率
- 期望：重复从随机分布中抽取样本得到的平均值，$\begin{aligned}E[X]=\sum_{i=1}^{n} x_{i} p_{i}\end{aligned}$

连续情况下：
- 概率密度函数  $X \sim p(x)$ 的性质：$p(x) \geq 0$ 且 $\begin{aligned}\int p(x) dx=1\end{aligned}$
- 期望：$\begin{aligned}E[X]=\int x p(x) dx\end{aligned}$

## 全局光照

直接和间接光照的集合，随着反弹次数的增大，亮度会收敛

## 蒙特卡洛积分

> 为什么：我们要求解一个积分，但是用解析方法求解太困难了
> 
> 是什么 & 怎么办：通过对函数值的随机样本进行平均来**估计**函数的积分（定积分）

- Monte Carlo estimator：$\begin{aligned}F_{N}=\frac{1}{N} \sum_{i=1}^{N} \frac{f\left(X_{i}\right)}{p\left(X_{i}\right)}\end{aligned}$
- 可理解为通过求长方形的平均面积来估计积分，其中长方形的宽为该随机变量在积分区域内概率的倒数 $\frac{1}{p(X_i)}$，高为 $f(X_i)$；$N$ 是采样数；样本越多，方差越小
- 当使用均匀随机变量采样时：  
![](_images/1316-18.png ':class=resizedImage')  
![](_images/1316-19.png ':class=resizedImage')

## 路径追踪

Whitted-Style Ray Tracing 的问题：
- Always perform specular reflections / refractions
- Stop bouncing at diffuse surfaces

Whitted-Style Ray Tracing is Wrong, but the rendering equation is correct.


用蒙特卡洛方法近似地求渲染方程，使用均匀采样。用来计算各个方向的**光源**对着色点的直接光照结果。

$\begin{aligned} L_{o}\left(p, \omega_{o}\right) &=\int_{\Omega^{+}} L_{i}\left(p, \omega_{i}\right) f_{r}\left(p, \omega_{i}, \omega_{o}\right)\left(n \cdot \omega_{i}\right) \mathrm{d} \omega_{i} \\ & \approx \frac{1}{N} \sum_{i=1}^{N} \frac{L_{i}\left(p, \omega_{i}\right) f_{r}\left(p, \omega_{i}, \omega_{o}\right)\left(n \cdot \omega_{i}\right)}{p\left(\omega_{i}\right)} \end{aligned}$

```
// 着色点 p，出射光 wo
// 从眼睛开始逆向追踪光线，光线从 p 点反射到各个入射方向 wi（对 wi 进行随机采样），若击中光源，则加上该方向的“贡献”
// 而 Whitted 光线追踪在着色点的计算仍采用 Blinn-Phong 模型，不是渲染方程
shade(p, wo)
  Randomly choose N directions wi~pdf
  Lo = 0.0
  For each wi
    Trace a ray r(p, wi)
    If ray r hit the light
      Lo += (1 / N) * L_i * f_r * cosine / pdf(wi)
  Return Lo
```

如果从着色点 P 发出的光线击中了物体的 Q 点该怎么办？

![](_images/1316-20.png ':class=resizedImage')

```
shade(p, wo)
  Randomly choose N directions wi~pdf
  Lo = 0.0
  For each wi
    Trace a ray r(p, wi)
    If ray r hit the light
      Lo += (1 / N) * L_i * f_r * cosine / pdf(wi)
    // 把光源的 radiance 换成 q 点 -wi 方向的 radiance
    Else If ray r hit an object at q
      Lo += (1 / N) * shade(q, -wi) * f_r * cosine / pdf(wi)
Return Lo
```

上述方法存在的问题：
- **光线数量爆炸**，$rays = N^{bounces}$  
![](_images/1316-21.png ':class=resizedImage')
  - 解决方法：只反射一根光线 $N = 1$，这就是**路径追踪**，但这会有很大的噪声
  - 改进：在每个像素上追踪更多的路径，然后求平均的 radiance，该方法叫 Ray Generation，如下图  
![](_images/1316-22.png ':class=resizedImage')

- **递归算法不会停止**
  - 解决方法 1：限定弹射次数。会造成能量损失，因为现实中光线的弹射是不会停的
  - 解决方法 2：俄罗斯轮盘赌，$P$ 概率的光线 radiance 为 $L_o / P$，$1-P$ 概率的光线 radiance 为 0，这样期望仍是 $E = P * (L_o / P) + (1 - P) * 0 = L_o$  
![](_images/1316-23.png ':class=resizedImage')

现在已经有了正确的路径跟踪方法，但并不是很高效。因为能不能击中（面）光源很看**运气**，很多光线会被“浪费”。

蒙特卡罗方法允许任何采样方法，因此可以对光源进行采样。但是积分是在着色点的立体角 $d\omega$上，因此需要把渲染方程写成在光源表面 $dA$ 上的积分，即改变积分域。
![](_images/1316-24.png ':class=resizedImage')  
$d\omega$ 与 $dA$ 有以下关系：$\begin{aligned} d \omega=\frac{d A \cos \theta^{\prime}}{\left\|x^{\prime}-x\right\|^{2}}\end{aligned}$  
改写后的渲染方程，对（面）光源进行均匀采样的 PDF 为 $1/A$：  
$\begin{aligned} L_{o}\left(x, \omega_{o}\right) &=\int_{\Omega^{+}} L_{i}\left(x, \omega_{i}\right) f_{r}\left(x, \omega_{i}, \omega_{o}\right) \cos \theta \mathrm{d} \omega_{i} \\ &=\int_{A} L_{i}\left(x, \omega_{i}\right) f_{r}\left(x, \omega_{i}, \omega_{o}\right) \frac{\cos \theta \cos \theta^{\prime}}{\left\|x^{\prime}-x\right\|^{2}} \mathrm{d} A \end{aligned}$


radiance 来自两部分：
1. 光源。按照改写后的渲染方程
2. 其他反射体。按照原来的“俄罗斯轮盘赌”方式来计算

伪代码：  
![](_images/1316-25.png ':class=resizedImage')

最后一个问题：
- **需要检测光源和着色点之间有无遮挡**

路径追踪难以处理点光源，trick 是看作一个很小面积的光源。


> Ray tracing 概念：
> - Previous：Ray tracing == Whitted-style ray tracing
> - Modern
>   - The general solution of light transport, including
>       - (Unidirectional & bidirectional) path tracing
>       - Photon mapping
>       - Metropolis light transport
>       - VCM / UPBP…

> 课程未涉及的：
> - Uniformly sampling the hemisphere
>   - How? And in general, how to sample any function?(sampling)
> - Monte Carlo integration allows arbitrary pdfs
>   - What's the best choice? (importance sampling)
> - Do random numbers matter?
>   - Yes! (low discrepancy sequences)
> - I can sample the hemisphere and the light
>   - Can I combine them? Yes! (multiple imp. sampling)
> - The radiance of a pixel is the average of radiance on all paths passing through it
>   - Why? (pixel reconstruction filter)
> - Is the radiance of a pixel the color of a pixel?（Radiance 换算成颜色需要伽马校正）
>   - No. (gamma correction, curves, color space)

<hr>
<br><br>
<center>光线追踪部分结束</center>
