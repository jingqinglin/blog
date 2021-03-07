- Finishing up Viewing
- Rasterization
  - Point-in-triangle test
  - Aliasing
- Antialiasing
  - Sampling theory
  - Antialiasing in practice
- Occlusions and Visibility
  - Z-buffering

## Finishing up Viewing

- field-of-view(fov) 和 aspect ratio

![](_images/0405-01.png ':size=50%')

在正交投影或透视投影结束后，将规范立方体显示到屏幕上（屏幕由像素点构成，是离散的，二维的）

## 三角形的离散化

图形学中，三角形是最基本的图元（Fundamental Shape Primitives）之一。如何通过像素点近似地表示一个三角形呢？采样（Sampling）

> 这里的采样指的是像素采样，而不是纹理采样

在一个点上计算一个函数就是采样。我们可以通过采样使函数离散化。三角形的采样函数：

$inside(t, x, y)=\left\{\begin{array}{ll}1 & \text { Point }(x, y) \\ & \text { in triangle } t \\ 0 & \text { otherwise }\end{array}\right.$

- 可通过叉积判断一个像素点在三角形的内部还是外部
- 提高采样效率：包围盒（Bounding box）AABB


## 深度测试与抗锯齿

采样的伪像或瑕疵（artifacts）：
- 锯齿（空间维度采样）
- 摩尔纹（空间维度采样）
- 车轮效应（时间维度采样）
- ……

出现伪像的原因：信号变化太快（高频），但采样太慢。

> [!TIP|label:如何减少走样？]
> - Option 1：提高采样率
> - Option 2：反走样
>   - 滤波操作（抹除信号高频信息。高频就是频率变化快，显示图像轮廓）
>   - 采样
> 
> 滤波器 = 抛弃特定频率的内容（Filtering = Getting rid of certain frequency contents）

### 多重采样抗锯齿（MSAA）

可以理解为对一个像素点进行多次采样，不同于超采样，MSAA 中对不同的像素会复用一些点。

![](_images/0405-02.png ':size=70%')
![](_images/0405-03.png ':size=70%')

缺点：提高了计算的成本

其他反走样方式：
- FXAA (Fast Approximate AA)。后期处理边界
- TAA (Temporal AA)。对于静止物体，每帧在像素内的不同位置采样，可以看作把 MSAA 分布在时间上