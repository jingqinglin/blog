
> [!NOTE|label:为什么需要光线追踪？]
> - 光栅化不能很好地处理全局效果
>   - （软）阴影
>   - 尤其当光线反射不止一次的时候
> - 光栅化速度快，但质量相对较低
> - 光线追踪很精确，但速度很慢
>   - 光栅化用于实时渲染；光线追踪多用于离线渲染
>   - 一帧约 10k 个 CPU 小时（~10K CPU core hours to render one frame in production）

## 基本光线追踪算法

### 光线投射（Ray Casting）

1. 通过每像素投射一束光线来生成图像（从眼睛/相机出发）
2. 通过向光源发送光线来检查阴影

![](_images/1316-01.png ':class=resizedImage')


### 递归光线追踪（Recursive (Whitted-Style) Ray Tracing）

> Whitted 是人名

![](_images/1316-02.png ':class=resizedImage')

如上图：
- 光线会弹射多次
- 在每一个弹射的点都计算着色的值，最后累加即为像素的值，每个点都会有系数否则可能过曝（除非被光源挡住，如图右上方的点）

以上为基本原理，后面开始解决原理中包含的具体技术问题

## 光线-表面相交（Ray-Surface Intersection）

### 光线方程（Ray Equation）

$\mathbf{r}(t)=\mathbf{o}+t \mathbf{d} \quad 0 \leq t<\infty$

### 光线与球体相交

![](_images/1316-03.png ':class=resizedImage')

$(\mathbf{o}+t \mathbf{d}-\mathbf{c})^{2}-R^{2}=0$，$t$ 是未知数，即解一元二次方程。

### 光线与三角形网格相交

判断光线与物体是否相交：

- 简单的做法：与模型上的每个三角形一一求交点
  - 太慢了
- 改进的方法 1：光线与三角形所在平面求交，再判断交点是否在三角形内（用点法式来表示平面 $a\left(x-x_{0}\right)+b\left(y-y_{0}\right)+c\left(z-z_{0}\right)=0$），相当于解一元一次方程
- 改进的方法 2：Möller Trumbore 算法
  - 利用重心坐标表示平面内的点，$\overrightarrow{\mathbf{O}}+t \overrightarrow{\mathbf{D}}=\left(1-b_{1}-b_{2}\right) \overrightarrow{\mathbf{P}}_{0}+b_{1} \overrightarrow{\mathbf{P}}_{1}+b_{2} \overrightarrow{\mathbf{P}}_{2}$
  - $t, b_1, b_2$ 是未知数，$\overrightarrow{\mathbf{P}}_{0}...$ 是三角形顶点，三维空间中可以列出三个方程式，因此相当于解三元一次方程（用克拉默法则），若三个未知数均为非负，则交点位于三角形内

#### 加速求交

如上述“简单的做法”中所述，与每个三角形求交太慢了

- 包围盒（Bounding Volumes）
  - 若光线未击中包围盒，也不会击中对象
  - 常用轴对齐包围盒（Axis-Aligned Bounding Box）
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
