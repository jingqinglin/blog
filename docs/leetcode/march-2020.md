力扣<a href="https://leetcode-cn.com/problemset/2020-03/" target="_blank">每日 1 题：3 月</a>（部分）。三月的题难度等级多为<font color=#009975>简单</font>，未作过多记录。

| 一                                | 二                                | 三                                | 四                                | 五                                | 六                                | 日                                |
| --------------------------------- | --------------------------------- | --------------------------------- | --------------------------------- | --------------------------------- | --------------------------------- | --------------------------------- |
| <font color=gray>24</font>        | <font color=gray>25</font>        | <font color=gray>26</font>        | <font color=gray>27</font>        | <font color=gray>28</font>        | <font color=gray>29</font>        | <font color=#2DB55D>~~1~~</font>  |
| <font color=#2DB55D>~~2~~</font>  | <font color=#2DB55D>~~3~~</font>  | <font color=#2DB55D>~~4~~</font>  | <font color=#2DB55D>~~5~~</font>  | <font color=#2DB55D>~~6~~</font>  | <font color=#2DB55D>~~7~~</font>  | <font color=#2DB55D>~~8~~</font>  |
| <font color=#2DB55D>~~9~~</font>  | <font color=#2DB55D>~~10~~</font> | <font color=#2DB55D>~~11~~</font> | <font color=#2DB55D>~~12~~</font> | <font color=#2DB55D>~~13~~</font> | <font color=#2DB55D>~~14~~</font> | <font color=#2DB55D>~~15~~</font> |
| <font color=#2DB55D>~~16~~</font> | <font color=#2DB55D>~~17~~</font> | <font color=#2DB55D>~~18~~</font> | <font color=#2DB55D>~~19~~</font> | <font color=#2DB55D>~~20~~</font> | <font color=#2DB55D>~~21~~</font> | <font color=#2DB55D>~~22~~</font> |
| <font color=#2DB55D>~~23~~</font> | <font color=#2DB55D>~~24~~</font> | <font color=#2DB55D>~~25~~</font> | <font color=#2DB55D>~~26~~</font> | <font color=#2DB55D>~~27~~</font> | <font color=#2DB55D>~~28~~</font> | <font color=#2DB55D>~~29~~</font> |
| <font color=#2DB55D>~~30~~</font> | <font color=#2DB55D>~~31~~</font> | <font color=gray>1</font>         | <font color=gray>2</font>         | <font color=gray>3</font>         | <font color=gray>4</font>         | <font color=gray>5</font>         |


---

打卡完毕 🎉

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/Blog/docs/leetcode/_images/medal.png" alt="打卡勋章" width="40%"/>

---

## 1. 分糖果 II

!> [1103](https://leetcode-cn.com/problems/distribute-candies-to-people/). 分糖果 II

等差数列求和：https://leetcode-cn.com/problems/distribute-candies-to-people/solution/fen-tang-guo-ii-by-leetcode-solution/

主要是如何求 `p`

## 2. 多数元素

!> [169](https://leetcode-cn.com/problems/majority-element/). 多数元素

> 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 `⌊ n/2 ⌋` 的元素

排序数组，`nums[nums.length / 2]` 肯定是多数元素

## 3. 使数组唯一的最小增量

!> [945](https://leetcode-cn.com/problems/minimum-increment-to-make-array-unique/). 使数组唯一的最小增量

### 计数法、排序法
https://leetcode-cn.com/problems/minimum-increment-to-make-array-unique/solution/shi-shu-zu-wei-yi-de-zui-xiao-zeng-liang-by-leet-2/

### 线性探测法
https://leetcode-cn.com/problems/minimum-increment-to-make-array-unique/solution/ji-shu-onxian-xing-tan-ce-fa-onpai-xu-onlogn-yi-ya/

#### 路径压缩（并查集知识，详见算法笔记）
问题的由来：  
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200324005441.png" width="70%"/>

本题中的情况：若出现 5 个 n，那么每次都是从第 n 位开始往后探测，显然会很耗时。所以每次放置好一个 n 后，把 `pos[n]` 修改为新的位置。比如第 4 个 n 放在 n + 3 的位置，那么放置好之后就把 `pos[n] = n + 3`，那么下次探测就从 `n + 3` 开始

## 4. ⭐ 单词的压缩编码

!> [820](https://leetcode-cn.com/problems/short-encoding-of-words/). 单词的压缩编码

### 根据长度排序（慢）
根据字符串长度降序排序：`{"atime", "aatime", "btime"}` -> `{aatime, atime, btime}`

- 法 1：若索引串中的后缀不包含当前字符串，就把字符串加入索引串。由于存在 `well` 和 `we` 这种情况，所以不能单纯地 `contains`。利用 `#` 这个特点，比较 `well#` 和 `we#` 的包含关系
- 法 2：因为字符串降序排序，所以向前搜索，若后缀匹配，则不加长度

### 倒序并排序
倒序并排序字符串：`{"atime", "aatime", "btime"}` -> `{"emita", "emitaa", "emitb"}`，String 没有 `reverse` 方法，要手动转一下

比较相邻字符串是否有包含关系即可，包含即不加入索引串，不包含即加入前一个字符串（只需记录索引串的长度）

```java
// 比较相邻字符串，若后者包含前者则跳过
for (int i = 0; i < wordsLen - 1; i++) {
    int len = reverseWords[i].length();
    if (reverseWords[i + 1].startsWith(reverseWords[i])) {
        continue;
    }
    indexLen += len + 1;
}
```

**学到一个新方法**：`String.StartsWith()`，检测字符串是否以指定的前缀开始

```java
public boolean startsWith(String prefix, int toffset)
或
public boolean startsWith(String prefix)
```

### 存储后缀（很难想到）
首先将所有单词加入哈希表

题目限制了单词长度不大于 7，枚举所有单词的后缀，若后缀存在于哈希表，则删除这个后缀。比如哈希表里有 `time` 和 `me`，遍历 `time` 的后缀，遍历到 `me` 时，哈希表中存在这个后缀，则删除 `me` 这个后缀

```java
public static int minimumLengthEncoding(String[]words) {
    Set<String> good = new HashSet(Arrays.asList(words));
    for (String word : words) {
        for (int k = 1; k < word.length(); ++k)
            good.remove(word.substring(k));
    }
    int ans = 0;
    for (String word : good)
        ans += word.length() + 1;
    return ans;
}
```

### ⭐ 字典树（前缀树）

!> [字典树](https://zh.wikipedia.org/wiki/Trie)（前缀树）

> 字典树可用于搜索提示或词频统计

<img src="https://i.loli.net/2020/03/28/pNs12f8hrcJ3aUV.png" width="70%">

字典树的叶子节点路径长度和即为答案

字典树的构造可以参照[此题](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)构造字典树

## 5. 地图分析（2020.03.29）& 腐烂的橘子（2020.03.04）

!> [1162](https://leetcode-cn.com/problems/as-far-from-land-as-possible/). 地图分析（2020.03.29）& [994](https://leetcode-cn.com/problems/rotting-oranges/). 腐烂的橘子（2020.03.04）

> 这两题是“换壳”题，思路完全一样。下面分析“地图分析”这题

### 从海洋开始广搜
对每个海洋点进行广搜，得到这个点到陆地的最近距离。然后从所有最近距离中挑出距离最大的那个点

时间复杂度：$O(n^4)$

### 从陆地开始广搜
> 橘子那题很容易就想到这个方法，但地图这题换了个说法，第一反应是上面的更费时的方法

把所有陆地点入队，然后进行广搜，直到遍历完所有海洋点，广搜的**层数**就是最远距离，如下图：

图片源自力扣讨论区[题解](https://leetcode-cn.com/problems/as-far-from-land-as-possible/solution/jian-dan-java-miao-dong-tu-de-bfs-by-sweetiee/)：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/367df5172fd16d2637e591f6586d146772758438c66660c86719ffb2d36eb14d-image.png" width="70%"/>

## 6. 面试题62. 圆圈中最后剩下的数字

!> [面试题62](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/). 圆圈中最后剩下的数字

👉 剑指 Offer