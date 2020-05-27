算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

> [!NOTE]
> 我们可以按如下步骤设计贪心算法:
> 1. 将最优化问题转化为这样的形式：对其做出一次选择后，只剩下一个子问题需要求解。
> 2. 证明做出贪心选择后，原问题总是存在最优解，即贪心选择总是安全的。
> 3. 证明做出贪心选择后，剩余的子问题满足性质：其最优解与贪心选择组合即可得到原问题的最优解，这样就得到了最优子结构。

> [!TIP]
> 贪心算法的正确性证明不太会


## 16.1-2

> Suppose that instead of always selecting the first activity to finish, we instead select the last activity to start that is compatible with all previously selected activities. Describe how this approach is a greedy algorithm, and prove that it yields an optimal solution.
>
> 假定我们不再一直选择最早结束的活动，而是选择最晚开始的活动，前提仍然是与之前选出的所有活动均兼容。描述如何利用这方法设计贪心算法，并证明算法会产生最优解。


This becomes exactly the same as the original problem if we imagine time running in reverse, so it produces an optimal solution for essentially the same reasons. It is greedy because we make the best looking choice at each step.

## 16.2-4

> Professor Gekko has always dreamed of inline skating across North Dakota. He plans to cross the state on highway U.S. 2, which runs from Grand Forks, on the eastern border with Minnesota, to Williston, near the western border with Montana. The professor can carry two liters of water, and he can skate $m$ miles before running out of water. (Because North Dakota is relatively flat, the professor does not have to worry about drinking water at a greater rate on uphill sections than on flat or downhill sections.) The professor will start in Grand Forks with two full liters of water. His official North Dakota state map shows all the places along U.S. 2 at which he can refill his water and the distances between these locations.
>
> The professor's goal is to minimize the number of water stops along his route across the state. Give an efficient method by which he can determine which water stops he should make. Prove that your strategy yields an optimal solution, and give its running time.
>
> Gekko 教授一直梦想用直排轮滑的方式横穿北达科他州。他计划沿 U.S. 2 号高速公路横穿，这条高速公路从明尼苏达州东部边境的大福克斯市到靠近蒙大拿州西部边境的威利斯顿市。教授计划带两公升水，在喝光水之前能滑行 $m$ 英里（由于北达科他州地势相对平坦，教授无需担心在上坡路段喝水速度比平地或下坡路段快）。教授从大福克斯市出发时带整整两公升水。他携带的北达科他州官方地图显示了 U.S. 2 号公路上所有可以补充水的地点，以及这些地点间的距离。
>
> 教授的目标是最小化横穿途中补充水的次数。设计一个高效的方法，以帮助教授确定应该在哪些地点补充水。证明你的策略会生成最优解，分析其运行时间。


The greedy solution solves this problem optimally, where we maximize distance we can cover from a particular point such that there still exists a place to get water before we run out. The first stop is at the furthest point from the starting position which is less than or equal to $m$ miles away. The problem exhibits optimal substructure, since once we have chosen a first stopping point $p$, we solve the subproblem assuming we are starting at $p$. Combining these two plans yields an optimal solution for the usual cut-and-paste reasons. Now we must show that this greedy approach in fact yields a first stopping point which is contained in some optimal solution. Let $O$ be any optimal solution which has the professor stop at positions $o_1, o_2, \dots, o_k$. Let $g_1$ denote the furthest stopping point we can reach from the starting point. Then we may replace $o_1$ by $g_2$ to create a modified solution $G$, since $o_2 - o_1 < o_2 - g_1$. In other words, we can actually make it to the positions in $G$ without running out of water. Since $G$ has the same number of stops, we conclude that $g_1$ is contained in some optimal solution. Therefore the greedy strategy works.

## 16.3-3

> What is an optimal Huffman code for the following set of frequencies, based on  
> the first $8$ Fibonacci numbers?
>
> 如下所示，$8$ 个字符对应的出现频率是斐波那契数列的前 $8$ 个数，此频率集合的赫夫曼编码是怎样的？
>
> $$a:1 \quad b:1 \quad c:2 \quad d:3 \quad e:5 \quad f:8 \quad g:13 \quad h:21$$
>
> Can you generalize your answer to find the optimal code when the frequencies are the first $n$ Fibonacci numbers?
>
> 你能否推广你的结论，求频率集为前 $n$ 个斐波那契数的最优前缀码？


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


推广：

设前 $n$ 个斐波那契数为 $f(0) = 1, f(1) = 1, ... , f(n - 1) = f(n - 2) + f(n - 3)$，其对应的赫夫曼编码为 $H(0), H(1), ... , H(n - 1)$，则由上图可归纳出：

$$
\begin{array}{l}
H(n - 1) = 0 \\
H(k) \quad \ \ \ = H(k + 1) + 2^{n - k - 1} \quad (0 < k < n - 1) \\
H(0) \quad \ \ \ = H(1) + 1
\end{array}
$$