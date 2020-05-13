?> 剑指 Offer

## 面试题04. 二维数组中的查找

!> [面试题04](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/). 二维数组中的查找

 从右上角开始找，若 `target` 小于此数 `col - 1`，大于则 `row + 1`  
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting/img/35a8c711-0dc0-4613-95f3-be96c6c6e104.gif" width=50%/>


## 面试题07. ⭐ 重建二叉树

!> [面试题07](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/). 重建二叉树

> 思路很清晰，代码不熟（下次再写一遍）  
> 要记录子树在先序和中序数组中的范围

    前序遍历 preorder = [3,9,20,15,7]
    中序遍历 inorder = [9,3,15,20,7]    
        3
       / \
      9  20
        /  \
       15   7

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting/img/60c4a44c-7829-4242-b3a1-26c3b513aaf0.gif" width="430px"/>

## 面试题09. 用两个栈实现队列

!> [面试题09](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/). 用两个栈实现队列

思路：栈 A `push`，栈 B `pop`，B 和 A 的方向相反，因此能 `pop` 出 head

> 摘自力扣：  
> 使用 Java 的同学请注意，如果你使用 Stack 的方式来做这道题，会造成速度较慢；这个原因的话是因为 Stack 继承了 Vector 接口，而 Vector 底层是 AbstractList，是一个数组，那么就要考虑空间扩容的问题了。可以使用 LinkedList 来做 Stack 的容器，因为 LinkedList 实现了 Deque 接口，所以 Stack 能做的事 LinkedList 都能做，其本身结构是个链表，扩容消耗少。但是我的意思不是像 100% 代码那样直接使用一个 List 当做队列，那确实是快，但是不符题意。贴上代码，这样的优化之后，效率提高了 40%，超过 97%。

## 面试题15. 二进制中1的个数

!> [面试题15](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/). 二进制中1的个数

> `>>>` 代表无符号右移，最高位补 0，`>>` 代表有符号右移，正数高位补 0，负数补 1

## 面试题16. ⭐⭐ 数值的整数次方

!> [面试题16](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/). 数值的整数次方

> 第一眼看感觉思路简单。写出了以下代码：

```java
public static double myPow(double x, int n) {
    // 防止最小负数取绝对值后溢出
    long N = n;
    N = Math.abs(N);
    x = n > 0 ? x : 1 / x;
    double res = 1;
    while (--N >= 0) {
        res = res * x;
    }
    return res;
}
```
### 快速幂思想（迭代和递归都可）
> 但以下测试用例超时 `1.00000 2147483647`，所以修改代码：
```java
public static double myPow(double x, int n) {
    long N = n;
    N = Math.abs(N);
    x = n > 0 ? x : 1 / x;
    double res = 1;
    while (N >= 1) {
        if (N % 2 == 1) {
            res = res * x;
        }
        x = x * x;
        N = N / 2;
    }
    return res;
}
```
每当 $n$ 为奇数时，将多出的一项 `x` 乘入 `res`，所以 `res` 内存的是多出来的次方，最后当 $n == 1$ 时，将累积的 `x` 乘入 `res`

**递归**方式更直观：

```java
public static double fastpow(double x,long n) {
    if (n == 0) {
        return 1.0;
    }
    double half = fastpow(x, n / 2);
    if (n % 2 == 1) {
        return x * half * half;
    }
    return half * half;
}
```

## 面试题18. 删除链表的节点

!> [面试题18](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof). 删除链表的节点

剑指 Offer 原题更值得思考：
https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/solution/cong-on-dao-o1-by-ml-zimingmeng/

## 面试题26. ⭐ 树的子结构

> [面试题26](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/). 树的子结构

> ❌我的思路：先序和中序遍历两颗树输出到字符串，再根据字符串是否有包含关系判断。这是错误的：
> 
> <img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting/img/20200303155419.png" width="50%"/>
> 
> 由于有结点 3 的存在，无法通过

因此，用 DFS 可实现（与之前的 DFS 略有不同）。在主方法内比较 B 的根结点和 A 的每一个结点：`return isSubStructureWithRoot(A, B) || isSubStructure(A.left, B) || isSubStructure(A.right, B);`  
若结点的值相同，则进一步在 DFS 方法内继续递归：`return isSubStructureWithRoot(A.left, B.left) && isSubStructureWithRoot(A.right, B.right);`

## 面试题31. 栈的压入、弹出序列

!> [面试题31](https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/). 栈的压入、弹出序列

> 我的思路（比较复杂，要考虑很多细节）：利用双指针记录两个数组的位置，模拟出栈、入栈操作。入栈时，`pushed` 数组指针向前移动；若栈顶元素和 `poped` 数组当前元素相等则出栈（循环判断，对应代码里的 `while`），`poped` 数组指针向前移动。当记录 `pushed` 的指针到达尾部时，判断栈是否为空

```java
// 下面的代码思路和我相似，且不复杂
for (int pushIndex = 0, popIndex = 0;pushIndex < n; pushIndex++) {
    stack.push(pushed[pushIndex]);
    while (popIndex < n && !stack.isEmpty()
            && stack.peek() == popped[popIndex]) {
        stack.pop();
        popIndex++;
    }
}
```

## 面试题51. 💣 数组中的逆序对

!> [面试题51](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/). 数组中的逆序对

### 暴力法
暴力法时间复杂度为 $O(n^2)$，不通过

### 归并排序
这题[官方题解](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/solution/shu-zu-zhong-de-ni-xu-dui-by-leetcode-solution/)中的视频解说很棒

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


**归并排序的小优化：**
若 Partition 后，左子数组的最右元素 <= 右子数组的最左元素，则说明（左 + 右数组）已经有序，无需 Merge 这一步

```java
// 已经有序
if (nums[mid] <= nums[mid + 1]) {
    return leftCount + rightCount;
}
```

用时有提升：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/1917068-20200424131835707-200222903.png" width="60%"/>

## 面试题57 - II. 和为s的连续正数序列

!> [面试题57 - II](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/). 和为s的连续正数序列

```
输入：target = 9        输入：target = 15
输出：[[2,3,4],[4,5]]   输出：[[1,2,3,4,5],[4,5,6],[7,8]]
```
> 我的思路：计算出 1 ~ i (i <= target / 2 + 1) 的和，并存入哈希表，只需在哈希表中寻找 key == sum - target 是否存在

### 滑动窗口
- `sum < target` 右指针增加  
- `sum > target` 左指针增加
- 输出，并使左指针加 2

当然也有求根法：$\frac{(x+y) *(y-x+1)}{2} = target$ 等其他方法。  
https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/solution/java-shuang-100-by-vapormax/

## 面试题59 - II. ⭐ 队列的最大值

!> [面试题59 - II](https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/). 队列的最大值

思路巧妙

要想在 $O(1)$ 时间内做到取出最大值，我们可以想到，能否用一个 `cur_max` 的变量，来记录并且比较每一次新入队的 `value`，但当调用一次 `pop_front()` 后，最大值可能会发生变化，所以行不通。  
进一步地想到，一个变量不行，那直接用一个辅助队列来记录最大值。  
如果我们向队列中插入数字序列 `1 1 1 1 2`，那么在第一个数字 2 被插入后，数字 2 前面的所有数字 1 将不会对结果产生影响。因为数字 2 只能在所有的数字 1 被取出之后才能被取出，因此如果数字 1 如果在队列中，那么数字 2 必然也在队列中，数字 1 不会影响最大值。

因此，**辅助队列设计思路**为：
- 从队尾插入元素时，我们可以提前取出辅助队列中所有比这个元素小的元素，使得辅助队列中只保留比他大的数字。
  - 注意点：应从辅助队列尾部循环取出。原因：当原始队列为 `3 1` 时，辅助队列也为 `3 1` ，此时插入 `2`，原始队列为 `3 1 2`。若从辅助队头取出，则 `1` 仍留在队中，但实际上 `1` 对最大值没有影响；若从尾部取出，`1` 会被取出
- 从队头取出元素时，若辅助队列队头和原始队列队头相等，则辅助队列也要取出元素

## 面试题62. 圆圈中最后剩下的数字

!> [面试题62](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof). 圆圈中最后剩下的数字

### 模拟
模拟的思路比较简单。需要注意的是，用 `LinkedList` 会超时，虽然它插入和删除操作是 $O(1)$，但是找到插入或删除的位置还是需要 $O(n)$，所以插、删操作相对于 `ArrayList` 并无优势；而查找 `ArrayList` 也比 `LinkedList` 快

### 约瑟夫环
看讨论区<a href="https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/chi-jing-stsu-degd-degtsu-tu-jie-yue-se-fu-huan-hu/" target="_blank">题解</a>

从题解中的递推图理解递推关系，截图备份：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200330112806.png" width="70%"/>