算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

## 15.4-3

> Give a memoized version of $\text{LCS-LENGTH}$ that runs in $O(mn)$ time.
>
> 设计 $\text{LCS-LENGTH}$ 的带备忘的版本，运行时间为 $O(mn)$。

```cpp
MEMOIZED-LCS-LENGTH(X, Y, i, j)
    if c[i, j] > -1
        return c[i, j]
    if i == 0 or j == 0
        return c[i, j] = 0
    if x[i] == y[j]
        return c[i, j] = LCS-LENGTH(X, Y, i - 1, j - 1) + 1
    return c[i, j] = max(LCS-LENGTH(X, Y, i - 1, j), LCS-LENGTH(X, Y, i, j - 1))
```

## 15.5-2

> Determine the cost and structure of an optimal binary search tree for a set of $n = 7$ keys with the following probabilities:
>
> 若 $7$ 个关键字的概率如下所示，求其最优二叉搜索树的结构和代价。
>
> $$
> \begin{array}{c|cccccccc}
> i   & 0    & 1    & 2    & 3    & 4    & 5    & 6    & 7 \\\\
> \hline
> p_i &      & 0.04 & 0.06 & 0.08 & 0.02 & 0.10 & 0.12 & 0.14 \\\\
> q_i & 0.06 & 0.06 & 0.06 & 0.06 & 0.05 & 0.05 & 0.05 & 0.05
> \end{array}
> $$

Cost is $3.12$.


$$
\begin{aligned}
& k_5 \text{ is the root} \\
& k_2 \text{ is the left  child of } k_5 \\
& k_1 \text{ is the left  child of } k_2 \\
& d_0 \text{ is the left  child of } k_1 \\
& d_1 \text{ is the right child of } k_1 \\
& k_3 \text{ is the right child of } k_2 \\
& d_2 \text{ is the left  child of } k_3 \\
& k_4 \text{ is the right child of } k_3 \\
& d_3 \text{ is the left  child of } k_4 \\
& d_4 \text{ is the right child of } k_4 \\
& k_7 \text{ is the right child of } k_5 \\
& k_6 \text{ is the left  child of } k_7 \\
& d_5 \text{ is the left  child of } k_6 \\
& d_6 \text{ is the right child of } k_6 \\
& d_7 \text{ is the right child of } k_7
\end{aligned}
$$

## 15.5-3

> Suppose that instead of maintaining the table $w[i, j]$, we computed the value of $w(i, j)$ directly from equation $\text{(15.12)}$ in line 9 of $\text{OPTIMAL-BST}$ and used this computed value in line 11. How would this change affect the asymptotic running time of $\text{OPTIMAL-BST}$?
>
> 假设 $\text{OPTIMAL-BST}$ 不维护表 $w(i, j)$，而是在第 9 行利用公式 $\text{(15.12)}$ 直接计算 $w(i, j)$，然后在第 11 行使用此值。如此改动会对渐近时间复杂性有何影响？

Each of the $\Theta(n^2)$ values of $w[i, j]$ would require computing those two sums, both of which can be of size $O(n)$, so, the asymptotic runtime would increase to $O(n^3)$.