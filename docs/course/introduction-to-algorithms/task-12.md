算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

## 16.5-1

> Solve the instance of the scheduling problem given in Figure 16.7, but with each penalty $w_i$ replaced by $80 - w_i$.
>
> 对图 16-7 给出的调度问题的实例，将每个惩罚值 $w_i$ 替换为 $80 - w_i$，求解修改后的问题。


$$
\begin{array}{c|ccccccc}
a_i &  1 &  2 &  3 &  4 &  5 &  6 &  7 \\
\hline
d_i &  4 &  2 &  4 &  3 &  1 &  4 &  6 \\
w_i & 10 & 20 & 30 & 40 & 50 & 60 & 70
\end{array}
$$

We begin by just greedily constructing the matroid, adding the most costly to leave incomplete tasks first. So, we add tasks $7, 6, 5, 4, 3$. Then, in order to schedule tasks $1$ or $2$ we need to leave incomplete more important tasks. So, our final schedule is $\langle 5, 3, 4, 6, 7, 1, 2 \rangle$ to have a total penalty of only $w_1 + w_2 = 30$.

## 16.5-2

> Show how to use property 2 of Lemma 16.12 to determine in time $O(|A|)$ whether or not a given set $A$ of tasks is independent.
>
> 说明如何利用引理 16.12 的性质 2 在 $O(|A|)$ 时间内确定-一个给定任务集合 $A$ 是独立的。

Create an array $B$ of length $n$ containing zeros in each entry. For each element $a \in A$, add $1$ to $B[a.deadline]$. If $B[a.deadline] > a.deadline$, return that the set is not independent. Otherwise, continue. If successfully examine every element of $A$, return that the set is independent.
