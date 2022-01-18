> 基本概念、质点弹簧系统、运动学、求解常微分方程，刚体与流体

---

第 21 节

计算机动画简介
- 历史
- 关键帧动画
- 物理模拟
- 运动学（Kinematics） 
- Rigging

---

图形学中动画是建模的扩展：将场景模型表示为时间的函数。

输出：按顺序观看时提供运动感的图像序列
- 电影：24 FPS
- 视频：30 FPS
- VR：90 FPS（不晕）

## 关键帧动画

指角色或者物体运动变化中关键动作所处的那一帧。关键帧与关键帧之间的动画可以由软件创建添加，叫做过渡帧或者中间帧。

- 中间帧可由关键帧插值得来
- 调用样条曲线进行平滑/可控插值

## 物理模拟\仿真

利用物理公式模拟物体形状或位置上的变化，如布料模拟、流体等。**先模拟后渲染**。

### 质点弹簧系统

> Mass Spring System，第八次作业

![](_images/2122-01.png ':class=resizedImage')

弹簧本身有长度，因此

$$\boldsymbol{f}_{a \rightarrow b}=k_{s} \frac{\boldsymbol{b}-\boldsymbol{a}}{\|\boldsymbol{b}-\boldsymbol{a}\|}(\|\boldsymbol{b}-\boldsymbol{a}\|-l)$$

$\boldsymbol{f}_{a \rightarrow b}$ 表示 $a$ 受到来自 $b$ 的力。此公式下弹簧不会停止震荡，需要加一个阻尼。

模拟仿真中，一个点表示一阶导数：
$$\begin{aligned} &\boldsymbol{x}\\ &\dot{\boldsymbol{x}}=\boldsymbol{v}\\ &\ddot{\boldsymbol{x}}=\boldsymbol{a} \end{aligned}$$

简单运动阻尼（Damping）：
$$\boldsymbol{f}=-k_{d}\dot{\boldsymbol{b}}$$

$k_{d}$ 是阻尼系数、$\dot{\boldsymbol{b}}$ 是速度。这个式子表示不了弹簧内部的能量损失。

![](_images/2122-02.png ':class=resizedImage')

- 红框是沿 ab 方向的相对速度的值（标量）
- 粘性阻力仅在弹簧长度变化时产生
- 只是一种的阻尼近似

> 一些拥有弹簧性质的结构，视频 [38:28](https://www.bilibili.com/video/BV1X7411F744?p=21&t=0h38m28s)


其他模拟方法：有限元方法，FEM（Finite Element Method）。力传导扩散适合用有限元方法建模做，如车辆碰撞。

### 粒子系统

每个粒子的运动由一组物理（或非物理）力定义。

挑战：
- 粒子的数量
- 粒子的加速结构（如，邻近粒子间的相互作用）


粒子在动画中的每一帧：
- [If needed] Remove dead particles
- Calculate forces on each particle
- Update each particle’s position and velocity
- [If needed] Create new particles
- Render particles

粒子系统的力：

Attraction and repulsion forces
- Gravity, electromagnetism, …
- Springs, propulsion, … 

Damping forces
- Friction, air drag, viscosity, … 

Collisions
- Walls, containers, fixed objects, …
- Dynamic objects, character body parts, …

## 运动学

### 正运动学

> Forward Kinematics，明确骨骼之间的运动关系，计算出各个部位的位置

![](_images/2122-03.png ':class=resizedImage')


关节骨骼：
- 拓扑学（什么连接到什么）
- 关节的几何关系
- 树结构（在没有循环的情况下）

（骨骼）连接类型：
- Pin (1D rotation)
- Ball (2D rotation)
- Prismatic joint (translation)，![](_images/2122-04.png ':class=resizedImage')

### 逆运动学


限制各个部位的位置、限制骨骼的运动方式，再计算骨骼的运动。

## Rigging

类似于操作木偶，允许对姿势、变形、表情等进行更快速、更直观的修改。

- Like strings on a puppet（木偶）
- Captures all meaningful character changes
- Varies from character to character

## 动作捕捉

真人的动作反映到虚拟的人物中，需要建立真实和虚拟的联系。NBA 2K 会对球星进行动作捕捉。

Data-driven approach to creating animation sequences
- Record real-world performances (e.g. person executing an activity)
- Extract pose as a function of time from the data collected

优点：
- 可以快速捕获大量真实数据
- 真实度高

缺点：
- 复杂且费钱
- 捕获的动画可能无法满足艺术需要，需要修改

## 动画生成流程

![](_images/2122-05.png ':class=resizedImage')

---

第 22 节，介绍数学方法，数值分析知识

- 简单粒子模拟
  - 欧拉方法
  - 不稳定和提高
- 刚体模拟
- 流体模拟

---

## 简单粒子模拟

> 首先研究单个粒子的运动，再推广到许多粒子

首先，假设粒子的运动由一个速度矢量场决定，它是位置和时间的函数，$v(x, t)$

计算粒子的位置需要计算一阶常微分方程：
$$\frac{d x}{d t}=\dot{x}=v(x, t)$$

解一阶常微分：
- 连续：积分
- 离散：欧拉方法
  - 用上一帧的状态更新下一帧
$$\begin{array}{l} \boldsymbol{x}^{t+\Delta t}=\boldsymbol{x}^{t}+\Delta t \dot{\boldsymbol{x}}^{t} \\ \dot{\boldsymbol{x}}^{t+\Delta t}=\dot{\boldsymbol{x}}^{t}+\Delta t \ddot{\boldsymbol{x}}^{t} \end{array}$$

欧拉方法的改进
- Midpoint method
- Adaptive step size
- 隐式欧拉方法
- 龙格库塔方法（Runge-Kutta Families）
- Position-Based / Verlet Integration（韦尔莱积分法）

## 刚体模拟

刚体不发生形变。

## 流体模拟

- 假设水由小刚体球体组成
- 假设水不可压缩，即密度不会变
- 所以只要某个地方的密度发生了变化，就应该通过改变粒子的位置来修正
- 你需要知道任何地方密度的梯度，梯度下降法

两个思路：
- 质点法（拉格朗日方法），以每个元素为单位模拟
- 网格法（欧拉方法），以空间为单位分割模拟

---

Advanced Image Synthesis（高级图像合成）
- Part 1: Advanced Light Transport
- Part 2: Advanced Appearance Modeling
- Part 3: Emerging Technology for Rendering
