算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

> [!NOTE]
> 本次作业主要涉及**二项堆**（Binomial Heap，第三版中移入思考题）和**斐波那契堆**，它们都是用于实现有限队列的数据结构。基于不同的数据结构，优先队列的各个操作的时间复杂度的关系是：
> 
> ![](_images/task-14-1.png ':class=resizedImage')<font size="2" color="#8590a6">图片来自[CSDN](https://blog.csdn.net/jmh1996/article/details/83662953)</font>
>
> 斐波那契堆看[这篇](https://www.cnblogs.com/dongkuo/p/7623882.html)和[这篇](https://www.cnblogs.com/junyuhuang/p/4463758.html)（后一篇“合并”操作有误，但“减值”操作比较详细），二项堆看[这篇](https://blog.csdn.net/jmh1996/article/details/83688059)。

> [!NOTE|label:二项树（Binomial Tree）和二项堆（Binomial Heap）]
> 二项树递归定义如下：
> - 度数为 0 的二项树只包含一个结点
> - 度数为 k 的二项树有一个根结点，根结点下有 $k$ 个子女，每个子女分别是度数分别为 $k-1, k-2, \ldots, 2, 1, 0$ 的二项树的根
>
> <center>
>
> ![](_images/task-14-2.svg ':class=resizedImage')
>
> </center>
> <center><font size="2" color="#8590a6">二项树（从左至右度数分别为 0 至 3）</font></center>
>
> **二项堆**是指满足以下性质的二项树的集合：
> - 每棵二项树都满足最小堆性质，即结点关键字大于等于其父结点的值
> - 具有度数 k 的二项树有 0 个或 1 个
>
> <center>
>
> ![](_images/task-14-3.svg ':class=resizedImage')
>
> </center>
> <center><font size="2" color="#8590a6">一个含 13 个结点的二项堆</font></center>

## 19.2-1

> Show the Fibonacci heap that results from calling $\text{FIB-HEAP-EXTRACT-MIN}$ on the Fibonacci heap shown in Figure 19.4(m).
>
> ![](_images/task-14-5.png ':class=resizedImage')
>
> 给出图 19-4(m) 中的斐波那契堆调用 $\text{FIB-HEAP-EXTRACT-MIN}$ 后得到的斐波那契堆。

删除最小结点，并把它的子结点加入堆的根表。合并相同度的根结点，使任何根结点的度不相等。图略。

## 思考题 19-2

> **d.** Suppose that we were to implement only the mergeable-heap operations on a Fibonacci heap (i.e., we do not implement the $\text{DECREASE-KEY}$ or $\text{DELETE}$ operations). How would the trees in a Fibonacci heap resemble those in a binomial heap? How would they differ? Show that the maximum degree in an $n$-node Fibonacci heap would be at most $\lfloor \lg n\rfloor$.
>
> **d.** 假定仅仅要实现在一个斐波那契堆上的可合并堆操作（即并不实现 $\text{DECREASE-KEY}$ 和 $\text{DELETE}$ 操作）。斐波那契堆中的树与二项堆中的树有何相似之处？有什么区别？证明在一个 $n$ 个结点的斐波那契堆中最大度数最多为 $\lfloor \lg n\rfloor$。

The Fibonacci heap will look like a binomial heap, except that multiple copies of a given binomial tree will be allowed. Since the only trees which will appear are binomial trees and $B_k$ has $2k$ nodes, we must have $2k \le n$, which implies $k \le \lfloor \lg n \rfloor$. Since the largest root of any binomial tree occurs at the root, and on $B_k$ it is degree $k$, this also bounds the largest degree of a node.
