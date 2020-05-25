算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

## 16.1-2

> Suppose that instead of always selecting the first activity to finish, we instead select the last activity to start that is compatible with all previously selected activities. Describe how this approach is a greedy algorithm, and prove that it yields an optimal solution.
>
> 假定我们不再一直选择最早结束的活动，而是选择最晚开始的活动，前提仍然是与之前选出的所有活动均兼容。描述如何利用这方法设计贪心算法，并证明算法会产生最优解。

This becomes exactly the same as the original problem if we imagine time running in reverse, so it produces an optimal solution for essentially the same reasons. It is greedy because we make the best looking choice at each step.

## 16.2-4

> Professor Gekko has always dreamed of inline skating across North Dakota. He plans to cross the state on highway U.S. 2, which runs from Grand Forks, on the eastern border with Minnesota, to Williston, near the western border with Montana. The professor can carry two liters of water, and he can skate $m$ miles before running out of water. (Because North Dakota is relatively flat, the professor does not have to worry about drinking water at a greater rate on uphill sections than on flat or downhill sections.) The professor will start in Grand Forks with two full liters of water. His official North Dakota state map shows all the places along U.S. 2 at which he can refill his water and the distances between these locations.
>
> The professor's goal is to minimize the number of water stops along his route across the state. Give an efficient method by which he can determine which water stops he should make. Prove that your strategy yields an optimal solution, and give its running time.

The greedy solution solves this problem optimally, where we maximize distance we can cover from a particular point such that there still exists a place to get water before we run out. The first stop is at the furthest point from the starting position which is less than or equal to $m$ miles away. The problem exhibits optimal substructure, since once we have chosen a first stopping point $p$, we solve the subproblem assuming we are starting at $p$. Combining these two plans yields an optimal solution for the usual cut-and-paste reasons. Now we must show that this greedy approach in fact yields a first stopping point which is contained in some optimal solution. Let $O$ be any optimal solution which has the professor stop at positions $o_1, o_2, \dots, o_k$. Let $g_1$ denote the furthest stopping point we can reach from the starting point. Then we may replace $o_1$ by $g_2$ to create a modified solution $G$, since $o_2 - o_1 < o_2 - g_1$. In other words, we can actually make it to the positions in $G$ without running out of water. Since $G$ has the same number of stops, we conclude that $g_1$ is contained in some optimal solution. Therefore the greedy strategy works.

## 16.3-3

> What is an optimal Huffman code for the following set of frequencies, based on  
> the first $8$ Fibonacci numbers?
>
> $$a:1 \quad b:1 \quad c:2 \quad d:3 \quad e:5 \quad f:8 \quad g:13 \quad h:21$$
>
> Can you generalize your answer to find the optimal code when the frequencies are the first $n$ Fibonacci numbers?

$$
\begin{array}{c|l}
a & 1111111 \\\\
b & 1111110 \\\\
c & 111110 \\\\
d & 11110 \\\\
e & 1110 \\\\
f & 110 \\\\
g & 10 \\\\
h & 0
\end{array}
$$