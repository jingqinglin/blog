力扣<a href="https://leetcode-cn.com/problemset/2020-04/" target="_blank">每日 1 题：4 月</a>（部分）。4 月的题难度较 3 月有所提升。

| 一                                                                                                                         | 二                                                                                                                                      | 三                                                                                                                                                | 四                                                                                                              | 五                                                                                                                         | 六                                                                                                                    | 日                                                                                                                |
| -------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| <font color=gray>30</font>                                                                                                 | <font color=gray>31</font>                                                                                                              | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings" target="_blank">1 ✅</a> | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/game-of-life" target="_blank">2 ✅</a>         | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/string-to-integer-atoi" target="_blank">3 ✅</a>          | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/trapping-rain-water" target="_blank">4 ✅</a>        | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/lfu-cache" target="_blank">5 ✅</a>              |
| <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/edit-distance" target="_blank">6 ✅</a>                   | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/rotate-matrix-lcci" target="_blank">7 ✅</a>                           | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof" target="_blank">8 ✅</a>                     | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/generate-parentheses" target="_blank">9 ✅</a> | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/reverse-words-in-a-string" target="_blank">10 ✅</a>      | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/super-egg-drop" target="_blank">11 ✅</a>            | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/intersection-lcci" target="_blank">12 ✅</a>     |
| <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/design-twitter" target="_blank">13 ✅</a>                 | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/add-two-numbers-ii" target="_blank">14 ✅</a>                          | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/01-matrix" target="_blank">15 ✅</a>                                             | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/merge-intervals" target="_blank">16 ✅</a>     | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/jump-game" target="_blank">17 ✅</a>                      | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/container-with-most-water" target="_blank">18 ✅</a> | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/count-the-repetitions" target="_blank">19 ✅</a> |
| <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/number-of-islands" target="_blank">20 ✅</a>              | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/count-number-of-nice-subarrays" target="_blank">21 ✅</a>              | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/binary-tree-right-side-view" target="_blank">22 ✅</a>                           | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/coin-lcci" target="_blank">23 ✅</a>           | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof" target="_blank">24 ✅</a> | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/permutations" target="_blank">25 ✅</a>              | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/merge-k-sorted-lists" target="_blank">26 ✅</a>  |
| <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/search-in-rotated-sorted-array" target="_blank">27 ✅</a> | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof" target="_blank">28 ✅</a> | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/find-in-mountain-array" target="_blank">29 ✅</a>                                | <a style="color: #2DB55D;" href="https://leetcode-cn.com/problems/happy-number" target="_blank">30 ✅</a>        | <font color=gray>1</font>                                                                                                  | <font color=gray>2</font>                                                                                             | <font color=gray>3</font>                                                                                         |

代码托管在 <a href="https://github.com/JingqingLin/LeetCode/tree/master/%E6%AF%8F%E6%97%A5%E4%B8%80%E9%A2%98%20-%202020.04" target="_blank">GitHub</a>，许多题目之前做过，位于其他目录。

---

打卡完毕 🎉

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/Blog/docs/leetcode/_images/medal.png" alt="打卡勋章" width="40%"/>

---

## 1. 有效括号的嵌套深度

!> [1111](https://leetcode-cn.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/). 有效括号的嵌套深度

题目很啰嗦。嵌套深度就是栈的最大深度，A 和 B 要求把栈的深度尽量对等分，所以可以把栈的深度为奇数的分给 B，偶数的分给 A

```java
Seq     =   (  (  )  (  (  )  )  (  )  )
嵌套深度 = [ 1, 2, 2, 2, 3, 3, 2, 2, 2, 1]
分组情况 = [ A, B, B, B, A, A, B, B, B, A]
最后输出 = [ 0, 1, 1, 1, 0, 0, 1, 1, 1, 0]

public static int[] maxDepthAfterSplit(String seq) {
    int[] ans = new int[seq.length()];
    int depth = 0;
    int index = 0;
    for (char c : seq.toCharArray()) {
        if (c == '(') {
            depth++;
            ans[index++] = depth % 2;
        } else {
            ans[index++] = depth % 2;
            depth--;
        }
    }
    return ans;
}
```

## 2. 生命游戏

!> [289](https://leetcode-cn.com/problems/game-of-life/). 生命游戏

如何原地解决？https://leetcode-cn.com/problems/game-of-life/solution/sheng-ming-you-xi-by-leetcode-solution/

## 3. 接雨水

!> [42](https://leetcode-cn.com/problems/trapping-rain-water/). 接雨水

直接看[官方题解](https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/)

### ⭐ 动态编程

左右各扫描一次

![](_images/april-3-1.png ':class=resizedImage')

### 双指针 和 单调栈

## 4. LFU缓存

!> [460](https://leetcode-cn.com/problems/lfu-cache/). LFU缓存

> 请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。它应该支持以下操作：get 和 put
> - get(key) - 如果键存在于缓存中，则获取键的值（总是正数），否则返回 -1
> - put(key, value) - 如果键已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量时，则应该在插入新项之前，使最不经常使用的项无效。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除**最近**最少使用的键
> 
> 「项的使用次数」就是自插入该项以来对其调用 get 和 put 函数的次数之和。使用次数会在对应项被移除后置为 0

键的移除条件：先比使用频率，再比最后一次的使用时间

### 哈希表 + 优先队列（$O(logN)$ 解法）
哈希表用于查找键是否在缓存中。优先队列用于判断移除哪个键，它根据键的**使用频率**和**最后使用时间**维护一个堆

对于 `get` 操作，
- 通过哈希表判断键是否在缓存中
  - 若存在，更新使用频率和最后使用时间，并更新优先队列
  - 若不存在，返回 -1

对于 `put` 操作，
- 若键在缓存中，则等同于进行一次 `get`
- 若不存在，则需要把键加入缓存
  - 若缓存已满，根据 `键的移除条件` 移除键，再初始化一个 Node 并加入哈希表和优先队列
  - 若缓存未满，初始化一个 Node 并加入哈希表和优先队列

由于键的**使用频率**和**最后使用时间**被频繁调用，我们创建一个 Node 类来保存这些信息，并通过实现 Comparable 接口来使其“支持排序”（或实现优先队列的 Comparator 接口）

```java
private static class Node implements Comparable<Node> {
    int key;
    int value;
    int frequency;
    int globalTime;
    public Node() {
    }
    public Node(int key, int value, int globalTime) {
        this.key = key;
        this.value = value;
        frequency = 1;
        this.globalTime = globalTime;
    }
    @Override
    public int compareTo(Node node) {
        int diff = frequency - node.frequency;
        return diff != 0 ? diff : globalTime - node.globalTime;
    }
}
```

哈希表的查找时间复杂度为 $O(1)$，优先队列的插入和删除操作时间复杂度为 $O(logN)$

代码<a href="https://github.com/JingqingLin/LeetCode/blob/master/%E6%AF%8F%E6%97%A5%E4%B8%80%E9%A2%98%20-%202020.04/460.%20LFU%E7%BC%93%E5%AD%98/src/BFS.java" target="_blank">在这<a>

## 5. ⭐ 旋转矩阵

!> 面试题 [01.07](https://leetcode-cn.com/problems/rotate-matrix-lcci/). 旋转矩阵 

### 原地旋转

https://leetcode-cn.com/problems/rotate-matrix-lcci/solution/xuan-zhuan-ju-zhen-by-leetcode-solution/

### 两次翻转

上下翻 + 对角线翻

## 6. 翻转字符串里的单词

!> [151](https://leetcode-cn.com/problems/reverse-words-in-a-string/). 翻转字符串里的单词

### 使用语言特性

很多语言对字符串提供了 `split`（拆分），`reverse`（翻转）和 `join`（连接）等方法，因此我们可以简单的调用内置的 API 完成操作

```java
public static String reverseWords(String s) {
    // 除去开头和末尾的空白字符
    s = s.trim();
    // 正则匹配连续的空白字符作为分隔符分割
    List<String> wordList = Arrays.asList(s.split("\\s+"));
    Collections.reverse(wordList);
    return String.join(" ", wordList);
}
```

- 学到一个新方法 `String.join()`：为 charSequence 加入 delimiter（分隔符）

### 双端队列

- 学到一个新方法 `StringBuilder.setLength()`

## 7. 鸡蛋掉落

!> [887](https://leetcode-cn.com/problems/super-egg-drop/). 鸡蛋掉落

### 动态规划

李永乐老师的视频讲解：

<!-- B 站嵌入参数调整：https://www.xbeibeix.com/bilibili3/ -->

<!-- 保持宽高比（js）：https://blog.csdn.net/sloafer/article/details/82659360 -->

B 站：

<!-- <iframe src="//player.bilibili.com/player.html?aid=96214853&bvid=BV1KE41137PK&cid=164251653&page=1&high_quality=1&danmaku=0" allowfullscreen scrolling="no" frameborder="0" sandbox="allow-top-navigation allow-same-origin allow-forms allow-scripts"></iframe> -->

[bilibili](https://player.bilibili.com/player.html?aid=96214853&bvid=BV1KE41137PK&cid=164251653&page=1&high_quality=1&danmaku=0 ':include :type=iframe width=100% height=550px')

<!-- 油管：

<iframe width="80%" src="https://www.youtube.com/embed/mLV_vOet0ss" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[YouTube](https://www.youtube.com/embed/mLV_vOet0ss ':include :type=iframe width=100% height=400px') -->

dp 思想截图：

![](_images/april-7-1.png ':class=resizedImage')

按照动规思想写出代码，

```java
public static int superEggDrop(int K, int N) {
    // N 层 K 蛋
    int[][] dp = new int[K + 1][N + 1];
    for (int i = 1; i <= K; i++) {
        dp[i][1] = 1;
    }
    for (int j = 1; j <= N; j++) {
        dp[1][j] = j;
    }
    // 蛋先遍历
    for (int i = 2; i <= K; i++) {
        for (int j = 2; j <= N; j++) {
            int min = Integer.MAX_VALUE;
            for (int k = 1; k <= j; k++) {
                min = Math.min(min, Math.max(dp[i - 1][k - 1], dp[i][j - k]) + 1);
            }
            dp[i][j] = min;
        }
    }
    return dp[K][N];
}
```

提交后超时。从转移方程入手，我们可以发现 `Math.max(dp[i - 1][k - 1], dp[i][j - k]) + 1` 中，

- 当 `k` 增大时，`dp[i - 1][k - 1]` 是递增的，因为层数 `k` 越多，需要的次数就越多
- 当 `k` 增大时，`dp[i][j - k]` 是递减的，因为层数 `j - k` 越小，需要的次数就越少

类似于下图：

![](_images/april-7-2.png ':class=resizedImage')

因此 max 在两者相交时取到最小值。那么我们令 `low = 1, high = j`（当前总楼层数），`index = (low + high) / 2`

```java
public static int superEggDrop(int K, int N) {
    ...
    // 蛋先遍历 + 二分查找
    for (int i = 2; i <= K; i++) {
        for (int j = 2; j <= N; j++) {
            int low = 2, high = j;
            while (low < high) {
                int m = low + (high - low) / 2;
                // y1 递增，y2 递减
                int y1 = dp[i - 1][m - 1], y2 = dp[i][j - m];
                if (y1 > y2) {
                    high = m - 1;
                } else if (y1 < y2) {
                    low = m + 1;
                } else {
                    low = high = m;
                }
            }
            // low 和 high 有可能是不相等的 low - 1 = high，因为他们的交点不在整数层上
            if (low == high) {
                dp[i][j] = Math.max(dp[i - 1][low - 1], dp[i][j - low]) + 1;
            } else {
                dp[i][j] = Math.min(Math.max(dp[i - 1][low - 1], dp[i][j - low]), Math.max(dp[i - 1][high - 1], dp[i][j - high])) + 1;
            }
        }
    }
    return dp[K][N];
}
```

### 决策单调性、数学法

[官方题解](https://leetcode-cn.com/problems/super-egg-drop/solution/ji-dan-diao-luo-by-leetcode-solution/)

## 8. 设计推特

!> [355](https://leetcode-cn.com/problems/design-twitter/). 设计推特

关键在于 `getNewsFeed(userId)`（获取最近十条推文流）如何设计，有两种思路：

1. 将所有推文存储到链表（准确地说用链表 + 哈希表。链表用来保持时间顺序；哈希表用于对推文和用户做映射关系），获得推流时，判断推文是否满足要求
2. 将推文根据用户 ID 分开存储，每个用户的推文用链表 + 哈希表存储。那么问题其实就等价于有若干个有序的链表，我们需要找到它们合起来最近的十条推文，问题就转化为 ⭐[合并 K 个排序链表](https://leetcode-cn.com/problems/merge-k-sorted-lists/)

## 9. 两数相加 II

!> [445](https://leetcode-cn.com/problems/add-two-numbers-ii/). 两数相加 II

题目建议不修改（反转）链表，所以通过**栈**暂存链表以达到反转效果

## 10. 01 矩阵

!> [542](https://leetcode-cn.com/problems/01-matrix/). 01 矩阵

### ⭐ BFS
遍历矩阵，若为 0 ，则把 0 加入队列并开始 BFS，设置一个 distance 变量记录 BFS 层数，遇到 1 则更新层数。对于矩阵中的每个 0，都要从它开始做 BFS，但这样的时间复杂度非常高，如下地图


0 <font color=red>0</font> 0  
0 1 0  
<font color=green>0</font> <font color=blue>1</font> 1  

若先从红色的 0 点开始 BFS，那么蓝色的 1 会被更新成 2；再从绿色的 0 点开始 BFS，蓝色的 1 会被重新更新为 1。所以从每个 0 点更新距离的方法可能会对某个点进行多次更新（要取最小值），导致时间复杂度非常高

代码<a href="https://paste.ubuntu.com/p/GTYDkdBFPr/" target="_blank">在这</a>

解决的方法是一次性把所有的 0 都加入队列，成为 BFS 的第一层。那么经过一次 BFS，所有距离为 1 的点都会入队；第二次 BFS，所有距离为 2 的点都会入队...

本题和三月份做过的两题“[1162](https://leetcode-cn.com/problems/as-far-from-land-as-possible/). 地图分析（2020.03.29）”和“[994](https://leetcode-cn.com/problems/rotting-oranges/). 腐烂的橘子（2020.03.04）”本质上相同


代码<a href="https://paste.ubuntu.com/p/5xP2YXwnzY/" target="_blank">在这</a>

### 动态规划
[官方题解](https://leetcode-cn.com/problems/01-matrix/solution/01ju-zhen-by-leetcode-solution/)

## 11. ⭐ 合并区间

!> [56](https://leetcode-cn.com/problems/merge-intervals/). 合并区间

> 第一眼看起来和<a href="https://leetcode-cn.com/problems/non-overlapping-intervals/" target="_blank">无重叠区间</a>很像，想用贪心做，但失败了


![](_images/april-11-1.png ':class=resizedImage')

按左端点排序，遍历区间，将合并后的区间放到“合并数组”中：
- 若“合并数组”为空，则把当前区间（排序后的第一个区间）加入“合并数组”
- **若当前区间的左端点小于等于“合并数组”最后一个区间的右端点**，说明有重合，只需更新“合并数组”的右区间
- 若若当前区间的左端点大于“合并数组”最后一个区间的右端点，则把当前区间加入“合并数组”

```java
public static int[][] merge(int[][] intervals) {
    int[][] mergedArray = new int[intervals.length][];
    Arrays.sort(intervals, (o1, o2) -> o1[0] - o2[0]);
    int index = -1;
    for (int i = 0; i < intervals.length; i++) {
        int leftEnd = intervals[i][0], rightEnd = intervals[i][1];
        if (index == -1 || mergedArray[index][1] < leftEnd) {
            mergedArray[++index] = intervals[i];
        } else if (mergedArray[index][1] >= leftEnd) {
            mergedArray[index][1] = Math.max(rightEnd, mergedArray[index][1]);
        }
    }
    return Arrays.copyOf(mergedArray, index + 1);
}
```

## 12. 跳跃游戏

!> [55](https://leetcode-cn.com/problems/jump-game/). 跳跃游戏

### BFS
把能跳到的位置加入队列，若最后一个点入队，返回 true

### ⭐ 贪心思想
> 我怎么就想不到呢 TAT

我们依次遍历数组中的每一个位置，并**实时**维护**最远可以到达的位置**

对于当前遍历到的位置 $x$，如果它在**最远可以到达的位置**的范围内，那么我们就可以从某点通过若干次跳跃到达该位置，因此我们可以用 $x + nums[x]$ 更新最远可以到达的位置；如果它超出了**最远可以到达的位置**，则无法到达终点

```java
public static boolean canJump(int[] nums) {
    int n = nums.length;
    int rightMost = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= rightMost) {
            rightMost = Math.max(rightMost, i + nums[i]);
            if (rightMost >= n - 1) {
                return true;
            }
        } else {
            break;
        }
    }
    return false;
}
```

## 13. 盛最多水的容器

!> [11](https://leetcode-cn.com/problems/container-with-most-water/). 盛最多水的容器

暴力法也可做，双指针法不太想得到

### 双指针
**移动较短的那根**  
因为短指针限制了高度，如果移动长指针不可能增加整体的高度，而底在不断减少，所以移动短指针来**尝试**增加最大高度

![](_images/april-13-1.png ':class=resizedImage')

## 14. ⭐ 统计重复个数

!> [466](https://leetcode-cn.com/problems/count-the-repetitions/). 统计重复个数

### 暴力法
循环方法一直报错，先暴力提交通过

```java
public static int getMaxRepetitions(String s1, int n1, String s2, int n2) {
    char[] c1 = s1.toCharArray();
    char[] c2 = s2.toCharArray();
    // i 为 s2 的索引
    int i = 0, num1 = 0, num2 = 0;
    while (num1 < n1) {
        for (char c : c1) {
            if (c == c2[i]) {
                if (i == c2.length - 1) {
                    i = 0;
                    num2++;
                } else {
                    i++;
                }
            }
        }
        num1++;
    }
    return num2 / n2;
}
```

### 找出循环节
一开始一直在找 s2 和 s1 之间的倍数关系，但始终有错误，以下测试用例为易错用例

```
"bacaba", 3, "abacab", 1
"baba", 11, "baab", 1
"niconiconi", 99981, "nico", 81
```

于是参考[官方题解](https://leetcode-cn.com/problems/count-the-repetitions/solution/tong-ji-zhong-fu-ge-shu-by-leetcode-solution/)，用循环节的方法（官方题解讲得不怎么清楚），代码 copy 了[这个](https://leetcode-cn.com/problems/count-the-repetitions/solution/java-1msxiang-xi-zhu-shi-by-feixiang-4/)题解<font color=gray>，我怎么就想不到呢 TAT</font>

- 什么是循环节？
    - 可以类比无限循环小数，如果从小数部分的某一位起向右进行到某一位止的一节数字「循环」出现，首尾衔接，称这种小数为「无限循环小数」，这一节数字称为「无限循环小数」。比如对于 `3.56789789789...` 这个无限循环小数，它的小数部分就是以 `789` 为一个「**循环节**」在无限循环，且开头可能会有部分不循环的部分，这个数字中即为 `56`

> S1 = [s1, n1]

我们可以将不断循环的 `s2` 组成的字符串类比作上面小数部分，去找是否存在一个子串，即「循环节」，满足不断在 `s2` 中循环，且这个**循环节能对应固定数量的 `s1`**。如下图所示，在第一次出现后，`s2` 的子串 `bdadc` 构成一个循环节：之后 `bdadc` 的每次出现都需要有相应的两段 `s1`。

![](_images/april-14-1.png ':class=resizedImage')

- 如何找出循环节？
  1. 以 `s1` 为单位循环遍历 `S1 = [s1,n1]`，同时维护为 `s2` 一个指针 `p`，记录现在指向 `s2` 中的哪个位置。若两字符串字符相等，则 `p++`（指向了 `s2` 的后一个位置）
  2. 我们记录每次结束遍历 `s1` 后 `p` 的位置，若 `p` 的位置之前和以前某一次一样，那么这两次 `p` 之间存在一个循环节

以上方图片为例，在黄色箭头处记录 `p` 的位置，我们发现第一次和第三次遍历 `s1` 结束后 `p` 的位置相同，都指向了 `s2` 的第三个字符 `c`，因此 `bdadc` 构成一个循环节。

接着，我们只需求出一个**循环节**包括了几个 `s1` 和 `s2`，就可以根据循环节的个数（看<a href="https://github.com/JingqingLin/LeetCode/blob/master/%E6%AF%8F%E6%97%A5%E4%B8%80%E9%A2%98%20-%202020.04/466.%20%E7%BB%9F%E8%AE%A1%E9%87%8D%E5%A4%8D%E4%B8%AA%E6%95%B0/src/Solution.java" target="_blank">代码</a>）求出答案。

- 如何处理开头和末尾的情况？
    - 最后一个 `s1` 不遍历，然后只需求出第一个循环节结束之前（上图第三个黄色箭头之前）遍历 `s2` 的次数


## 15. 统计「优美子数组」

!> [1248](https://leetcode-cn.com/problems/count-number-of-nice-subarrays/). 统计「优美子数组」

> 这题没想出来 TAT

这老兄的方法妙，<a href="https://leetcode-cn.com/problems/count-number-of-nice-subarrays/solution/zui-jian-dan-jie-fa-bie-yong-shi-yao-shuang-zhi-zh/" target="_blank">链接</a>

「优美子数组」的个数取决于**以奇数为端点的数组的左右两边偶数个数**。以 `[2, 2, 2, 1, 2, 2, 1, 2, 2, 2], k = 2` 为例，我们取 `[1, 2, 2, 1]` 作为**以奇数为端点的数组**，此数组左右两边各有三个偶数，穷举左边偶数的情况：

[<font color=red>1, 2, 2, 1,</font> ...]  
[2, <font color=red>1, 2, 2, 1,</font> ...]  
[2, 2, <font color=red>1, 2, 2, 1,</font> ...]  
[2, 2, 2, <font color=red>1, 2, 2, 1,</font> ...]

有四种情况，同理右边也是四种。因此当 `[1, 2, 2, 1]` 作为**以奇数为端点的数组**时，共有 4 * 4 = 16 个「优美子数组」

根据此方法，可写出代码


## 16. 二叉树的右视图

!> [199](https://leetcode-cn.com/problems/binary-tree-right-side-view/). 二叉树的右视图

> 不能单条线递归，如下情况，5 不会被遍历进去

![](_images/april-16-1.png ':class=resizedImage')

BFS，⭐ DFS 皆可。BFS 先把左子树入队，DFS 先递归右子树

## 17. 💣 硬币

!> [面试题 08.11](https://leetcode-cn.com/problems/coin-lcci/). 硬币

DFS 也可以做，但是会 `java.lang.StackOverflowError`

> 0 - 1 背包的变种，完全背包问题
>
>**完全背包问题**
>- 有 $n$ 种物品，每种物品的单件重量为 $w[i]$,价值为 $c[i]$。现有一个容量为 $V$ 的背包，问如何选取物品放入背包，使得背包内物品的总价值最大。其中每种物品都有无穷件
>
>通用转移方程（从小到大枚举），要么不放第 $i$ 件物品，要么放：
>
>${dp}[{i}][{v}]=\max ({dp}[{i}-1][{v}], {dp}[{i}][{v}-{w}[{i}]]+{c}[{i}])$  
$\quad(1 ≤ {i} ≤ {n}, {w}[{i}] ≤ {v} ≤ {V})$

回到本题：


有四种类型的物品（硬币），每种物品（硬币）的重量（面值） $coins[i]$ 为 1，5，10，25，背包的容量（总面值）为 n，求共有几种可能性，使背包内物品的总重量（总面值）为 n 

**dp 数组定义**：

$dp[i][j]$ 表示前 $i$ 种硬币组成面值为 $j$ 时的方法数

**初始值**：
- $dp[0][j]$ 表示 0 种硬币组成面值 $j$，不可能有方案，因此是 0
- $dp[i][0]$ 表示多种硬币组成面值 $0$，只有一种方案，一枚也不选

**状态转移方程**：

${dp}[{i}][{j}]= {dp}[{i}-1][{j}] + {dp}[{i}][{j}-{coins}[{i}]]$  
$\quad(1 ≤ {i} ≤ 4, {coins}[{i}] ≤ {j} ≤ {n})$

当遍历到第 $i$ 种硬币时，组成面值 $j$ 的硬币有两种可能：选了第 $i$ 种硬币面值刚好达到 $j$，不选它面值就已经达到 $j$
- $dp[i - 1][j]$ 表示当前硬币不选
- $dp[i][j - coins[i])$ 表示当前硬币选了

再进行空间优化...

## 18. 💣 数组中的逆序对

!> [面试题51](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/). 数组中的逆序对

剑指 Offer 里的题

### 暴力法
暴力法时间复杂度为 $O(n^2)$，不通过

### 归并排序
今天的[官方题解](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/solution/shu-zu-zhong-de-ni-xu-dui-by-leetcode-solution/)很棒

以下摘自官方题解（有修改）：

> 求逆序对和归并排序又有什么关系呢？关键就在于「归并」当中「并」的过程。我们通过一个实例来看看。假设我们有两个**有序序列**等待合并，分别是 $L = \{ 8, 12, 16, 22, 100 \}$ 和 $R = \{ 9, 26, 55, 64, 91 \}$。一开始我们用指针 `lPtr = 0` 指向 $L$ 的首部，`midPtr = (lPtr + rPtr) / 2` 指向 $L$ 的尾部，`rPtr = 0` 指向 $R$ 的头部。记已经合并好的部分为 $M$。
>
> ```java
> L = [8, 12, 16, 22, 100]   R = [9, 26, 55, 64, 91]  M = [8]
>      |                          |
>    lPtr                       rPtr
> ```
>
> 我们发现 `lPtr` 指向的元素小于 `rPtr` 指向的元素，我们把左边的 $8$ 加入了答案，我们发现右边没有数比 $8$ 小，所以 $8$ 对逆序数的「贡献」为 $0$。并把 `lPtr` 后移一位。
>
> ```java
> L = [8, 12, 16, 22, 100]   R = [9, 26, 55, 64, 91]  M = [8, 9]
>         |                       |
>       lPtr                     rPtr
> ```
>
> 接着我们继续合并，把 $9$ 加入了答案，此时 $L$ 中 `lPtr` 和它之后的数（`[12, 16, 22, 100]`）都比 $9$ 大，说明 $9$ 对逆序数的贡献为 $4$。并把 `rPtr` 后移一位。
>
> 我们发现用这种「算贡献」的思想在合并的过程中计算逆序对的数量的时候，只发生在 `L[lPtr] > R[rPtr]` 时，并且贡献了 `midPtr - lPtr + 1` 个逆序数


**归并排序的优化：**
若 Partition 后，左子数组的最右元素 <= 右子数组的最左元素，则说明（左 + 右数组）已经有序，无需 Merge 这一步

```java
// 已经有序
if (nums[mid] <= nums[mid + 1]) {
    return leftCount + rightCount;
}
```

用时缩短：

![](_images/april-18-1.png ':class=resizedImage')

## 19. 合并K个排序链表

!> [23](https://leetcode-cn.com/problems/merge-k-sorted-lists/). 合并K个排序链表

看[官方题解](https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/he-bing-kge-pai-xu-lian-biao-by-leetcode-solutio-2/)完事

## 20. 搜索旋转排序数组

!> [33](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/). 搜索旋转排序数组

本题若用 $O(n)$ 完成则无意义，考查的是对二分查找的应用

先应用一次二分找出最小或最大值（它们），确定目标值的范围，再应用一次二分查找即可

```java
// 找出最小值
int l = 0, r = len - 1;
while (l < r) {
    int m = l + (r - l) / 2;
    if (nums[m] > nums[r]) {
        l = m + 1;
    }
    else {
        r = m;
    }
}
```

## 21. ⭐ 数组中数字出现的次数

!> [面试题56 - I](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/). 数组中数字出现的次数

要求时间复杂度 $O(n)$，空间复杂度 $O(1)$

> 想到往位运算方向靠，但没想出解法 TAT

### 异或 + 分组

对于异或，我们有一个性质：$x = x \oplus y \oplus y$

由于数组中仅存在两个数字只出现一次，我们将所有的数字异或操作起来，最终得到的结果是这两个数字的异或结果。以示例 1 为例：

```
4 ^ 1 ^ 4 ^ 6 = 1 ^ 6

6 对应的二进制： 110
1 对应的二进制： 001
1 ^ 6  二进制： 111
```

此时我们无法通过 111（二进制），去获得 110 和 001。

那么当我们可以把数组**分为两组**进行异或（相同的数字放在同一组），那么就可以知道是哪两个数字不同了。

我们可以想一下**如何分组**：

1. 对*重复的数字*进行分组，很简单，只需要有一个统一的规则，就可以把相同的数字分到同一组了。例如：奇偶分组。因为重复的数字，数值都是一样的，所以一定会分到同一组
2. 此时的难点在于，对*两个不同数字*的分组。我们要找到一个操作，让两个数字进行这个操作后，分为两组。最容易想到的就是 `& 1` 操作， 当我们对奇偶分组时，容易地想到 `& 1`，即用于判断最后一位二进制是否为 1 来辨别奇偶

由于两个不同的二进制数中至少有一位（bit）是不同的，那么我们通过上面的分析，可以尝试通过与运算来找出不同的那位（bit），比如上述例子中 `110` 和 `001` 中的最低位不同，那么我们可以通过 `& 1` 操作得到不同的结果：`110 & 1 = 0`，`001 & 1 = 1`，即可根据结果分组。

再举个例子：对于二进制数 `001111` 和 `111111`，最高的两位都不同，我们既可以对两个数 `& 010000`，也可以 `& 100000` 进行分组。因此，我们约定取**最低的不同位**进行与运算，也就是进行 `& 010000` 操作。

接着，剩下最后一个问题，如何从一个数组中得到这两个数最低的不同位呢？**异或**！由于 `0 ^ 1 = 1` 那么我们只需找出异或结果的最低位的那个 `1` 即可。 

```
4 ^ 1 ^ 4 ^ 6 = 1 ^ 6

6 对应的二进制： 110
1 对应的二进制： 001
1 ^ 6  二进制： 111
```

在这个例子中，异或结果 `111` 中最低位的那个 `1` 是最右边那位，那么我们需要对数字进行 `& 1` 操作

代码[传送门](https://paste.ubuntu.com/p/hqgbksPvVg/)

<font color=gray>摘自力扣[题解](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/solution/jie-di-qi-jiang-jie-fen-zu-wei-yun-suan-by-eddievi/)</font>

<!-- 截图<a href="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1917068-20200428110544221-407370357.png" target="_blank">备份</a> -->

## 22. 山脉数组中查找目标值

!> [1095](https://leetcode-cn.com/problems/find-in-mountain-array/). 山脉数组中查找目标值

> 考查二分查找的知识

如何查找峰值？代码如下

```java
int maxIndex = 0;
while (l < r) {
    int m = l + (r - l) / 2;
    int temp = mountainArr[m];
    int left = mountainArr[m - 1];
    int right = mountainArr[m + 1];
    if (temp > left && temp > right) {
        maxIndex = m;
        break;
    } else if (temp > left) {
        l = m + 1;
    } else if (temp > right) {
        r = m;
    }
}
```