由于本节作业在第三版中无对应题目，以下均为第二版原题。

## 26.1-1

> Using the definition of a flow, prove that if $(u, v) \notin E$ and $(v, u) \notin E$ then $f(u, v) = f(v, u) = 0$.
>
> 利用流的定义，证明如果 $(u, v) \notin E$ 且 $(v, u) \notin E$，有 $f(u, v) = f(v, u) = 0$。

由流的定义可得，若 $(u, v) \notin E$，则 $c(u, v) = 0$。

由流的**容量限制**和**反对称性**得：$f(u, v) \leq c(u, v) = 0$，$f(u, v) = -f(v, u) = 0$，所以 $f(u, v) = f(v, u) = 0$。

## 26.1-2

> Prove that for any vertex $v$ other than the source or sink, the total positive flow entering $v$ must equal the total positive flow leaving $v$.
>
> 证明：对于任意非源点非汇点的顶点 $v$，进入 $v$ 的总正向流必定等于离开 $v$ 的总正向流。

**流守恒性**：对所有 $u \in V - \{s, t\}$，要求：$\sum\limits_{v \in V} f(u, v)=0$

定义进入顶点 $v$ 总的正网络流为：

$$\sum_{\substack{u \in V \\ f(u, v) > 0}} f(u, v)$$

定义离开顶点 $v$ 总的正网络流为：

$$\sum_{\substack{u \in V \\ f(u, v) < 0}} f(v, u)$$

因此，

$$
\begin{aligned}
\sum_{v \in V} f(u, v) & = 0 \\
                              & = \sum_{\substack{u \in V \\ f(u, v) > 0}} f(u, v) + \sum_{\substack{u \in V \\ f(u, v) < 0}} f(u, v) + 0 \\
                              & = \sum_{\substack{u \in V \\ f(u, v) > 0}} f(u, v) - \sum_{\substack{u \in V \\ f(u, v) < 0}} f(v, u)
\end{aligned}
$$

所以，

$$
\sum_{\substack{u \in V \\ f(u, v) > 0}} f(u, v) = \sum_{\substack{u \in V \\ f(u, v) < 0}} f(v, u)
$$

## 26.1-5

> For the flow network $G = (V, E)$ and flow $f$ shown in Figure 26.1(b), find a pair of subsets $X, Y \in V$ for which $f(X, Y) = −f(V − X, Y)$. Then, find a pair of subsets $X, Y \in V$ for which $f(X, Y) \ne −f(V − X, Y)$.
>
> 对于图 26-1b 所示的流网络 $G = (V, E)$ 和流 $f$,找出两个子集合 $X, Y \in V$，且满足 $f(X, Y) = −f(V − X, Y)$。再找出两个子集合 $X, Y \in V$，且满足 $f(X, Y) \ne −f(V − X, Y)$。
>
> ![](_images/task-15-1.png ':class=image-50')

1. $X = \{v_1, v_2\}, Y = \{v_3\}$，此时 $f(X, Y) = 12 - 4 = 8, f(V − X, Y) = 7 - 15 = -8$
2. $X = \{s\}, Y = \{t\}$，此时 $f(X, Y) = 8, f(V − X, Y) = 19$