> 该节内容作为知识扩展

## 高级光线传播

- Unbiased light transport methods
  - 双向路径追踪，Bidirectional path tracing (BDPT)
  - Metropolis light transport (MLT)
- Biased light transport methods
  - 光子映射，Photon mapping
  - Vertex connection and merging (VCM)

- 无偏估计：估计量的数学期望等于被估计参数的真实值
- [如何理解 (un)biased render？ - 知乎](https://www.zhihu.com/question/26683585)

### 双向路径追踪

> Bidirectional Path Tracing (BDPT)

- 跟踪来自相机和灯光的半路径（sub-paths）
- 连接两个半路径的端点

### Metropolis Light Transport

- 马尔可夫链：根据当前样本，根据一个概率分布函数，生成下一个相近的样本
- Key idea：局部扰动现有路径以获得新路径

### 光子映射

> Photon Mapping，有偏估计

- 擅长处理镜面-漫反射-镜面（Specular-Diffuse-Specular）路径和焦散
- 阶段 1——光子追踪
  - 从光源发射光子，使其反弹，然后在漫反射表面上记录光子
- 阶段 2——光子收集
  - 从相机射出半路径，使其反弹，直到它们击中漫反射表面
- 计算——局部密度估计
  - 光子较多的区域应更亮
  - 局部密度估计（有偏，$dN / dA \neq \Delta N / \Delta A$）。对于每个着色点，查找最近的 N 个光子，找出它们覆盖的面积，即可计算密度
- 有偏会出现模糊

### VCM

> Vertex Connection and Merging，双向路径追踪 + 光子映射

### 实时辐射度

> Instant Radiosity

已经被照亮的地方都可以被认为是光源

## Advanced Appearance Modeling

### 非表面模型

#### 参与（散射）介质

- 当光通过参与介质的任何一点时，它都可以被（部分）吸收和散射
- 相位函数，决定光线如何散射
- 渲染方程不适用
- 巧克力、手指也是散射介质，[次表面散射](https://www.google.com/search?q=%E6%AC%A1%E8%A1%A8%E9%9D%A2%E6%95%A3%E5%B0%84)


> 后续一些模型描述，可以看[课件](https://sites.cs.ucsb.edu/~lingqi/teaching/resources/GAMES101_Lecture_18.pdf)和这篇[笔记](https://www.notion.so/Lec-18-Advanced-Topics-in-Rendering-c40ecbb678744b8e85fd2cf095067026)

#### 头发

#### 颗粒状材质

### 表面模型

#### 次表面散射

#### 布料


## Procedural Appearance

程序化生成材质