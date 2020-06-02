算法导论的作业答案摘自 [walkccc](https://walkccc.github.io/CLRS/)

## 16.3-5

> Prove that if we order the characters in an alphabet so that their frequencies are monotonically decreasing, then there exists an optimal code whose codeword lengths are monotonically increasing.
>
> 证明：如果我们将字母表中字符按频率单调递减排序，那么存在一个最优编码，其码字长度是单调递增的。


It were a contradiction to have an optimal tree whose frequencies and codewords were monotonically increasing in the strict sense; since, given $f(x_1) > \ldots > f(x_n) \wedge d_T(x_1) > \cdots > d_T(x_n)$, it follows that (where $n$ is odd):

$$
\begin{aligned}
& f(x_1)d_T(x_1) + \cdots + f(x_n)d_T(x_n) > f(x_1)d_T(x_n) + \cdots + f(x_n)d_T(x_1) > 0 \\
& f(x_1)(d_T(x_1) - d_T(x_n)) + \cdots + f(x_n)(d_T(x_n) - d_T(x_1)) > 0 \\
& f(x_1)(d_T(x_1) - d_T(x_n)) + \cdots + f(x_{\lfloor \frac{n}{2} - 1 \rfloor})(d_T(x_{\lfloor \frac{n}{2} \rfloor - 1}) - d_T(x_{\lfloor \frac{n}{2} \rfloor + 1})) \\
& > f(x_{\lfloor \frac{n}{2} + 1 \rfloor})(d_T(x_{\lfloor \frac{n}{2} \rfloor - 1}) - d_T(x_{\lfloor \frac{n}{2} \rfloor + 1}))+ \cdots + f(x_n)(d_T(x_1) - d_T(x_n)).
\end{aligned}
$$

That is, where $i$ and $j$ are the upper and lower median,
respectively; and $c_i = d_T(x_i) - d_T(x_{n - i + 1})$:

$$f(x_1)c_1 + \cdots + f(x_i)c_i > f(x_j)c_i + \cdots + f(x_n)c_1$$

since

$$
\begin{aligned}
f(x_i) & > f(x_{n - i + 1}) & 1 \le i \le \Big\lfloor \frac{n}{2} \Big\rfloor.
\end{aligned}
$$

## 16.4-1

> Show that $(S, \mathcal I_k)$ is a matroid, where $S$ is any finite set and $\mathcal I_k$ is the set of all subsets of $S$ of size at most $k$, where $k \le |S|$.
>
> 证明：若 $S$ 是任意一个有限集，$\mathcal I_k$ 是 $S$ 的所有规模不超过 $k$ 的子集的集合（$k \le |S|$），则 $(S, \mathcal I_k)$ 是一个拟阵。


The first condition that $S$ is a finite set is a given. To prove the second condition we assume that $k \ge 0$, this gets us that $\mathcal I_k$ is nonempty. Also, to prove the hereditary property, suppose $A \in \mathcal I_k$ this means that $|A| \le k$.
Then, if $B \subseteq A$, this means that $|B| \le |A| \le k$, so $B \in \mathcal I_k$. Lastly, we prove the exchange property by letting $A, B \in \mathcal I_k$ be such that $|A| < |B|$. Then, we can pick any element $x \in B \backslash A$, then,

$$|A \cup {x}| = |A| + 1 \le |B| \le k,$$

so, we can extend $A$ to $A \cup \{x\} \in \mathcal I_k$.