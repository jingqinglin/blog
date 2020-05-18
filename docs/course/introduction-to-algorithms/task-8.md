算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

## 15.2-1

> Find an optimal parenthesization of a matrix-chain product whose sequence of dimensions is $\langle 5, 10, 3, 12, 5, 50, 6 \rangle$.
>
> 对矩阵规模序列 $\langle 5, 10, 3, 12, 5, 50, 6 \rangle$，求矩阵链最优括号化方案。

$$((5 \times 10)(10 \times 3))(((3 \times 12)(12 \times 5))((5 \times 50)(50 \times 6))).$$

## 15.2-2

> Give a recursive algorithm $\text{MATRIX-CHAIN-MULTIPLY}(A, s, i, j)$ that actually performs the optimal matrix-chain multiplication, given the sequence of matrices $\langle A_1, A_2, \ldots ,A_n \rangle$, the $s$ table computed by $\text{MATRIX-CHAIN-ORDER}$, and the indices $i$ and $j$. (The initial call would be $\text{MATRIX-CHAIN-MULTIPLY}(A, s, 1, n)$.)
>
> 设计递归算法 $\text{MATRIX-CHAIN-MULTIPLY}(A, s, i, j)$，实现矩阵链最优代价乘法计算的真正计算过程，其输入参数为矩阵序列 $\langle A_1, A_2, \ldots ,A_n \rangle$，$\text{MATRIX-CHAIN-ORDER}$ 得到的表 $s$，以及下标 $i$ 和 $j$。（初始调用应为 $\text{MATRIX-CHAIN-MULTIPLY}(A, s, 1, n)$。）


```cpp
MATRIX-CHAIN-MULTIPLY(A, s, i, j)
    if i == j
        return A[i]
    if i + 1 == j
        return A[i] * A[j]
    b = MATRIX-CHAIN-MULTIPLY(A, s, i, s[i, j])
    c = MATRIX-CHAIN-MULTIPLY(A, s, s[i, j] + 1, j)
    return b * c
```

## 15.3-1

> Which is a more efficient way to determine the optimal number of multiplications in a matrix-chain multiplication problem: enumerating all the ways of parenthesizing the product and computing the number of multiplications for each, or running $\text{RECURSIVE-MATRIX-CHAIN}$? Justify your answer.
>
> 对于矩阵链乘法问题，下面两种确定最优代价的方法哪种更高效？第一种方法是穷举所有可能的括号化方案，对每种方案计算乘法运算次数，第二种方法是运行 $\text{RECURSIVE-MATRIX-CHAIN}$。证明你的结论。


Running $\text{RECURSIVE-MATRIX-CHAIN}$ is asymptotically more efficient than enumerating all the ways of parenthesizing the product and computing the number of multiplications for each.

Consider the treatment of subproblems by each approach:

1. For each possible place to split the matrix chain, the enumeration approach finds all ways to parenthesize the left half, finds all ways to parenthesize the right half, and looks at all possible combinations of the left half with the right half. The amount of work to look at each combination of left and right half subproblem results is thus the product of the number of ways to parenthesize the left half and the number of ways to parenthesize the right half.

2. For each possible place to split the matrix chain, $\text{RECURSIVE-MATRIX-CHAIN}$ finds the best way to parenthesize the left half, finds the best way to parenthesize the right half, and combines just those two results. Thus the amount of work to combine the left and right half subproblem results is $O(1)$.

## 15.3-2

> Draw the recursion tree for the $\text{MERGE-SORT}$ procedure from Section 2.3.1 on an array of $16$ elements. Explain why memoization fails to speed up a good divide-and-conquer algorithm such as $\text{MERGE-SORT}$.
>
> 对一个有 16 个元素的数组，画出 2.3.1 节中 $\text{MERGE-SORT}$ 过程运行的递归调用树。解释备忘技术为什么对 $\text{MERGE-SORT}$ 这种分治算法无效。


Draw a recursion tree. The $\text{MERGE-SORT}$ procedure performs at most a single call to any pair of indices of the array that is being sorted. In other words, the subproblems do not overlap and therefore memoization will not improve the running time.