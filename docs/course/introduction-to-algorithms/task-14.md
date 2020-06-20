算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

> [!NOTE]
> 本次作业主要涉及**二项堆**（Binomial Heap，第三版中移入思考题）和**斐波那契堆**，它们都是用于实现有限队列的数据结构。基于不同的数据结构，优先队列的各个操作的时间复杂度的关系是：
> 
> ![](_images/task-14-1.png ':class=image-80')<font size="2" color="#c0c0c0">图片来自[CSDN](https://blog.csdn.net/jmh1996/article/details/83662953)</font>


> [!NOTE|label:二项树（Binomial Tree）和二项堆（Binomial Heap）]
> 二项树递归定义如下：
> - 度数为 0 的二项树只包含一个结点
> - 度数为 k 的二项树有一个根结点，根结点下有 $k$ 个子女，每个子女分别是度数分别为 $k-1, k-2, \ldots, 2, 1, 0$ 的二项树的根
>
> <center>
>
> ![](_images/task-14-2.svg ':class=image-70')
>
> </center>
> <center><font size="2" color="#c0c0c0">二项树（从左至右度数分别为 0 至 3）</font></center>
>
> **二项堆**是指满足以下性质的二项树的集合：
> - 每棵二项树都满足最小堆性质，即结点关键字大于等于其父结点的值
> - 具有度数 k 的二项树有 0 个或 1 个
>
> <center>
>
> ![](_images/task-14-3.svg ':class=image-40')
>
> </center>
> <center><font size="2" color="#c0c0c0">一个含 13 个结点的二项堆</font></center>


