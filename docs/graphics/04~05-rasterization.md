- Finishing up Viewing
- Rasterization
- Occlusions and Visibility

## Finishing up Viewing

- field-of-view(fov) 和 aspect ratio

![](_images/0405-01.png ':size=50%')

在正交投影或透视投影结束后，将规范立方体显示到屏幕上（屏幕由像素点构成，是离散的，二维的）

## 三角形的离散化

图形学中，三角形是最基本的图元（Fundamental Shape Primitives）之一。如何通过像素点近似地表示一个三角形呢？采样（Sampling）

在一个点上计算一个函数就是采样。我们可以通过采样使函数离散化。三角形的采样函数：

$inside(t, x, y)=\left\{\begin{array}{ll}1 & \text { Point }(x, y) \\ & \text { in triangle } t \\ 0 & \text { otherwise }\end{array}\right.$

- 可通过叉积判断一个点在三角形的内部还是外部
- 提高采样效率：包围盒（Bounding box）AABB
- 采样的缺点：以点代面，有失偏颇；若采样率低会出现锯齿