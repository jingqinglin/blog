## 实验二 典型排序算法训练：快速排序、计数排序

### 问题一：.实现对数组 `[2, 1, 3, 4, 1, 2, 1, 5, 4]` 的快速排序并画出流程图

#### 算法原理

快速排序的主要思想是通过划分将待排序的序列分成前后两部分，其中前一部分的数据都比后一部分的数据要小，然后再递归调用函数对两部分的序列分别进行快速排序，以此使整个序列达到有序

流程图来自算法笔记：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200428203003.png"/>
<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200428203115.png"/>

#### 实验截图

对数组 `[2, 1, 3, 4, 1, 2, 1, 5, 4]` 的实验截图

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200428202318.png" />

#### 结果分析

**时间复杂度**：基于*随机选取*主元的快速排序时间复杂度为期望 $O(nlogn)$，其中 $n$ 为数组的长度

**空间复杂度**：$O(h)$，其中 $h$ 为快速排序递归调用的层数。我们需要额外的 $O(h)$ 的递归调用的栈空间，由于划分的结果不同导致了快速排序递归调用的层数也会不同，最坏情况下需 $O(n)$ 的空间，最优情况下每次都平衡，此时整个递归树高度为 $log n$，空间复杂度为 $O(log n)$。

#### 代码

```java
import java.util.Arrays;
import java.util.Random;

public class QuickSort {
    public static int[] sortArray(int[] nums) {
        quickSort(nums, 0, nums.length - 1);
        return nums;
    }

    private static void quickSort(int[] nums, int l, int r) {
        if (l < r) {
            int pos = partition(nums, l, r);
            quickSort(nums, l, pos - 1);
            quickSort(nums, pos + 1, r);
        }
    }

    private static int partition(int[] nums, int l, int r) {
        Random rand = new Random();
        int randIndex = rand.nextInt(r - l + 1) + l;
        int pivot = nums[randIndex];
        swap(nums, randIndex, l);
        while (l < r) {
            while (r > l && nums[r] > pivot) {
                r--;
            }
            nums[l] = nums[r];
            while (l < r && nums[l] <= pivot) {
                l++;
            }
            nums[r] = nums[l];
        }
        nums[l] = pivot;
        return l;
    }

    private static void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }

    public static void main(String[] args) {
        System.out.println(Arrays.toString(sortArray(new int[]{2, 1, 3, 4, 1, 2, 1, 5, 4})));
    }
}

```

### 问题二：实现对数组 `[95, 94, 91, 98, 99, 90, 99, 93, 91, 92]` 的计数排序并画出流程图

#### 算法原理

计数排序本质上是一种特殊的桶排序，当桶的个数取最大 (maxV - minV + 1) 的时候，就变成了计数排序

计数排序的过程是创建一个长度为数组中最小和最大元素之差的数组，分别对应数组中的每个元素，然后用这个新的数组来统计每个元素出现的频率，然后遍历新的数组，根据每个元素出现的频率把元素放回到老的数组中，得到已经排好序的数组。

流程图，截自 [visualgo](https://visualgo.net/zh)：

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/gi76s-xn7oj.gif"/>

#### 实验截图

对数组 `[95, 94, 91, 98, 99, 90, 99, 93, 91, 92]` 的实验截图

<img src="https://cdn.jsdelivr.net/gh/JingqingLin/ImageHosting@master/img/20200428210215.png"/>

#### 结果分析

**时间复杂度**：$O(n + k)$（$k$ 为数组元素最大最小值之差）

**空间复杂度**：$O(k)$（额外空间复杂度），若原数组不能改变，则为 $O(n + k)$

#### 代码

```java
import java.util.Arrays;

public class CountSort {
    public static int[] sortArray(int[] nums) {
        countSort(nums);
        return nums;
    }

    private static void countSort(int[] nums) {
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;
        // 找到最大最小值
        for (int num : nums) {
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        // 建立新数组
        int[] count = new int[max - min + 1];
        // 统计每个元素出现频率
        for (int num : nums) {
            count[num - min]++;
        }
        int cur = 0;
        // 根据出现频率把计数数组中的元素放回到旧数组中
        for (int i = 0; i < count.length; i++) {
            while (count[i] > 0) {
                nums[cur++] = i + min;
                count[i]--;
            }
        }
    }

    public static void main(String[] args) {
        System.out.println(Arrays.toString(sortArray(new int[]{95, 94, 91, 98, 99, 90, 99, 93, 91, 92})));
    }
}

```