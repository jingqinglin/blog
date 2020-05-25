?> 0-1 背包问题的算法设计

## 实验要求
 
> 输入物品数 $n$，背包容量 $V$，输入 $n$ 个物品的重量、价值，任选**两个**算法实现最优解决 0-1 背包问题

## 实验分析

**问题描述**：有 $n$ 件物品，每件物品的重量为 $w[i]$，价值为 $c[i]$。现有一个容量为 $V$ 的背包，问如何选取物品放入背包，使得背包内物品的总价值最大。其中每种物品都只有 1 件。

### 动态规划

令 $dp[i][v]$ 表示前 $i$ 件**物品** $(1 ≤ i ≤ n, 0 ≤ v ≤ V)$ 恰好装入**容量**为 $V$ 的背包中所能获得的最大**价值**。

考虑对第 $i$ 件物品的选择策略，有两种策略:
1. 不放第 $i$ 件物品，那么问题转化为前 $i - 1$ 件物品恰好装入容量为 $V$ 的背包中所能获得的最大价值，也即 $dp[i- 1][v]$
2. 放第 $i$ 件物品，那么问题转化为前 $i - 1$ 件物品恰好装入容量为 $v - w[i]$ 的背包中所能获得的最大价值，也即 $dp[i - 1][v - w[i]] + c[i]$

可以得到**状态转移方程**：

$$
{dp}[{i}][{v}]=\max ({dp}[{i}-1][{v}], {dp}[{i}-1][{v}-{w}[{i}]]+{c}[{i}]) \quad(1 ≤ {i} ≤ {n}, {w}[{i}] ≤ {v} ≤ {V})
$$

边界：$dp[0][v] = 0 (0 \leq v \leq V)$ （即前 $0$ 件物品放入任何容量 $v$ 的背包中都只能获得价值 $0$）



代码如下：

```java
public static int dynamicProgramming(int[] w, int[] c, int V) {
    int n = w.length;
    int[][] dp = new int[n + 1][V + 1];
    for (int i = 1; i <= n; i++) {
        for (int v = w[i - 1]; v <= V; v++) {
            dp[i][v] = Math.max(dp[i - 1][v], dp[i - 1][v - w[i - 1]] + c[i - 1]);
        }
    }
    return dp[n][V];
}
```

空间优化后：（从大到小枚举）

$$
{dp}[{v}]=\max ({dp}[{v}], {dp}[{v}-{w}[{i}]]+{c}[{i}]) \quad(1 ≤ {i} ≤ {n}, {V} ≥ {v} ≥ {w}[{i}])
$$

代码如下：

```java
public static int optimizedDynamicProgramming(int[] w, int[] c, int V) {
    int n = w.length;
    int[] dp = new int[V + 1];
    for (int i = 1; i <= n; i++) {
        for (int v = V; v >= w[i - 1]; v--) {
            dp[v] = Math.max(dp[v], dp[v - w[i - 1]] + c[i - 1]);
        }
    }
    return dp[V];
}
```


### 回溯 + 剪枝

回溯（无剪枝）实质上就是枚举，对于一件物品，有放进背包和不放两种选择。分别对应 DFS 的左子树和右子树，代码如下：

```java
private static int maxValue;
public static int recursion(int[] w, int[] c, int V) {
    int n = w.length;
    maxValue = Integer.MIN_VALUE;
    backtracking(w, c, V, n, 0, 0, 0);
    return maxValue;
}
private static void backtracking(int[] w, int[] c, int V, int n, int index, int volumn, int value) {
    if (volumn > V) {
        return;
    }
    maxValue = Math.max(maxValue, value);
    if (index == n) {
        return;
    }
    volumn += w[index];
    value += c[index];
    backtracking(w, c, V, n, index + 1, volumn, value);
    volumn -= w[index];
    value -= c[index];
    backtracking(w, c, V, n, index + 1, volumn, value);
}
```

由于每件物品都有两种选择，因此 $n$ 件物品就有 $2^n$ 种情况。那么回溯法的时间复杂度就是 $O(2^n)$，指数级的时间复杂度对于一个算法来说是糟糕的。

因此我们考虑为 DFS 剪枝。可以将 DFS 过程中选择物品 $i$ 装入的步骤视为遍历左子树，不选择视为遍历右子树。那么根据上述代码可以看出，在遍历左子树的过程中，如果出现了不能再装入下一物品的情况，就需要去遍历右子树。

但是，如果剩余最大可容纳的价值<sup>[1]</sup>比当前最优解还要的小的话，那么右子树是完全没有必要去遍历，可以对其进行剪枝。

<font size="2">注<sup>[1]</sup>：为了计算*剩余最大可容纳价值*，我们需要先将 $w[i]$ 和 $c[i]$ 按照单位重量的价值排序（降序）。那么计算*剩余最大可容纳价值*时，只需按价重比降序将物品塞入背包即可。如果塞到最后，剩余容量大于 $0$ 且小于当前物品的重量，那么按照单位重量的价值乘以剩余容量填满背包，这一步骤“切割”了物品，但计算*剩余最大可容纳价值*只是用来判断是否需要剪枝的，并不会影响最优解，因此可能需要切割物品来得到理想化的*剩余最大可容纳价值*，以防误剪枝。</font>

回溯 + 剪枝代码如下：

```java
private static int maxValue;
public static int optimizedRecursion(int[] w, int[] c, int V) {
    int n = w.length;
    maxValue = Integer.MIN_VALUE;

    // 按单位重量的价值排序，以便剪枝
    int[][] cw = new int[n][2];
    for (int i = 0; i < n; i++) {
        cw[i][0] = c[i];
        cw[i][1] = w[i];
    }
    Arrays.sort(cw, (o1, o2) -> o2[0] * o1[1] - o1[0] * o2[1]);
    for (int i = 0; i < n; i++) {
        c[i] = cw[i][0];
        w[i] = cw[i][1];
    }

    optimizedBacktracking(w, c, V, n, 0, 0, 0);
    return maxValue;
}
private static void optimizedBacktracking(int[] w, int[] c, int V, int n, int index, int volumn, int value) {
    if (volumn > V) {
        return;
    }
    maxValue = Math.max(maxValue, value);
    if (index == n) {
        return;
    }
    volumn += w[index];
    value += c[index];
    backtracking(w, c, V, n, index + 1, volumn, value);
    volumn -= w[index];
    value -= c[index];
    // 若 当前背包价值 + 剩余最大可容纳的价值 > 当前最优解，则继续递归右子树
    if (bound(w, c, V, n, index + 1, volumn, value) > maxValue) {
        backtracking(w, c, V, n, index + 1, volumn, value);
    }
}
/**
 * 剪枝函数
 */
private static double bound(int[] w, int[] c, int V, int n, int index, int volumn, int value) {
    // 剩余背包容量
    double leftV = V - volumn;
    double doubleValue = value;
    // 按单位重量的价值递减，将物品装入背包，直到放不下为止，再把放不下的物品的一部分装入
    while (index < n && w[index] <= leftV) {
        leftV -= w[index];
        doubleValue += c[index];
        index++;
    }
    // 若背包没满（背包剩余容量小于当前物品的重量），按比例把当前物品的一部分装入，使 leftV = 0
    if (index < n) {
        doubleValue = c[index] * 1.0 / w[index] * leftV;
    }
    return doubleValue;
}
```

## 复杂度分析

从两层 for 循环可以看出动态规划的时间复杂度为 $O(nV)$。而回溯的时间复杂度为 $O(2^n)$，虽然剪枝会修剪掉部分情况，但不影响数量级。

运行以下测试用例：

```java
int[] w = new int[]{71, 34, 82, 23, 1, 88, 12, 57, 10, 68, 5, 33, 37, 69, 98, 24, 26, 83, 16, 26, 18, 43, 52, 7122, 65, 68, 8, 40, 40, 24, 72, 16, 34, 10};
int[] c = new int[]{26, 59, 30, 19, 66, 85, 94, 8, 3, 44, 5, 1, 41, 82, 76, 1, 12, 81, 73, 32, 74, 54, 62, 41, 1910, 65, 53, 56, 53, 70, 66, 58, 22, 72};
int V = 350;
```

各方法的运行时间如下：

```
881
动态规划运行时间：0ms
881
回溯运行时间：1178ms
881
回溯 + 剪枝运行时间：769ms
```

完整代码：https://paste.ubuntu.com/p/t9wkCHYtqZ