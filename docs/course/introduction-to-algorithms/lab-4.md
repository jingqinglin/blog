?> 贪心算法实现最佳任务调度实验

## 实验要求
 
> 实现一个任务调度问题（16.5 节）：在单处理器上具有期限和惩罚的单位时间任务调度。
> 
> 1. 实现这个问题的贪心算法，并写出流程图或者伪代码
> 2. 将每个 $w_i$ 替换为 $\max(w_1,w_2, ..., w_n) - w_i$ 运行算法、比较并分析结果
> <center>
> 
> <font size="4">任务</font>
> 
> | $a_i$ | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
> | ----- | --- | --- | --- | --- | --- | --- | --- |
> | $d_i$ | 4   | 2   | 4   | 3   | 1   | 4   | 6   |
> | $w_i$ | 70  | 60  | 50  | 40  | 30  | 20  | 10  |
> 
> <font size="2">单处理器上带截止时间和惩罚的单位时间任务调度问题的一个实例</font>
> 
> </center>

## 实验分析

### 调度问题简述

**单处理器上带截止时间和惩罚的单位时间任务调度问题**有如下输入：

- $n$ 个单位时间任务的集合 $S = {a_1, a_2, ..., a_n}$
- $n$ 个整数截止时间 $d_1, d_2, ..., d_n$，每个 $d_i$ 满足 $1 \leq d_i \leq n$，我们期望任务 $a_i$ 在时间 $d_i$ 之前完成
- $n$ 个非负权重或惩罚 $w_1, w_2, ..., w_n$，若任务 $a_i$ 在时间 $d_i$ 之前没有完成，我们就会受到 $w_i$ 这么多的惩罚，如果任务在截止时间前完成，则不会受到惩罚

我们希望找到 $S$ 的一个调度方案，能最小化超过截止时间导致的惩罚总和。

### 解题思路

> 问题 1. 实现这个问题的贪心算法，并写出流程图或者伪代码

对于一个给定的 $S$，在截止时间之前完成的任务称为**提前任务**，在截止时间之后完成的任务称为**延迟任务**。

对于任意调度方案，可以将其调整成**提前优先形式**，即其中所有提前任务先于延迟任务。类似地，还可将任意的调度方案调整成为**规范形式**，其中提前任务先于延迟任务，且提前任务依其截止时间的增序排列。

这样，寻找最优调度方案的问题就归结为寻找提前任务子集 $A$ 的问题。确定 $A$ 之后，我们可以将 $A$ 中元素按截止时间递增的顺序排列，然后将延迟任务（即 $S - A$）以任意顺序排列其后，就得到了最优调度方案的规范形式。


代码如下：

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class TaskScheduling {
    public static int greedy(int[] d, int[] w) {
        int n = d.length;
        int punishment = 0;
        // 提前任务子集（按截止时间递增）
        List<Integer> A = new ArrayList<>();
        A.add(0);

        for (int i = 1; i < n; i++) {
            // insertPos 为任务 i 要插入的位置
            int insertPos = A.size();
            while (insertPos > 0 &&
                    d[A.get(insertPos - 1)] > d[i] &&
                    // 若「提前任务子集」中 insertPos 位置任务的 deadline 等于 insertPos，
                    // 说明这个任务不能被往后移了
                    d[A.get(insertPos - 1)] != insertPos) {
                insertPos--;
            }
            // 若 deadline > 插入位置，则插入「提前任务子集」
            if (d[i] > insertPos) {
                A.add(insertPos, i);
            } else {
                // 若被舍弃，加上惩罚时间
                punishment += w[i];
            }
        }
        return punishment;
    }

    public static void main(String[] args) {
        int[] d = new int[]{4, 2, 4, 3, 1, 4, 6};
        int[] w = new int[]{70, 60, 50, 40, 30, 20, 10};

        // 若 w 非递减，对其排序
        int[][] wd = new int[d.length][2];
        for (int i = 0; i < wd.length; i++) {
            wd[i][0] = w[i];
            wd[i][1] = d[i];
        }
        Arrays.sort(wd, ((o1, o2) -> o2[0] - o1[0]));
        for (int i = 0; i < wd.length; i++) {
            w[i] = wd[i][0];
            d[i] = wd[i][1];
        }

        System.out.println(greedy(d, w));
    }
}
```

运行代码，输出如下：`50`，其中任务 $a_5$ 和 $a_6$ 受到了惩罚。

> 问题 2. 将每个 $w_i$ 替换为 $\max(w_1,w_2, ..., w_n) - w_i$ 运行算法、比较并分析结果

对 main 方法进行修改，如下。

```java
public class TaskScheduling {
    public static int greedy(int[] d, int[] w) {
        // ...
    }

    public static void main(String[] args) {
        int[] d = new int[]{4, 2, 4, 3, 1, 4, 6};
        int[] w = new int[]{70, 60, 50, 40, 30, 20, 10};

        // 修改权重数组
        int maxWi = 0;
        for (int i = 0; i < w.length; i++) {
            maxWi = Math.max(maxWi, w[i]);
        }
        for (int i = 0; i < w.length; i++) {
            w[i] = maxWi - w[i];
        }

        // ...
    }
}
```

运行得到结果：`10`，其中任务 $a_1$ 和 $a_2$ 受到了惩罚。

## 复杂度分析

时间复杂度是 $O(nlogn + nf(n))$。其中 $O(nlogn)$ 是对权重数组进行排序的时间复杂度，$f(n)$ 是用于检测任务子集 $A$ 的独立性所需的时间，为 $O(n)$。因此，整个算法的时间复杂度是 $O(n^2)$。