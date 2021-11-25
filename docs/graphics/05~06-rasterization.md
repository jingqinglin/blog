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

- 垂直可视角度（field-of-view）和长宽比（aspect ratio）

![](_images/0405-01.png ':size=50%')

在正交投影或透视投影结束后，将规范立方体显示到屏幕上（屏幕由像素点构成，是离散的，二维的）

## 三角形的离散化

光栅化就是把图元映射为屏幕上的像素。

图形学中，三角形是最基本的图元（Fundamental Shape Primitives）之一。如何通过像素点近似地表示一个三角形呢？采样（Sampling）

> 这里的采样指的是像素采样，而不是纹理采样

在一个点上计算一个函数就是采样。我们可以通过采样使函数离散化。三角形的采样函数：

$inside(t, x, y)=\left\{\begin{array}{ll}1 & \text { Point }(x, y) \\ & \text { in triangle } t \\ 0 & \text { otherwise }\end{array}\right.$

- 可通过**叉乘**判断一个像素点在三角形的内部还是外部
- 提高采样效率：轴向包围盒（Axis-Aligned Bounding Box，AABB），可不用遍历所有的像素

> [!NOTE|label:边界情况]
> 若像素点中心刚好落在三角形的边上，最好有一个统一的处理方式。对于 DirectX 来说，遵循[左上规则](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules#triangle-rasterization-rules-without-multisampling)：如果某个像素中心位于三角形的上边或左边，则将其定义为位于三角形内。其中：
> - 上边完全水平且高于其他边
> - 左边不完全水平且位于三角形左侧。一个三角形可以有一个或两个左边
> 
> ![](_images/0405-04.png ':size=50%')

## 深度测试与抗锯齿

采样的伪像或瑕疵（artifacts）：
- 锯齿（空间维度采样）
- 摩尔纹（空间维度采样，跳过奇数行列）
- 车轮效应（时间维度采样）
- ……

出现伪像的原因：信号变化太快（高频），但采样太慢。视频中分析了信号在频域上的表现形式（通过傅里叶变换把信号从时域或空域变换到频域），走样在频率的角度是什么表现形式没听懂。

> [!TIP|label:如何减少走样？]
> - Option 1：提高采样率
> - Option 2：反走样
>   先进行滤波操作，如模糊（抹除信号高频信息。高频就是频率变化快，一般是图像轮廓）。然后再采样
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