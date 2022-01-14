> 该节内容相对独立，可作为知识扩展


Imaging = Synthesis + Capture

- Synthesis: raster or ray tracing，合成的方法来成像
- Capture: 捕捉真实世界来成像
  - 相机
  - Transient Imaging: 研究光在极短时间内的传播
  - 计算摄影学（Computational Photography）


相机的成像原理：
- 小孔成像：没有虚化；之前的光追也是根据小孔成像原理
- 透镜成像

Shutter（快门）：控制光在多长的时间段内进入相机
Sensor（传感器）：捕捉光线
- 传感器的每个点集成了物体上所有点的光，因此所有像素值都是相似的（Each sensor point would integrate light from all points on the object, so all pixel values would be similar）
- 记录 irradiance

## 视场

> Field of View

$$\mathrm{FOV}=2 \arctan \left(\frac{h}{2 f}\right)$$

焦距可以影响 FOV

![](_images/19-01.png ':class=resizedImage')

通常以 35mm(36 x 24mm) 格式胶片为基准，通过定义焦距的方式来定义 FOV：
- 17mm is wide angle 104°
- 50mm is a “normal” lens 47°
- 200mm is telephoto lens 12°
- 手机相机上的焦距一般是等效焦距，因为胶片面积小于 35mm，真实焦距也要等比缩小

同样大小的胶片，焦距越大，视场越小

传感器（Sensor）和胶片（Film）有区别
- 通常两者可以混淆使用
- 在渲染器里面，传感器记录 irradiance，胶片决定存成什么样的图片格式

## 曝光

> Exposure

Exposure(H) = time(T) * irradiance(E)

Exposure time (T) 
- Controlled by shutter（快门）

Irradiance (E)
- 落在传感器单位面积上的光的功率
- Controlled by lens aperture（光圈） and focal length（焦距）

光圈大小
- 和人眼瞳孔大小原理相似
- F-Stop
- 光圈变大会出现景深

快门速度
- Change the duration the sensor pixels integrate light

ISO 增益
- 后期处理
- 在传感器值转变到数字图像值过程中，对值进行放大
- 硬件上：调节传感器灵敏度；软件上：调节数字信号

![](_images/19-02.png ':class=resizedImage')

- ISO 变大，放大信号的同时也会放大噪声

- F-Number(F-Stop)：曝光等级
  - Written as FN or F/N. N is the f-number
  - 非正式的理解：光圈直径的倒数

- 快门过慢的副作用
  - **运动模糊**：手抖或物体运动都可以造成，运动模糊不一定是坏事，比如在赛车游戏里

- Rolling shutter
 - 机械式快门打开有一个过程，和卷帘门拉起来很相似
 - 会造成高速运动的物体成像错误，比如螺旋桨扭曲，桨的不同部分在不同时刻被记录

## Thin Lens Approximation

> 薄透镜。焦距是由透镜的中心至主焦点的距离，平行光会聚集在焦点

真实的透镜存在像差，即透镜不会将光线会聚到任意一点。

理想的透镜：
- All parallel rays entering a lens pass through its focal point
- All rays through a focal point will be in parallel after passing the lens
- Focal length can be arbitrarily changed (in reality, yes!)

Thin Lens Equation:
$$\frac{1}{f}=\frac{1}{z_{i}}+\frac{1}{z_{o}}$$
焦距、像距、物距

## 散焦模糊

> Defocus Blur

透镜有个聚焦平面。

![](_images/19-03.png ':class=resizedImage')

从上面的等式可以看出，光圈大小和模糊圈（Circle of Confusion）成正比，因此光圈越大虚化越明显。

F-Number 的正式定义：焦距/光圈直径

## 使用薄透镜光线追踪

设置：
- 选择传感器尺寸、透镜焦距和光圈尺寸
- 选择合适的物距 $z_o$
  - 计算相应的镜距 $z_i$

![](_images/19-04.png ':class=resizedImage')

渲染：
- 遍历胶片上的每个像素 $x^\prime$
- 在透镜平面上的 $x^{\prime\prime}$ 点随机采样
- 穿过透镜的光线将击中 $x^{\prime\prime\prime}$（物体上的 $x^{\prime\prime\prime}$ 经过透镜后聚焦在 $x^\prime$）
- 估计 $x^{\prime\prime}$ -> $x^{\prime\prime\prime}$ 的 radiance

## 景深

![](_images/19-05.png ':class=resizedImage')

CoC 小到一定程度，可以认为是清晰的


## 光场

> Light Field / Lumigraph

下节课……

