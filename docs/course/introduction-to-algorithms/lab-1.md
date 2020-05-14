## 实验一 用分治法求解数组的中位数和最大子集

### [问题一](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)：寻找两个有序数组的中位数

#### 题目描述

给定两个大小为 m 和 n 的有序数组 `nums1` 和 `nums2`。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 $O(log(m + n))$。

你可以假设 `nums1` 和 `nums2` 不会同时为空。

**示例 1:**

```java
nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
```

**示例 2:**

```java
nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5
```

#### 解题思路
> 参考自[力扣题解](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-2/)

#### 代码
```java
public static double findMedianSortedArrays(int[]nums1, int[] nums2) {
    int j1 = nums1.length, j2 = nums2.length;
    if (j1 == 0) {
        return (double) (nums2[(j2 - 1) / 2] + nums2[j2 / 2]) / 2;
    } else if (j2 == 0) {
        return (double) (nums1[(j1 - 1) / 2] + nums1[j1 / 2]) / 2;
    } else {
        int left = (j1 + j2 + 1) / 2;
        int right = (j1 + j2 + 2) / 2;
        // left/right 代表奇偶的情况
        return (getKth(nums1, 0, j1 - 1, nums2, 0, j2 - 1, left) + getKth(nums1, 0, j1 - 1, nums2, 0, j2 - 1, right)) * 0.5;
    }
}
private static int getKth(int[] nums1, int start1,int end1, int[] nums2, int start2, int end2, int k){
    // 数组剩余长度
    int len1 = end1 - start1 + 1;
    int len2 = end2 - start2 + 1;
    // 始终让剩余长度较短的数组为 len1
    if (len1 > len2) {
        return getKth(nums2, start2, end2, nums1, start1, end1, k);
    }
    // len1 == 0 或 k == 1 时递归结束
    if (len1 == 0) {
        return nums2[start2 + k - 1];
    }
    if (k == 1) {
        return Math.min(nums1[start1], nums2[start2]);
    }
    int i = start1 + Math.min(len1, k / 2);
    int j = start2 + Math.min(len2, k / 2);
    if (nums1[i - 1] > nums2[j - 1]) {
        return getKth(nums1, start1, end1, nums2, j, end2, k - (Math.min(len2, k / 2)));
    } else {
        return getKth(nums1, i, end1, nums2, start2, end2, k - (Math.min(len1, k / 2)));
    }
}
```

#### 复杂度分析

**时间复杂度**：每进行一次循环，我们就减少 `k/2` 个元素，所以时间复杂度是 $O(log(k)$，而 `k = (m + n) / 2`，所以最终的复杂也就是 $O(log(m+n))$

**空间复杂度**：$O(1)$

### [问题二](https://leetcode-cn.com/problems/maximum-subarray/)：最大子序和

#### 题目描述

给定一个整数数组 `nums` ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

**示例:**

```java
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
```

**进阶:**

如果你已经实现复杂度为 $O(n)$ 的解法，尝试使用更为精妙的分治法求解。

#### 解题思路

> 参考自[力扣官方题解](https://leetcode-cn.com/problems/maximum-subarray/solution/zui-da-zi-xu-he-by-leetcode/)

#### 代码

```java
public static int maxSubArray(int[] nums) {
    return partition(nums, 0, nums.length - 1);
}
public static int sum(int[] nums, int left, intright, int p) {
    if (left == right) {
        return nums[left];
    }
    int leftSubsum = Integer.MIN_VALUE;
    int currSum = 0;
    for (int i = p; i > left - 1; --i) {
        currSum += nums[i];
        leftSubsum = Math.max(leftSubsum, currSum);
    }
    int rightSubsum = Integer.MIN_VALUE;
    currSum = 0;
    for (int i = p + 1; i < right + 1; ++i) {
        currSum += nums[i];
        rightSubsum = Math.max(rightSubsum, currSum);
    }
    return leftSubsum + rightSubsum;
}
public static int partition(int[] nums, int left,int right) {
    if (left == right) {
        return nums[left];
    }
    int mid = (left + right) / 2;
    int leftSum = partition(nums, left, mid);
    int rightSum = partition(nums, mid + 1, right);
    int crossSum = sum(nums, left, right, mid);
    return Math.max(Math.max(leftSum, rightSum), crossSum);
}
```

#### 复杂度分析

时间复杂度：$O(NlogN)$

空间复杂度：$O(logN)$，递归时栈使用的空间
