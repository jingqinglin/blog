算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

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