这节的目的是让物体动起来。我们可以尝试着在每一帧改变物体的顶点并且重配置缓冲区从而使它们移动，但这太繁琐了，而且会消耗很多的处理时间。我们现在有一个更好的解决方案，使用（多个）矩阵对象可以更好的变换一个物体。

> 关键词：向量、矩阵

## 向量

### 点积

两个向量 $\vec{a}=\left[a_{1}, a_{2}, \cdots, a_{n}\right]$ 和 $\vec{b}=\left[b_{1}, b_{2}, \cdots, b_{n}\right]$ 的点积定义为:

$\vec{a} \cdot \vec{b}=\sum_{i=1}^{n} a_{i} b_{i}=a_{1} b_{1}+a_{2} b_{2}+\cdots+a_{n} b_{n}$

在欧几里得空间中，点积可以直观地定义为：

$\vec{a} \cdot \vec{b}=|\vec{a}||\vec{b}| \cos \theta$

![](_images/learnopengl-getting-started-20.png ':class=resizedImage')

### 叉积

叉积 $\vec{a} \times \vec{b}$ 都垂直的向量 $\vec{c}$ 。其方向由右手定则决定，模长等于以两个向量为边的平行四边形的面积。

![](_images/learnopengl-getting-started-21.png ':class=resizedImage')

叉积可以定义为：

$\vec{a} \times \vec{b}=|\vec{a}||\vec{b}| \cos(\theta) \vec{n}$

#### 计算

对于叉积的计算，有两种表示方式：

##### 坐标表示

向量 $\vec{u}$ 和 $\vec{v}$ 可以定义为平行于基向量的三个正交元素之和：

$
\begin{array}{l}
\vec{u}=u_{1} \vec{i}+u_{2} \vec{j}+u_{3} \vec{k} \\
\vec{v}=v_{1} \vec{i}+v_{2} \vec{j}+v_{3} \vec{k}
\end{array}
$

两者的叉积 $\vec{u} \times \vec{v}$ 可以根据分配律展开：

$
\begin{aligned}
\vec{u} \times \vec{v} & =\left(u_{1} \vec{i}+u_{2} \vec{j}+u_{3} \vec{k}\right) \times\left(v_{1} \vec{i}+v_{2} \vec{j}+v_{3} \vec{k}\right)\\
& =u_{1} v_{1}(\vec{i} \times \vec{i})+u_{1} v_{2}(\vec{i} \times \vec{j})+u_{1} v_{3}(\vec{i} \times \vec{k})+\\
& \quad \ u_{2} v_{1}(\vec{j} \times \vec{i})+u_{2} v_{2}(\vec{j} \times \vec{j})+u_{2} v_{3}(\vec{j} \times \vec{k})+\\
& \quad \ u_{3} v_{1}(\vec{k} \times \vec{i})+u_{3} v_{2}(\vec{k} \times \vec{j})+u_{3} v_{3}(\vec{k} \times \vec{k})\\
& =\left(u_{2} v_{3}-u_{3} v_{2}\right) \vec{i}+\left(u_{3} v_{1}-u_{1} v_{3}\right) \vec{j}+\left(u_{1} v_{2}-u_{2} v_{1}\right) \vec{k}
\end{aligned}
$


##### 行列式表示

叉积可以表达为这样的行列式：

$
\vec{u} \times \vec{v}=\left|\begin{array}{ccc}
\vec{i} & \vec{j} & \vec{k} \\
u_{1} & u_{2} & u_{3} \\
v_{1} & v_{2} & v_{3}
\end{array}\right|
$

使用拉普拉斯展开可以沿第一行展开为：

$
\begin{aligned}
\vec{u} \times \vec{v} &=\left|\begin{array}{ll}
u_{2} & u_{3} \\
v_{2} & v_{3}
\end{array}\right| \vec{i}-\left|\begin{array}{ll}
u_{1} & u_{3} \\
v_{1} & v_{3}
\end{array}\right| \vec{j}+\left|\begin{array}{ll}
u_{1} & u_{2} \\
v_{1} & v_{2}
\end{array}\right| \vec{k} \\
&=\left(u_{2} v_{3}-u_{3} v_{2}\right) \vec{i}-\left(u_{1} v_{3}-u_{3} v_{1}\right) \vec{j}+\left(u_{1} v_{2}-u_{2} v_{1}\right) \vec{k}
\end{aligned}
$

## 矩阵