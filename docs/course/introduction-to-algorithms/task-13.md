算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

> [!NOTE]
> 本次作业涉及摊还分析章节知识，摊还分析有常用的三种技术：聚合分析、核算法和势能法（中文教材 P258 有概括）。👉 来自博客园的总结[部分一](https://www.cnblogs.com/dongkuo/p/5824007.html)、[部分二](https://www.cnblogs.com/dongkuo/p/5826852.html)。

## 17.1-1

> If the set of stack operations included a $\text{MULTIPUSH}$ operation, which pushses $k$ items onto the stack, would the $O(1)$ bound on the amortized cost of stack operations continue to hold?
>
> 如果栈操作包括 $\text{MULTIPUSH}$ 操作，它将 $k$ 个数据项压人栈中，那么栈操作的摊还代价的界还是 $O(1)$ 吗？


No. The time complexity of such a series of operations depends on the number of pushes (pops vise versa) could be made. Since one $\text{MULTIPUSH}$ needs $\Theta(k)$ time, performing $n$ $\text{MULTIPUSH}$ operations, each with $k$ elements, would take $\Theta(kn)$ time, leading to amortized cost of $\Theta(k)$.

## 17.1-2

> Show that if a $\text{DECREMENT}$ operatoin were included in the $k$-bit counter example, $n$ operations could cost as much as $\Theta(nk)$ time.
>
> 证明：如果 $k$ 位计数器的例子中允许 $\text{DECREMENT}$ 操作，那么 $n$ 个操作的运行时间可能达到 $\Theta(nk)$。

The logarithmic bit flipping predicate does not hold, and indeed a sequence of events could consist of the incrementation of all $1$s and decrementation of all $0$s; yielding $\Theta(nk)$.

> [!NOTE]
> 当计数器值为 $0$ 时，执行 $\text{DECREMENT}$；计数器值为 $2^k - 1$ 时，执行 $\text{INCREMENT}$ 操作...

## 17.2-1

> Suppose we perform a sequence of stack operations on a stack whose size never exceeds $k$. After every $k$ operations, we make a copy of the entire stack for backup purposes. Show that the cost of $n$ stack operations, including copying the stack, is $O(n)$ by assigning suitable amortized costs to the various stack operations.
>
> 假定对一个规模永远不会超过 $k$ 的栈执行一个栈操作序列。 执行 $k$ 个操作后，我们复制整个栈来进行备份。通过为不同的栈操作赋予适合的摊还代价，证明：$n$ 个栈操作（包括复制栈）的代价为 $O(n)$。


For every stack operation, we charge twice.

- First, we charge the actual cost of the stack operation.
- Second, we charge the cost of copying an element later on.

Since we have the size of the stack never exceed $k$, and there are always $k$ operations between backups, we always overpay by at least enough. Therefore, the amortized cost of the operation is constant, and the cost of the $n$ operation is $O(n)$.

> [!NOTE]
> 我们假设在 $k$ 个 $\text{PUSH}$ 和 $\text{POP}$ 操作后会自动调用 $\text{COPY}$ 操作。  
> 我们用 $1$ 美元支付 $\text{PUSH}$ 操作的实际代价，将剩余的 $1$ 美元存为信用（共缴费 $2$ 美元）；$\text{POP}$ 操作的缴费情况和 $\text{PUSH}$ 操作相同；$\text{COPY}$ 操作无需缴费。因为堆栈大小不超过 $k$，所以 $\text{COPY}$ 操作的实际代价最多为 $k$。由于在两个连续的 $\text{COPY}$ 操作之间有 $k$ 个 $\text{PUSH}$ 和 $\text{POP}$ 操作，因此在 $\text{COPY}$ 发生时，$\text{PUSH}$ 和 $\text{POP}$ 上存储了 $k$ 的信用，任何时刻的信用值是非负的。因此，总实际代价的上界为总摊还代价，即为 $O(n)$。

## 17.3-1

> Suppose we have a potential function $\Phi$ such that $\Phi(D_i) \ge \Phi(D_0)$ for all $i$, but $\Phi(D_0) \ne 0$. Show that there exists a potential fuction $\Phi'$ such that $\Phi'(D_0) = 0$, $\Phi'(D_i) \ge 0$ for all $i \ge 1$, and the amortized costs using $\Phi'$ are the same as the amortized costs using $\Phi$.
>
> 假定有势函数 $\Phi$，对所有 $i$ 满足 $\Phi(D_i) \ge \Phi(D_0)$，但 $\Phi(D_0) \ne 0$。证明：存在势函数 $\Phi'$，使得 $\Phi'(D_i) = 0$，对所有 $i \ge 1$ 满足 $\Phi'(D_i) \ge 0$，且使用 $\Phi'$ 的摊还代价与使用 $\Phi$ 的摊还代价相同。


Define the potential function $\Phi'(D_i) = \Phi(D_i) - \Phi(D_0)$ for all $i \ge 1$.

Then

$$\Phi'(D_0) = \Phi(D_0) - \Phi(D_0) = 0,$$

and

$$\Phi'(D_i) = \Phi(D_i) - \Phi(D_0) \ge 0.$$

The amortized cost is

$$
\begin{aligned}
\hat c_i' & = c_i + \Phi'(D_i) - \Phi'(D_{i - 1}) \\
          & = c_i + (\Phi(D_i) - \Phi(D_0)) - (\Phi(D_{i - 1}) - \Phi(D_0)) \\
          & = c_i + \Phi(D_i) - \Phi(D_{i - 1}) \\
          & = \hat c_i.
\end{aligned}
$$

## 17.3-3

> Consider an ordinary binary min-heap data structure with $n$ elements supporting the instructions $\text{INSERT}$ and $\text{EXTRACT-MIN}$ in $O(\lg n)$ worst-case time. Give a potential function $\Phi$ such that the amortized cost of $\text{INSERT}$ is $O(\lg n)$ and the amortized cost of $\text{EXTRACT-MIN}$ is $O(1)$, and show that it works.
>
> 考虑一个包含 $n$ 个元素的普通二叉最小堆数据结构，它支持 $\text{INSERT}$ 和 $\text{EXTRACT-MIN}$ 操作，最坏情况时间均为 $O(\lg n)$。给出一个势函数 $\Phi$，使得 $\text{INSERT}$ 操作的摊还代价为 $O(\lg n)$，而 $\text{EXTRACT-MIN}$ 操作的摊还代价为 $O(1)$，证明它是正确的。

Make the potential function be equal to $\sum_{i = 1}^n \lg i$ where $n$ is the size of the min-heap. Then, there is still a cost of $O(\lg n)$ to $\text{INSERT}$, since only an amount of amortization that is $\lg n$ was spent to increase the size of the heap by $1$.

However, the amortized cost of $\text{EXTRACT-MIN}$ is $0$, as all its actual cost is compensated.

## 17.3-4

> What is the total cost of executing $n$ of the stack operations $\text{PUSH}$, $\text{POP}$, and $\text{MULTIPOP}$, assuming that the stack begins with $s_0$ objects and finishes with $s_n$ objects?
>
> 执行 $n$ 个 $\text{PUSH}$、$\text{POP}$ 和 $\text{MULTIPOP}$ 栈操作的总代价是多少？假定初始时栈中包含 $s_0$ 个对象，结束后包含 $s_n$ 个对象。

Let $\Phi$ be the potential function that returns the number of elements in the stack. We know that for this potential function, we have amortized cost $2$ for $\text{PUSH}$ operation and amortized cost $0$ for $\text{POP}$ and $\text{MULTIPOP}$ operations.

The total amortized cost is

$$\sum_{i = 1}^n \hat c_i = \sum_{i = 1}^n c_i + \Phi(D_n) - \Phi(D_0).$$

Using the potential function and the known amortized costs, we can rewrite the equation as

$$
\begin{aligned}
\sum_{i = 1}^n c_i
    & = \sum_{i = 1}^n \hat c_i + \Phi(D_0) - \Phi(D_n) \\
    & = \sum_{i = 1}^n \hat c_i + s_0 - s_n \\
    & \le 2n + s_0 - s_n,
\end{aligned}
$$

which gives us the total cost of $O(n + (s_0 - s_n))$. If $s_n \ge s_0$, then this equals to $O(n)$, that is, if the stack grows, then the work done is limited by the number of operations.

(Note that it does not matter here that the potential may go below the starting potential. The condition $\Phi(D_n) \ge \Phi(D_0)$ for all $n$ is only required to have $\sum_{i = 1}^n \hat c_i \ge \sum_{i = 1}^n c_i$, but we do not need for that to hold in this application.)

## 17.4-2

> Show that if $\alpha_{i - 1} \ge 1 / 2$ and the $i$th operation on a dynamic table is $\text{TABLE-DELETE}$, then the amortized cost of the operation with respect to the potential function $\text{(17.6)}$ is bounded above by a constant.
>
> 证明：如果动态表的 $\alpha_{i - 1} \ge 1 / 2$ 且第 $i$ 个操作是 $\text{TABLE-DELETE}$，那么用势函数公式 $\text{(17.6)}$ 定义的操作的摊还代价的上界是一个常数。

If $\alpha_{i - 1} \ge 1 / 2$, $\text{TABLE-DELETE}$ cannot **_contract_**, so $c_i = 1$ and $size_i = size_{i - 1}$.

- **Case 1:** if $\alpha_{i - 1} \ge 1 / 2$,

    $$
    \begin{aligned}
    \hat c_i & = c_i + \Phi_i - \Phi_{i - 1} \\
             & = 1 + (2 \cdot num_i - size_i) - (2 \cdot num_{i - 1} - size_{i - 1}) \\
             & = 1 + (2 \cdot (num_{i - 1} - 1) - size_{i - 1}) - (2 \cdot num_{i - 1} - size_{i - 1}) \\
             & = -1.
    \end{aligned}
    $$

- **Case 2:** if $\alpha_i < 1 / 2$,

    $$
    \begin{aligned}
    \hat c_i & =   c_i + \Phi_i - \Phi_{i - 1} \\
             & =   1 + (size_i / 2 - num_i) - (2 \cdot num_{i - 1} - size_{i - 1}) \\
             & =   1 + (size_{i - 1} / 2 - (num_{i - 1} - 1)) - (2 \cdot num_{i - 1} - size_{i - 1}) \\
             & =   2 + \frac{3}{2} size_{i - 1} - 3 \cdot num_{i - 1} \\
             & =   2 + \frac{3}{2} size_{i - 1} - 3\alpha_{i - 1} size_{i - 1} \\
             & \le 2 + \frac{3}{2} size_{i - 1} - \frac{3}{2} size_{i - 1} \\
             & =   2.
    \end{aligned}
    $$

## 17.4-3

> Suppose that instead of contracting a table by halving its size when its load factor drops below $1 / 4$, we contract it by multiplying its size by $2 / 3$ when its load factor drops below $1 / 3$. Using the potential function
>
> 假定我们改变表收缩的方式，不是当装载因子小于 $1 / 4$ 时将表规模减半，而是当装载因子小于 $1 / 3$ 时将表规模变为原来的 $2 / 3$。使用势函数
>
> $$\Phi(T) = | 2 \cdot T.num - T.size |,$$
>
> show that the amortized cost of a $\text{TABLE-DELETE}$ that uses this strategy is bounded above by a constant.
>
> 证明：使用此策略，$\text{TABLE-DELETE}$ 操作的摊还代价的上界是一个常数。


If $1 / 3 < \alpha_i \le 1 / 2$,

$$
\begin{aligned}
\hat c_i & = c_i + \Phi_i - \Phi_{i - 1} \\
         & = 1 + (size_i - 2 \cdot num_i) - (size_i - 2 \cdot (num_i + 1)) \\
         & = 3.
\end{aligned}
$$

If the $i$th operation does trigger a contraction,

$$
\begin{aligned}
\frac{1}{3} size_{i - 1} & = num_i + 1 \\
            size_{i - 1} & = 3 (num_i + 1) \\
            size_{i}     & = \frac{2}{3} size_{i - 1} = 2 (num_i + 1).
\end{aligned}
$$

$$
\begin{aligned}
\hat c_i & = c_i + \Phi_i - \Phi_{i - 1} \\
         & = (num_i + 1) + [2 \cdot (num_i + 1) - 2 \cdot num_i] - [3 \cdot (num_i + 1) - 2 \cdot (num_i + 1)] \\
         & = 2.
\end{aligned}
$$