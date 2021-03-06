## 面试必备：八种排序算法原理及Java实现

来源：[https://juejin.im/post/5b95da8a5188255c775d8124](https://juejin.im/post/5b95da8a5188255c775d8124)

时间 2018-10-11 10:24:07

 
排序算法分为内部排序和外部排序，内部排序把数据记录放在内存中进行排序，而外部排序因排序的数据量大，内存不能一次容纳全部的排序记录，所以在排序过程中需要访问外存。
 
 ![][0]
 
经常提及的八大排序算法指的就是内部排序的八种算法，分别是冒泡排序、快速排序、直接插入排序、希尔排序、简单选择排序、堆排序、归并排序和基数排序，如果按原理划分，冒泡排序和快速排序都属于交换排序，直接插入排序和希尔排序属于插入排序，而简单选择排序和堆排序属于选择排序，如上图所示。
 
### 2. 冒泡排序
 
#### 2.1 基本思想
 
冒泡排序（Bubble Sort）是一种简单的排序算法。它重复访问要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来。访问数列的工作是重复地进行直到没有再需要交换的数据，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端，像水中的气泡从水底浮到水面。
 
 ![][1]
 
#### 2.2 算法描述
 
冒泡排序算法的算法过程如下：
 
①. 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
 
②. 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。
 
③. 针对所有的元素重复以上的步骤，除了最后一个。
 
④. 持续每次对越来越少的元素重复上面的步骤①~③，直到没有任何一对数字需要比较。
 
#### 2.3 代码实现

```java
package com.fufu.algorithm.sort;

import java.util.Arrays;

/**
 * 冒泡排序
 * Created by zhoujunfu on 2018/8/2.
 */
public class BubbleSort {
    public static void sort(int[] array) {
        if (array == null || array.length == 0) {
            return;
        }

        int length = array.length;
        //外层：需要length-1次循环比较
        for (int i = 0; i < length - 1; i++) {
            //内层：每次循环需要两两比较的次数，每次比较后，都会将当前最大的数放到最后位置，所以每次比较次数递减一次
            for (int j = 0; j < length - 1 - i; j++) {
                if (array[j] > array[j+1]) {
                    //交换数组array的j和j+1位置的数据
                    swap(array, j, j+1);
                }
            }
        }
    }

    /**
     * 交换数组array的i和j位置的数据
     * @param array 数组
     * @param i 下标i
     * @param j 下标j
     */
    public static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

```
 
#### 2.4 算法效率
 
冒泡排序是稳定的排序算法，最容易实现的排序, 最坏的情况是每次都需要交换, 共需遍历并交换将近n²/2次, 时间复杂度为O(n²). 最佳的情况是内循环遍历一次后发现排序是对的, 因此退出循环, 时间复杂度为O(n). 平均来讲, 时间复杂度为O(n²). 由于冒泡排序中只有缓存的temp变量需要内存空间, 因此空间复杂度为常量O(1)。
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(n <sup>2</sup> ) | O(n) | O(n <sup>2</sup> ) | O(1) | 
 
 
#### 2.5 交换数字的三种方法
 
我们从冒泡排序的代码中看到了交换两个数字的方法 swap(int[] array, int i, int j)，这里使用了临时变量，而交换数字主要有三种方法，临时变量法、算术法、位运算法、面试中经常会问到，这里简单说一下，代码如下：

```java
package com.fufu.algorithm.sort;

import java.util.Arrays;

/**
 * Created by zhoujunfu on 2018/9/10.
 */
public class SwapDemo {

    public static void main(String[] args) {
        // 临时变量法
        int[] array = new int[]{10, 20};
        System.out.println(Arrays.toString(array));
        swapByTemp(array, 0, 1);
        System.out.println(Arrays.toString(array));
        
        // 算术法
        array = new int[]{10, 20};
        swapByArithmetic(array, 0, 1);
        System.out.println(Arrays.toString(array));
        
        // 位运算法
        array = new int[]{10, 20};
        swapByBitOperation(array, 0, 1);
        System.out.println(Arrays.toString(array));
    }

    /**
     * 通过临时变量交换数组array的i和j位置的数据
     * @param array 数组
     * @param i 下标i
     * @param j 下标j
     */
    public static void swapByTemp(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    /**
     * 通过算术法交换数组array的i和j位置的数据（有可能溢出）
     * @param array 数组
     * @param i 下标i
     * @param j 下标j
     */
    public static void  swapByArithmetic(int[] array, int i, int j) {
        array[i] = array[i] + array[j];
        array[j] = array[i] - array[j];
        array[i] = array[i] - array[j];
    }


    /**
     * 通过位运算法交换数组array的i和j位置的数据
     * @param array 数组
     * @param i 下标i
     * @param j 下标j
     */
    public static void  swapByBitOperation(int[] array, int i, int j) {
        array[i] = array[i]^array[j];
        array[j] = array[i]^array[j]; //array[i]^array[j]^array[j]=array[i]
        array[i] = array[i]^array[j]; //array[i]^array[j]^array[i]=array[j]
    }
}

```
 
### 3. 快速排序
 
#### 3.1 基本思想
 
快速排序（Quicksort）是对冒泡排序的一种改进，借用了分治的思想，由C. A. R. Hoare在1962年提出。它的基本思想是：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
 
#### 3.2 算法描述
 
快速排序使用分治策略来把一个序列（list）分为两个子序列（sub-lists）。步骤为：
 
①. 从数列中挑出一个元素，称为”基准”（pivot）。
 
②. 重新排序数列，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面（相同的数可以到任一边）。在这个分区结束之后，该基准就处于数列的中间位置。这个称为分区（partition）操作。
 
③. 递归地（recursively）把小于基准值元素的子数列和大于基准值元素的子数列排序。
 
递归到最底部时，数列的大小是零或一，也就是已经排序好了。这个算法一定会结束，因为在每次的迭代（iteration）中，它至少会把一个元素摆到它最后的位置去。
 
 ![][2]
 
#### 3.3 代码实现
 
①. 挖坑法 用伪代码描述如下：
 
（1）low = L; high = R; 将基准数挖出形成第一个坑a[low]。
 
（2）high--，由后向前找比它小的数，找到后挖出此数填前一个坑a[low]中。
 
（3）low++，由前向后找比它大的数，找到后也挖出此数填到前一个坑a[high]中。
 
（4）再重复执行②，③二步，直到low==high，将基准数填入a[low]中。
 
举例说明： 一个无序数组：[4, 3, 7, 5, 10, 9, 1, 6, 8, 2]
 
（1）随便先挖个坑，就在第一个元素（基准元素）挖坑，挖出来的“萝卜”（第一个元素4）在“篮子”（临时变量）里备用。 挖完之后的数组是这样：[ 坑, 3, 7, 5, 10, 9, 1, 6, 8,2]
 
（2）挖右坑填左坑：从右边开始，找个比“萝卜”（元素4）小的元素，挖出来，填到前一个坑里面。 填坑之后：[ 2, 3, 7, 5, 10, 9, 1, 6, 8,坑]
 
（3）挖左坑填右坑：从左边开始，找个比“萝卜”（元素4）大的元素，挖出来，填到右边的坑里面。 填坑之后：[ 2, 3,坑, 5, 10, 9, 1, 6, 8, 7]
 
（4）挖右坑填左坑：从右边开始，找个比“萝卜”（元素4）小的元素，挖出来，填到前一个坑里面。 填坑之后：[ 2, 3, 1, 5, 10, 9,坑, 6, 8, 7]
 
（5）挖左坑填右坑：从左边开始，找个比“萝卜”（元素4）大的元素，挖出来，填到右边的坑里面。 填坑之后：[ 2, 3, 1,坑, 10, 9, 5, 6, 8, 7]
 
（6）挖右坑填左坑：从右边开始，找个比“萝卜”（元素4）小的元素，挖出来，填到前一个坑里面，这一次找坑的过程中，找到了上一次挖的坑了，说明可以停了，用篮子里的的萝卜，把这个坑填了就行了，并且返回这个坑的位置，作为分而治之的中轴线。 填坑之后：[ 2, 3, 1, 4, 10, 9, 5, 6, 8, 7]
 
上面的步骤中，第2，4, 6其实都是一样的操作，3和5的操作也是一样的，代码如下：

```java
/**
     *  快速排序（挖坑法递归）
     * @param arr   待排序数组
     * @param low   左边界
     * @param high  右边界
     */
    public static void sort(int arr[], int low, int high) {
        if (arr == null || arr.length <= 0) {
            return;
        }
        if (low >= high) {
            return;
        }

        int left = low;
        int right = high;
        int temp = arr[left]; //挖坑1：保存基准的值

        while (left < right) {
            while (left < right && arr[right] >= temp) {
                right--;
            }
            arr[left] = arr[right]; //坑2：从后向前找到比基准小的元素，插入到基准位置坑1中
            while (left < right && arr[left] <= temp) {
                left ++;
            }
            arr[right] = arr[left]; //坑3：从前往后找到比基准大的元素，放到刚才挖的坑2中
        }
        arr[left] = temp; //基准值填补到坑3中，准备分治递归快排
        System.out.println("Sorting: " + Arrays.toString(arr));
        sort(arr, low, left-1);
        sort(arr, left + 1, high);
    }
```
 
②. 左右指针法
 
用伪代码描述如下：
 
（1）low = L; high = R; 选取a[low]作为关键字记录为key。
 
（2）high--，由后向前找比它小的数
 
（3）low++，由前向后找比它大的数
 
（4）交换第（2）、（3）步找到的数
 
（5）重复（2）、（3），一直往后找，直到left和right相遇，这时将key和a[low]交换位置。
 
代码如下：

```java
/**
 * 快速排序
 * Created by zhoujunfu on 2018/8/6.
 */
public class QuickSort {
    /**
     * 快速排序（左右指针法）
     * @param arr 待排序数组
     * @param low 左边界
     * @param high 右边界
     */
    public static void sort2(int arr[], int low, int high) {
        if (arr == null || arr.length <= 0) {
            return;
        }
        if (low >= high) {
            return;
        }

        int left = low;
        int right = high;

        int key = arr[left];

        while (left < right) {
            while (left < right && arr[right] >= key) {
                right--;
            }
            while (left < right && arr[left] <= key) {
                left++;
            }
            if (left < right) {
                swap(arr, left, right);
            }
        }
        swap(arr, low, left);
        System.out.println("Sorting: " + Arrays.toString(arr));
        sort2(arr, low, left - 1);
        sort2(arr, left + 1, high);
    }

    public static void swap(int arr[], int low, int high) {
        int tmp = arr[low];
        arr[low] = arr[high];
        arr[high] = tmp;
    }
}
```
 
#### 3.4 算法效率
 
快速排序并不稳定，快速排序每次交换的元素都有可能不是相邻的, 因此它有可能打破原来值为相同的元素之间的顺序。
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(nlogn) | O(nlogn) | O(n <sup>2</sup> ) | O(1) | 
 
 
### 4. 直接插入排序
 
#### 4.1 基本思想
 
直接插入排序的基本思想是：将数组中的所有元素依次跟前面已经排好的元素相比较，如果选择的元素比已排序的元素小，则交换，直到全部元素都比较过为止。
 
 ![][3]
 
#### 4.2 算法描述
 
一般来说，插入排序都采用in-place在数组上实现。具体算法描述如下：
 
①. 从第一个元素开始，该元素可以认为已经被排序
 
②. 取出下一个元素，在已经排序的元素序列中从后向前扫描
 
③. 如果该元素（已排序）大于新元素，将该元素移到下一位置
 
④. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
 
⑤. 将新元素插入到该位置后
 
⑥. 重复步骤②~⑤
 
 ![][4]
 
#### 4.3 代码实现
 
提供两种写法，一种是移位法，一种是交换法。移位法是完全按照以上算法描述实，再插入过程中将有序序列中比待插入数字大的数据向后移动，由于移动时会覆盖待插入数据，所以需要额外的临时变量保存待插入数据，代码实现如下：
 
①. 移位法：

```java
public static void sort(int[] a) {
        if (a == null || a.length == 0) {
            return;
        }

        for (int i = 1; i < a.length; i++) {
            int j = i - 1;
            int temp = a[i]; // 先取出待插入数据保存，因为向后移位过程中会把覆盖掉待插入数
            while (j >= 0 && a[j] > a[i]) { // 如果待是比待插入数据大，就后移
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = temp; // 找到比待插入数据小的位置，将待插入数据插入
        }
    }
```
 
而交换法不需求额外的保存待插入数据，通过不停的向前交换带插入数据，类似冒泡法，直到找到比它小的值，也就是待插入数据找到了自己的位置。
 
②. 交换法：

```java
public static void sort2(int[] arr) {
        if (arr == null || arr.length == 0) {
            return;
        }

        for (int i = 1; i < arr.length; i ++) {
            int j = i - 1;
            while (j >= 0 && arr[j] > arr[i]) {
                arr[j + 1] = arr[j] + arr[j+1];      //只要大就交换操作
                arr[j] = arr[j + 1] - arr[j];
                arr[j + 1] = arr[j + 1] - arr[j];
                System.out.println("Sorting:  " + Arrays.toString(arr));
            }
        }
    }
```
 
#### 4.4 算法效率
 
直接插入排序不是稳定的排序算法。
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(n <sup>2</sup> ) | O(n) | O(n <sup>2</sup> ) | O(1) | 
 
 
### 5.希尔排序
 
希尔排序，也称递减增量排序算法，1959年Shell发明。是插入排序的一种高速而稳定的改进版本。
 
希尔排序是先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录“基本有序”时，再对全体记录进行依次直接插入排序。
 
#### 5.1 基本思想
 
将待排序数组按照步长gap进行分组，然后将每组的元素利用直接插入排序的方法进行排序；每次再将gap折半减小，循环上述操作；当gap=1时，利用直接插入，完成排序。
 
可以看到步长的选择是希尔排序的重要部分。只要最终步长为1任何步长序列都可以工作。一般来说最简单的步长取值是初次取数组长度的一半为增量，之后每次再减半，直到增量为1。更好的步长序列取值可以参考维基百科。
 
#### 5.2 算法描述
 
①. 选择一个增量序列t1，t2，…，tk，其中ti>tj，tk=1；（一般初次取数组半长，之后每次再减半，直到增量为1）
 
②. 按增量序列个数k，对序列进行k 趟排序；
 
③. 每趟排序，根据对应的增量ti，将待排序列分割成若干长度为m 的子序列，分别对各子表进行直接插入排序。仅增量因子为1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。
 
 ![][5]
 
在上面这幅图中： 初始时，有一个大小为 10 的无序序列。
 
在第一趟排序中，我们不妨设 gap1 = N / 2 = 5，即相隔距离为 5 的元素组成一组，可以分为 5 组。
 
接下来，按照直接插入排序的方法对每个组进行排序。
 
在第二趟排序中，我们把上次的 gap 缩小一半，即 gap2 = gap1 / 2 = 2 (取整数)。这样每相隔距离为 2 的元素组成一组，可以分为 2 组。
 
按照直接插入排序的方法对每个组进行排序。
 
在第三趟排序中，再次把 gap 缩小一半，即gap3 = gap2 / 2 = 1。 这样相隔距离为 1 的元素组成一组，即只有一组。 按照直接插入排序的方法对每个组进行排序。此时，排序已经结束。
 
需要注意一下的是，图中有两个相等数值的元素 5 和 5 。我们可以清楚的看到，在排序过程中，两个元素位置交换了。 所以，希尔排序是不稳定的算法。
 
#### 5.3 代码实现

```java
public class ShellSort {

    public static void sort(int[] arr) {
        int gap = arr.length / 2;
        for (;gap > 0; gap = gap/2) {
            for (int j = 0; (j + gap) < arr.length; j++) { //不断缩小gap，直到1为止
                for (int k = 0; (k + gap) < arr.length; k+=gap) { //使用当前gap进行组内插入排序
                    if (arr[k] > arr[k+gap]) { //交换操作
                        arr[k] = arr[k] + arr[k+gap];
                        arr[k+gap] = arr[k] - arr[k+gap];
                        arr[k] = arr[k] - arr[k+gap];
                        System.out.println("    Sorting:  " + Arrays.toString(arr));
                    }
                }
            }
        }
    }
}
```
 
#### 5.4 算法效率
 
不稳定排序算法，希尔排序第一个突破O(n <sup>2</sup> )的排序算法；是简单插入排序的改进版；它与插入排序的不同之处在于，它会优先比较距离较远的元素，直接插入排序是稳定的；而希尔排序是不稳定的，希尔排序的时间复杂度和步长的选择有关，常用的是Shell增量排序，也就是N/2的序列，Shell增量序列不是最好的增量序列，其他还有Hibbard增量序列、Sedgewick 增量序列等，具体可以参考，希尔排序增量序列简介。
 
### 6.选择排序
 
#### 6.1 基本思想
 
在未排序序列中找到最小（大）元素，存放到未排序序列的起始位置。在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。
 
#### 6.2 算法描述
 
①. 从待排序序列中，找到关键字最小的元素；
 
②. 如果最小元素不是待排序序列的第一个元素，将其和第一个元素互换；
 
③. 从余下的 N - 1 个元素中，找出关键字最小的元素，重复①、②步，直到排序结束。
 
 ![][6]
 
#### 6.3 代码实现

```java
public class SelectSort {
    public static void sort(int[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            int min = i;
            for (int j = i+1; j < arr.length; j ++) { //选出之后待排序中值最小的位置
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            if (min != i) {
                arr[min] = arr[i] + arr[min];
                arr[i] = arr[min] - arr[i];
                arr[min] = arr[min] - arr[i];
            }
        }
    }
```
 
#### 6.4 算法效率
 
不稳定排序算法，选择排序的简单和直观名副其实，这也造就了它出了名的慢性子，无论是哪种情况，哪怕原数组已排序完成，它也将花费将近n²/2次遍历来确认一遍。 唯一值得高兴的是，它并不耗费额外的内存空间。
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(n <sup>2</sup> ) | O(n <sup>2</sup> ) | O(n <sup>2</sup> ) | O(1) | 
 
 
### 7.归并排序
 
归并排序是建立在归并操作上的一种有效的排序算法，1945年由约翰·冯·诺伊曼首次提出。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用，且各层分治递归可以同时进行。
 
#### 7.1 基本思想
 
归并排序算法是将两个（或两个以上）有序表合并成一个新的有序表，即把待排序序列分为若干个子序列，每个子序列是有序的。然后再把有序子序列合并为整体有序序列。
 
 ![][7]
 
#### 7.2 算法描述
 
采用递归法： ①. 将序列每相邻两个数字进行归并操作，形成 floor(n/2)个序列，排序后每个序列包含两个元素；
 
②. 将上述序列再次归并，形成 floor(n/4)个序列，每个序列包含四个元素；
 
③. 重复步骤②，直到所有元素排序完毕
 
 ![][8]
 
#### 7.3 代码实现

```java
package com.fufu.algorithm.sort;

import java.util.Arrays;

/**
 * Created by zhoujunfu on 2018/8/10.
 */
public class MergeSort {

    public static int[] sort(int [] a) {
        if (a.length <= 1) {
            return a;
        }
        int num = a.length >> 1;
        int[] left = Arrays.copyOfRange(a, 0, num);
        int[] right = Arrays.copyOfRange(a, num, a.length);
        return mergeTwoArray(sort(left), sort(right));
    }

    public static int[] mergeTwoArray(int[] a, int[] b) {
        int i = 0, j = 0, k = 0;
        int[] result = new int[a.length + b.length]; // 申请额外空间保存归并之后数据

        while (i < a.length && j < b.length) { //选取两个序列中的较小值放入新数组
            if (a[i] <= b[j]) {
                result[k++] = a[i++];
            } else {
                result[k++] = b[j++];
            }
        }

        while (i < a.length) { //序列a中多余的元素移入新数组
            result[k++] = a[i++];
        }
        while (j < b.length) {//序列b中多余的元素移入新数组
            result[k++] = b[j++];
        }
        return result;
    }

    public static void main(String[] args) {
        int[] b = {3, 1, 5, 4};
        System.out.println(Arrays.toString(sort(b)));
    }
}
```
 
#### 7.4 算法效率
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(nlogn) | O(nlogn) | O(nlogn) | O(n) | 
 
 
稳定排序算法，从效率上看，归并排序可算是排序算法中的”佼佼者”. 假设数组长度为n，那么拆分数组共需logn, 又每步都是一个普通的合并子数组的过程，时间复杂度为O(n)， 故其综合时间复杂度为O(nlogn)。另一方面， 归并排序多次递归过程中拆分的子数组需要保存在内存空间， 其空间复杂度为O(n)。 和选择排序一样，归并排序的性能不受输入数据的影响，但表现比选择排序好的多，因为始终都是O(nlogn）的时间复杂度。代价是需要额外的内存空间。
 
### 8.基数排序
 
基数排序（Radix sort）是一种非比较型整数排序算法，其原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。
 
#### 8.1 基本思想
 
将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后，数列就变成一个有序序列。
 
基数排序按照优先从高位或低位来排序有两种实现方案：
   **`MSD（Most significant digital）`**  从最左侧高位开始进行排序。先按k1排序分组, 同一组中记录, 关键码k1相等, 再对各组按k2排序分成子组, 之后, 对后面的关键码继续这样的排序分组, 直到按最次位关键码kd对各子组排序后. 再将各组连接起来, 便得到一个有序序列。MSD方式适用于位数多的序列。
   **`LSD（Least significant digital）`**  从最右侧低位开始进行排序。先从kd开始排序，再对kd-1进行排序，依次重复，直到对k1排序后便得到一个有序序列。LSD方式适用于位数少的序列。
 
下图是LSD基数排序的示意图：
 
 ![][9]
 
#### 8.2 算法描述
 
以LSD为例，从最低位开始，具体算法描述如下：
 
①. 取得数组中的最大数，并取得位数； ②. arr为原始数组，从最低位开始取每个位组成radix数组； ③. 对radix进行计数排序（利用计数排序适用于小范围数的特点）；
 
#### 8.3 代码实现
   **`基数排序`**  ：通过序列中各个元素的值，对排序的N个元素进行若干趟的“分配”与“收集”来实现排序。
   **`分配`**  ：我们将L[i]中的元素取出，首先确定其个位上的数字，根据该数字分配到与之序号相同的桶中
   **`收集`**  ：当序列中所有的元素都分配到对应的桶中，再按照顺序依次将桶中的元素收集形成新的一个待排序列L[]。对新形成的序列L[]重复执行分配和收集元素中的十位、百位…直到分配完该序列中的最高位，则排序结束

```java
package com.fufu.algorithm.sort;

import java.util.Arrays;

/**
 * Created by zhoujunfu on 2018/9/11.
 * 基数排序LSD
 */
public class RadixSort {

    public static void main(String[] args) {
        int[] array = {10, 20, 5, 4, 100};
        sort(array);

    }

    public static void sort(int[] a) {

        if (a == null || a.length < 0) {
            return;
        }

        int max = a[0];
        for (int i = 0; i <a.length; i++) {
            if (a[i] > max) {
                max = a[i];
            }
        }
        System.out.println("max, " + max);

        int maxDigit = 0;
        while (max != 0) {
            max = max / 10;
            maxDigit++;
        }
        System.out.println("maxDigit, " + maxDigit);

        int[][] buckets = new int[10][a.length];
        int base = 10;

        //从低位到高位，对每一位遍历，将所有元素分配到桶中
        for (int i = 0; i < maxDigit; i++) {
            int[] bucketLen = new int[10];  //存储各个桶中存储元素的数量

            //收集：将不同桶里数据挨个捞出来,为下一轮高位排序做准备,由于靠近桶底的元素排名靠前,因此从桶底先捞
            for (int j = 0; j < a.length; j++) {
                int whichBucket = (a[j] % base) / (base / 10);
                buckets[whichBucket][bucketLen[whichBucket]] = a[j];
                bucketLen[whichBucket]++;
            }

            int k = 0;
            //收集：将不同桶里数据挨个捞出来,为下一轮高位排序做准备,由于靠近桶底的元素排名靠前,因此从桶底先捞
            for (int l = 0; l < buckets.length; l++) {
                for (int m =0; m < bucketLen[l]; m++) {
                    a[k++] = buckets[l][m];
                }
            }
            System.out.println("Sorting: " + Arrays.toString(a));
            base *= 10;
        }
    }
}
```
 
#### 8.4 算法效率
 
基数排序不改变相同元素之间的相对顺序，因此它是稳定的排序算法，以下是基数排序算法复杂度：
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(d*(n+r)) | O(d*(n+r)) | O(d*(n+r)) | O(n+r) | 
 
 
其中，d 为位数，r 为基数，n 为原数组个数。在基数排序中，因为没有比较操作，所以在复杂上，最好的情况与最坏的情况在时间上是一致的，均为 O(d*(n + r))。
 
基数排序更适合用于对时间, 字符串等这些整体权值未知的数据进行排序，适用于。
 
(1)数据范围较小，建议在小于1000
 
(2)每个数值都要大于等于0
 
基数排序 vs 计数排序 vs 桶排序
 
这三种排序算法都利用了桶的概念，但对桶的使用方法上有明显差异：
 
基数排序：根据键值的每位数字来分配桶
 
计数排序：每个桶只存储单一键值
 
桶排序：每个桶存储一定范围的数值
 
计数排序和桶排序在这篇文章里具体就不写了，有需要的可以自行百度。
 
### 9.堆排序
 
看堆排序之前先介绍一下面几个概念：
 
完全二叉树： 若设二叉树的深度为h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，第 h 层所有的结点都连续集中在最左边，这就是完全二叉树，很好理解如下图所示。
 
 ![][10]
 
堆： 堆是具有以下性质的完全二叉树，每个结点的值都大于或等于其左右孩子结点的值，称为大顶堆；或者每个结点的值都小于或等于其左右孩子结点的值，称为小顶堆。如下图：
 
 ![][11]
 
同时，我们对堆中的结点按层进行编号，将这种逻辑结构映射到数组中就是下面这个样子：
 
 ![][12]
 
该数组从逻辑上讲就是一个堆结构，我们用简单的公式来描述一下堆的定义就是：
 
大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]
 
小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]
 
ok，了解了这些定义。接下来，我们来看看堆排序的基本思想及基本步骤：
 
#### 9.1 基本思想
 
堆排序的基本思想是：将待排序序列构造成一个大顶堆，此时，整个序列的最大值就是堆顶的根节点。将其与末尾元素进行交换，此时末尾就为最大值。然后将剩余n-1个元素重新构造成一个堆，这样会得到n个元素的次小值。如此反复执行，便能得到一个有序序列了。
 
#### 9.2 算法描述
 
步骤一 构造初始堆。将给定无序序列构造成一个大顶堆（一般升序采用大顶堆，降序采用小顶堆)。
 
1.假设给定无序序列结构如下
 
 ![][13]
 
2.此时我们从最后一个非叶子结点开始（叶结点自然不用调整，第一个非叶子结点 arr.length/2-1=5/2-1=1，也就是下面的6结点），从左至右，从下至上进行调整。
 
 ![][14]
 
3.找到第二个非叶节点4，由于[4,9,8]中9元素最大，4和9交换。
 
 ![][15]
 
这时，交换导致了子根[4,5,6]结构混乱，继续调整，[4,5,6]中6最大，交换4和6。
 
 ![][16]
 
此时，我们就将一个无需序列构造成了一个大顶堆。
 
步骤二 将堆顶元素与末尾元素进行交换，使末尾元素最大。然后继续调整堆，再将堆顶元素与末尾元素交换，得到第二大元素。如此反复进行交换、重建、交换。
 
 ![][17]
 
b.重新调整结构，使其继续满足堆定义
 
 ![][18]
 
c.再将堆顶元素8与末尾元素5进行交换，得到第二大元素8.
 
 ![][19]
 
后续过程，继续进行调整，交换，如此反复进行，最终使得整个序列有序
 
 ![][20]
 
再简单总结下堆排序的基本思路：
 
a.将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆;
 
b.将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端;
 
c.重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，反复执行调整+交换步骤，直到整个序列有序。
 
#### 9.3 算法实现

```java
package com.fufu.algorithm.sort;

import java.util.Arrays;

/**
 * Created by zhoujunfu on 2018/9/26.
 */
public class HeapSort {

    public static void main(String []args){
        int []arr = {4,6,8,5,9};
        sort(arr);
        System.out.println(Arrays.toString(arr));
    }
    public static void sort(int []arr){
        //1.构建大顶堆
        for(int i=arr.length/2-1;i>=0;i--){
            //从第一个非叶子结点从下至上，从右至左调整结构
            adjustHeap(arr,i,arr.length);
        }
        //2.调整堆结构+交换堆顶元素与末尾元素
        for(int j=arr.length-1;j>0;j--){
            swap(arr,0,j);//将堆顶元素与末尾元素进行交换
            adjustHeap(arr,0,j);//重新对堆进行调整
        }

    }

    /**
     * 调整大顶堆（仅是调整过程，建立在大顶堆已构建的基础上）
     * @param arr
     * @param i
     * @param length
     */
    public static void adjustHeap(int []arr,int i,int length){
        int temp = arr[i];//先取出当前元素i
        for(int k=i*2+1;k<length;k=k*2+1){//从i结点的左子结点开始，也就是2i+1处开始
            if(k+1<length && arr[k]<arr[k+1]){//如果左子结点小于右子结点，k指向右子结点
                k++;
            }
            if(arr[k] >temp){//如果子节点大于父节点，将子节点值赋给父节点（不用进行交换）
                arr[i] = arr[k];
                i = k;
            }else{
                break;
            }
        }
        arr[i] = temp;//将temp值放到最终的位置
    }

    /**
     * 交换元素
     * @param arr
     * @param a
     * @param b
     */
    public static void swap(int []arr,int a ,int b){
        int temp=arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}
```
 
#### 9.4 算法效率
 
由于堆排序中初始化堆的过程比较次数较多, 因此它不太适用于小序列。同时由于多次任意下标相互交换位置, 相同元素之间原本相对的顺序被破坏了, 因此, 它是不稳定的排序。
 
①. 建立堆的过程, 从length/2 一直处理到0, 时间复杂度为O(n);
 
②. 调整堆的过程是沿着堆的父子节点进行调整, 执行次数为堆的深度, 时间复杂度为O(lgn);
 
③. 堆排序的过程由n次第②步完成, 时间复杂度为O(nlgn).
 
| 平均时间复杂度 | 最好情况 | 最坏情况 | 空间复杂度 |
| - | - | - | - | 
| O(nlogn) | O(nlogn) | O(nlogn) | O(1) | 
 
 
### 10. 总结
 
 ![][21]
 
从时间复杂度来说：
 
(1). 平方阶O(n²)排序：各类简单排序：直接插入、直接选择和冒泡排序；
 
(2). 线性对数阶O(nlog₂n)排序：快速排序、堆排序和归并排序；
 
(3). O(n1+§))排序，§是介于0和1之间的常数：希尔排序
 
(4). 线性阶O(n)排序：基数排序，此外还有桶、箱排序。
 
时间复杂度极限：
 
当被排序的数有一些性质的时候（比如是整数，比如有一定的范围），排序算法的复杂度是可以小于O(nlgn)的。比如：
 
计数排序 复杂度O( k+n) 要求：被排序的数是0~k范围内的整数
 
基数排序 复杂度O( d(k+n) ) 要求：d位数，每个数位有k个取值
 
桶排序 复杂度 O( n ) （平均） 要求：被排序数在某个范围内，并且服从均匀分布
 
但是，当被排序的数不具有任何性质的时候，一般使用基于比较的排序算法，而基于比较的排序算法时间复杂度的下限必须是O( nlgn) 。参考[很多高效排序算法的代价是 nlogn，难道这是排序算法的极限了吗][22] ？
 
说明 当原表有序或基本有序时，直接插入排序和冒泡排序将大大减少比较次数和移动记录的次数，时间复杂度可降至O（n）；
 
而快速排序则相反，当原表基本有序时，将蜕化为冒泡排序，时间复杂度提高为O（n2）；
 
原表是否有序，对简单选择排序、堆排序、归并排序和基数排序的时间复杂度影响不大。


[22]: https://link.juejin.im?target=https%3A%2F%2Fwww.zhihu.com%2Fquestion%2F24516934
[0]: ./img/F7bQfuR.png
[1]: ./img/VZrM7nn.gif
[2]: ./img/6RrMzia.gif
[3]: ./img/MbyAbm3.gif
[4]: ./img/nU3MJrY.gif
[5]: ./img/eaENbmi.png
[6]: ./img/iuqamuJ.gif
[7]: ./img/Ab6Nvyy.gif
[8]: ./img/VfQRbiY.gif
[9]: ./img/QbYRNra.gif
[10]: ./img/ZZFZb2E.jpg
[11]: ./img/32qE3uY.png
[12]: ./img/m6RriyQ.png
[13]: ./img/QRzQfqn.png
[14]: ./img/EfMbEbF.png
[15]: ./img/2MjuMjb.png
[16]: ./img/beiUzuE.png
[17]: ./img/nIbMVrY.png
[18]: ./img/NFFJvab.png
[19]: ./img/rimieeN.png
[20]: ./img/eEVfeez.png
[21]: ./img/UVj6fuZ.png