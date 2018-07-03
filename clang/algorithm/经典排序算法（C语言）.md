## 经典排序算法（C语言）

来源：[http://www.cnblogs.com/chownjy/p/8663069.html](http://www.cnblogs.com/chownjy/p/8663069.html)

时间 2018-03-28 11:59:00

 
本文章包括所有基本排序算法（和其中一些算法的改进算法）：
 
直接插入排序、希尔排序、直接选择排序、堆排序、冒泡排序、快速排序、归并排序、基数排序。
 
## 算法复杂度比较：
 
![][0]
 
## 算法分类
 
![][1]
 
### 一、直接插入排序
 
一个插入排序是另一种简单排序，它的思路是：每次从未排好的序列中选出第一个元素插入到已排好的序列中。
 
它的算法步骤可以大致归纳如下：
 

* 从未排好的序列中拿出首元素，并把它赋值给temp变量； 
* 从排好的序列中，依次与temp进行比较，如果元素比temp大，则将元素后移（实际上放置temp的元素位置已经空出） 
* 直到找到一个元素比temp小， 将temp放入该位置； 
 

因此，从上面的描述中我们可以发现，直接插入排序可以用两个循环完成：
 
第一层循环：遍历待比较的所有数组元素
 
第二层循环：将本轮选择的元素(selected)与已经排好序的元素(ordered)相比较。
 
如果：selected > ordered，那么将二者交换
 
```c
#include <stdio.h>
void InsertSort(int *a, int len)
{
    int i, j, tmp;
    for(i=1; i<len; i++){         //i指向无序区第一个元素
        tmp = a[i];
        j = i - 1;                //j指向有序去第一个元素
        // j往前遍历，找到比a[i]小的，插入到此处。比a[i]大的后移
        while(j>=0 && tmp<a[j]){   //小于号换成大于号则是从大到小排序
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;  //插入到空出来的位置
    }
    
    return;
}
int main()
{
    int a[] = {1,3,63,5,78,9,12,52,8};
    int n = sizeof(a)/sizeof(int),i;
    InsertionSort(a, n);
    for(i=0; i<n; i++)
        printf("%d ", a[i]);
    return 0;
}
```
 
### 二、折半插入排序
 
与直接插入算法的区别在于：在有序表中寻找待排序数据的正确位置时，使用了折半查找/二分查找。
 
减少了比较的次数，但没有减少插入的次数。时间复杂度仍为O(n^2)，但比直接插入排序稍微快一点。
 
```c
void BinaryInsertSort(int *a, int len)
{
    int i, j, low, high, tmp;
    for(i=1; i<len; i++){
        tmp = a[i];
        j = i - 1;
        low = 0;
        high = i - 1;
        while(low<=high){
            int mid = (low + high) / 2;
            if(tmp>a[mid])
                low = mid + 1;
            else
                high = mid - 1 ;
        }
        while(j>=low && tmp<a[j]){   //小于号换成大于号则是从大到小排序
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;
    }
    
    return;
}
```
 
### 三、希尔排序法
 
希尔排序又叫缩小增量排序
 
基于直接插入排序，基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录“基本有序”时，再对全体记录进行依次直接插入排序。
 
希尔的思想也很简单就是一个h-sort的插入算法——每相邻h个元素进行插入排序
 
如果h比较大，那么子数组会很小，用插入效率高
 
如果h很小，这时候数组基本有序，插入效率也很高
 
```c
void ShellSort(int arr[], int len)
{
    int step;
    int i, j;
    int tmp;
    for(step = len/2; step > 0; step = step/2)   // 比直接插入排序多了一层循环
    {
        for(i = step; i < len; i++)              // 直接插入排序可以看成step为1的希尔排序。把这里的Step都替换成1，就是直接插入排序
        {
            j = i - step;
            tmp = arr[i];
            while(j>=0 && tmp<arr[j])
            {
                arr[j+step] = arr[j];
                j = j - step;
            }
            arr[j+step] = tmp;
        }
    }
    
    return;
}
```
 
### 四、简单选择排序
 
排序思路是：每次从未排序的序列中选出一个最小值，并把它放在已排好序的序列的序尾。这样就形成了一个有序序列（从小到大）。
 
简单选择排序的基本思想：找到最小值 + 交换。
 
第一趟，从n 个记录中找出关键码最小的记录与第一个记录交换；
 
第二趟，从第二个记录开始的 n-1 个记录中再选出关键码最小的记录与第二个记录交换；
 
以此类推.....
 
第 i 趟，则从第 i 个记录开始的 n-i+1 个记录中选出关键码最小的记录与第 i 个记录交换，
 
直到整个序列按关键码有序。
 
```c
void SelectSort(int *a, int len)
{
    int i, j;
    int key, tmp;
    
    for(i=0; i<len; i++)
    {
        key = i;          // 记录最小值的下标，初始值为i，即有序序列的最后一个元素    
        for(j=i+1; j<len; j++)  // j从i的下一个元素开始遍历，即无序序列的第一个元素
        {
            if(a[j]<a[key])  // 如果找到比当前key上的值小的值，则替换key值
                key = j;
        }
        
        if(key!=i)          // key == i说明 无序序列中没有比a[i]更小的数了，不必替换
        {
            tmp = a[i];      // 替换a[i]和无序序列中最小的元素a[key]
            a[i] = a[key];
            a[key] = tmp;
        }
    }
    return;
}
```
 
### 五、堆排序
 
堆排序是一种树形选择排序，是对直接选择排序的有效改进。实际上也是一种选择排序，只不过采用了堆这种数据结构，利用这种数据结构，使得在每次查找最大元素时，直接选取堆顶元素，从而时间大大缩短，相对简单选择排序算法来说，比较高效。
 
将初始待排序关键字序列(A0, A1, A2 .... An-1)构建成大顶堆(从最后一个非叶子结点 i = len/2 - 1 自下而上)，此堆为初始的无序区（构建堆）
 
将堆顶元素A[0]与最后一个元素A[n-1]交换，此时得到新的无序区(A0, A1, A2,......An-2)和新的有序区(An-1)  （交换首尾元素）
 
由于交换后新的堆顶A[0]可能违反堆的性质，因此需要对当前无序区(A0,A1,......An-2)重新调整为新的大顶堆(从根节点 i = 0，自上而下) （调整堆）
 
然后再次将A[0]与无序区最后一个元素交换，得到新的无序区(A0,A1....Rn-3)和新的有序区(An-2,An-1)。（不断循环）
 
不断重复此过程直到有序区的元素个数为n-1，则整个排序过程完成
 
// 下标从0开始，左孩子是2 start+1; 如果从1开始，是2  start
 
```c
void HeapAdjust(int *A, int start, int end)
{
    int k;
    int tmp = A[start];
    for(k=2*start+1; k<=end; k=k*2+1)           // k=k*2+1 是取左孩子
    {
        if(k<end && A[k]<A[k+1])    // 比较左右孩子，选较大者
            k++;
        if(tmp<A[k])         // 比较父节点和左右孩子中较大者，如果孩子较大，将孩子节点值赋值给父节点，start指向孩子节点的位置
        {
            A[start] = A[k];
            start = k;
        }
        else
            break;
    }
    A[start] = tmp;      // 将一开始的start的值赋给此时start指向的节点，即将原来不和谐的元素放到合适的位置上
}
void HeapSort(int *A, int len)
{
    int i, j;
    for(i=len/2-1; i>=0; i--)    //从最后一个非叶子结点i（len/2-1）从下至上，从右至左调整结构，构建初始堆
    {
        HeapAdjust(A, i, len);
    }
    for(j=len-1; j>=0; j--)       // 将堆顶元素和末尾元素互换，再将剩下的j-1个元素调整为大顶堆
    {
        int tmp = A[j];
        A[j] = A[0];
        A[0] = tmp;
        HeapAdjust(A, 0, j-1);    // 重建堆是从顶至下，与初始堆相反
    }
}
```
 
[https://www.cnblogs.com/0zcl/p/6737944.html][5] 堆排序详解
 
[http://www.cnblogs.com/mengdd/archive/2012/11/30/2796845.html][6] 堆排序 Heap Sort
 
### 六、冒泡排序
 
冒泡排序是一种相对简单的排序，它每次比较相邻的两个元素，如果前者大于后者，则交换< swap >这两个元素（从小到大排序），这样每一趟比较就把大的元素沉入最后，形象的称之为“冒泡”，每走一趟，实际上最尾的元素已经排好。
 
将序列当中的左右元素，依次比较，保证右边的元素始终大于左边的元素；（ 第一轮结束后，序列最后一个元素一定是当前序列的最大值；）
 
对序列当中剩下的n-1个元素再次执行步骤1。
 
对于长度为n的序列，一共需要执行n-1轮比较。（利用while循环可以减少执行次数）
 
```c
void BubbleSort(int *A, int len)
{
    int i, j;
    int tmp;
    for(i=0; i<len-1; i++)    // 长度为len的数组，最多需要len-1次冒泡，即可有序(剩下一个自动变为最大或最小)
    {
        for(j=0; j<len-i-1; j++)  // 注意：每次循环比较len-1-i次，如果写成len-1，多了一次数组会越界，产生不可预料的结果
        {
            if(A[j]>A[j+1])
            {
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
}
```
 
#### 冒泡算法改进之一（加入标志位判断是否已经有序）：
 
对冒泡排序常见的改进方法是加入一标志性变量exchange，用于标志某一趟排序过程中是否有数据交换，如果进行某一趟排序时并没有进行数据交换，则说明数据已经按要求排列好，可立即结束排序，避免不必要的比较过程。
 
```c
// 改进一，加入标志位
void BubbleSort2(int *A, int len)
{
    int i, j;
    int tmp;
    int flag;        // flag=1时表示已经排序完成
    for(i=0; i<len-1; i++)
    {
        flag = 1;          // 每次冒泡前把flag置1
        for(j=0; j<len-i-1; j++)
        {
            if(A[j]>A[j+1])
            {
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                flag = 0;  // 如果发生交换，置0，说明还没有排序完成
            }
        }
        if(flag==1)  // 如果一次冒泡循环中一次交换也没发生，则flag还是为1，说明数组已经排好序
            break;
    }
}
```
 
#### 冒泡算法改进之二（记录最后一次交换的位置）：
 
在冒泡排序的每趟扫描中，记住最后一次交换发生的位置lastexchange也能有所帮助。因为该位置之前的相邻记录已经有序，故下一趟排序开始的时候，0到lastexchange已经是有序的了，lastexchange到n-1是无序区。所以一趟排序可能使当前有序区扩充多个记录.即较大缩小无序区范围，而非递减1，以此减少排序趟数。这种算法如下：
 
```c
// 改进二，记录最后一次交换的位置
void BubbleSort3(int *A, int len)
{
    int j;
    int tmp;
    int flag = len - 1;
    int pos;
    while(flag>0)
    {
        pos = 0;        // 不要漏了该条赋值语句。否则会陷入无限循环。
        
        for(j=0; j<flag; j++)
        {
            if(A[j]>A[j+1])   // 如果没有交换，则不会进入该if分支，pos还是=0，说明已经排好序，while循环才会结束
            {
                tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
                pos = j;           // 记录最后一次交换的位置
            }
        }
        flag = pos;         // 把位置赋给flag，用于判断无序区是否还有元素
    }
}
```
 
#### 冒泡算法改进之三（双向冒泡）：
 
传统冒泡排序中每一趟排序操作只能找到一个最大值或最小值,我们考虑利用在每趟排序中进行正向和反向两遍冒泡的方法一次可以得到两个最终值(最大者和最小者) , 从而使排序趟数几乎减少了一半。
 
```c
// 改进三，双向冒泡
void BubbleSort4(int *A, int len)
{
    int low=0, high=len-1;
    int i;
    int tmp;
    while(low<high)
    {
        for(i=low; i<high; i++)  // 正向冒泡,找到最大者
        {
            if(A[i]>A[i+1])
            {
                tmp = A[i];
                A[i] = A[i+1];
                A[i+1] = tmp;
            }
        }
        high--;            // 修改high值, 前移一位 
        for(i=high; i>low; i--)     // 反向冒泡,找到最小者 
        {
            if(A[i]<A[i-1])
            {
                tmp = A[i];
                A[i] = A[i-1];
                A[i-1] = tmp;
            }
        }
        low++;            // 修改low值,后移一位
    }
}
```
 
### 七、快速排序
 
快速排序（Quicksort）是对冒泡排序的一种改进。
 
关于快速排序，它的基本思想就是选取一个基准，一趟排序确定两个区间，一个区间全部比基准值小，另一个区间全部比基准值大，接着再选取一个基准值来进行排序，以此类推，最后得到一个有序的数列。
 
1.选取基准值，通过不同的方式挑选出基准值。
 
2.用分治的思想进行分割，通过该基准值在序列中的位置，将序列分成两个区间，在准值左边的区间里的数都比基准值小（默认以升序排序），在基准值右边的区间里的数都比基准值大。
 
3.递归调用快速排序的函数对两个区间再进行上两步操作，直到调用的区间为空或是只有一个数。
 
```c
// 基本双向快速排序
void QuickSort(int *A, int start, int end)
{
    if(start<end){                // 调试时少了这一步，一直报错
        int i=start, j=end;
        int pivot = A[i];    // 第0个元素作为基准数
        while(i<j)
        {
            while(i<j && A[j]>pivot) j--;
            A[i] = A[j];
            while(i<j && A[i]<pivot) i++;
            A[j] = A[i];
        }
        A[i] = pivot;          // 基准数归位，i左边为较小数，右边为较大数
        QuickSort(A, start, i-1);  // 递归调用，将剩下两部分继续进行快排
        QuickSort(A, i+1, end);
    }
}
```
 
#### 快速排序改进一（基准数随机选取）
 
上面版本的快排在选取主元的时候，每次都选取第一个元素。当序列为有序时，会发现划分出来的两个子序列一个里面没有元素，而另一个则只比原来少一个元素。为了避免这种情况，引入一个随机化量来破坏这种有序状态。
 
```c
// 随机选取基准数，如果序列基本有序，可以避免分治之后一个区间元素过少，一个区间元素过多的情况
void QuickSort2(int *A, int start, int end)
{
    if(start<end){
        int i=start, j=end;
        int pivot_pos = rand() % (end - start) + start;      // 从start~end间随机选取一个元素作为基准数
        int pivot = A[pivot_pos];              // 开辟一块内存存储pivot值
        SWAP(&A[pivot_pos], &A[start]);        // 交换pivot_pos和start位置上的值，不会影响到上面pivot的值
        while(i<j)
        {
            while(i<j && A[j]>pivot) j--;
            A[i] = A[j];
            while(i<j && A[i]<pivot) i++;
            A[j] = A[i];
        }
        A[i] = pivot;          // 基准数归位，i左边为较小数，右边为较大数
        QuickSort2(A, start, i-1);  // 递归调用，将剩下两部分继续进行快排
        QuickSort2(A, i+1, end);
    }
}
```
 
#### 快速排序改进二（三数取中）
 
但是随机函数本身也要消耗一定的时间，而且随机选取也有可能出现不好分割的几率，所以又提出了三数取中法，即取左端、右端和中间三个元素排序后取中间的数作为关键元素。
 
```c
// 三数取中选取基准数，选取序列头尾还有中间的三个数，取三个中值在中间的元素作为基准数
void QuickSort3(int *A, int start, int end)
{
    if(start<end){
        int mid = (start + end) / 2;
        if(A[mid]>A[end]) SWAP(&A[mid], &A[end]);
        if(A[start]>A[end]) SWAP(&A[start], &A[end]);
        if(A[start]<A[mid]) SWAP(&A[start], &A[mid]);        //通过以上三步可以找到中间值，存放在A[start]中
        int i=start, j=end;
        int pivot = A[start];
        while(i<j)
        {
            while(i<j && A[j]>pivot) j--;
            A[i] = A[j];
            while(i<j && A[i]<pivot) i++;
            A[j] = A[i];
        }
        A[i] = pivot;          // 基准数归位，i左边为较小数，右边为较大数
        QuickSort3(A, start, i-1);  // 递归调用，将剩下两部分继续进行快排
        QuickSort3(A, i+1, end);
        return;
    }
    else
        return;
}
```
 
#### 快速排序改进三（当待排序序列的长度分割到一定大小后，使用插入排序）
 
原因：对于很小和部分有序的数组，快排不如插排好。当待排序序列的长度分割到一定大小后，继续分割的效率比插入排序要差，此时可以使用插排而不是快排
 
截止范围：待排序序列长度N = 10，虽然在5~20之间任一截止范围都有可能产生类似的结果。这种做法也避免了一些有害的退化情形。
 
```c
if (start - end + 1 < 10)  
{  
    InsertSort(A, start, end);  
    return;  
}
//else时，正常执行快排
```
 
#### 快速排序改进四（尾递归，减少一次递归）
 
其实这种优化编译器会自己优化，相比不使用优化的方法，时间几乎没有减少。
 
QuickSort函数在其尾部有两次递归操作。如果待排序的序列划分极端不平衡，递归的深度将趋近于n，而不是平衡时的logn。
 
```c
// 尾递归，减少递归深度
int Partition(int *A, int start, int end)
{
    int pivot = A[start];
    while(start<end)
    {
        while(start<end && A[end]>pivot) end--;
        SWAP(&A[end], &A[start]);
        while(start<end && A[start]<pivot) start++;
        SWAP(&A[start], &A[end]);
    }
    return start;
}
​
void QuickSortTail(int *A, int start, int end)
{
    /* 普通递归方式，start和end这两个局部变量在下一次函数调用中还需要使用，所以需要继续堆栈
    if(start<end)
    {
        int pivot_pos = Partition(A, start, end);
        QuickSort(A, start, pivot_pos-1);
        QuickSort(A, pivot_pos+1, end);
    }
    */
    while(start<end)
    {
        int pivot_pos = Partition(A, start, end);
​
        if(pivot_pos-start < end-pivot_pos)            // 短的部分采用递归，可以有效减少递归深度
        {
            QuickSortTail(A, start, pivot_pos-1);        //　左半部分继续递归
            start = pivot_pos + 1;
        }
        else
        {
            QuickSortTail(A, pivot_pos+1, end);        //　右半部分继续递归
            end = pivot_pos - 1;
        }
​
    }
}
```
 
### 八、归并排序
 
  
归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。
 
  
![][2]


 
#### （1）递归方式实现归并排序
 
分为两个函数实现:
 
1、分：可以看到这种结构很像一棵完全二叉树，本文的归并排序我们采用递归去实现（也可采用迭代的方式去实现）。分阶段可以理解为就是递归拆分子序列的过程，递归深度为log2n。
 
2、并：然后考虑下如何将将二个有序数列合并。这个非常简单，只要从比较二个数列的第一个数，谁小就先取谁，取了后就在对应数列中删除这个数。然后再进行比较，如果有数列为空，那直接将另一个数列的数据依次取出即可。
 
```c
// 把两个有序数组合并成一个有序数组
void MergeArray(int *A, int len_A, int *B, int len_B)
{
    int i, j, k;
    i = j = k = 0;
    int temp[len_A + len_B];
    while(i<len_A && j<len_B)          //取两个数组第一个元素比较，小的存入temp中
    {
        if(A[i]<B[j])
            temp[k++] = A[i++];
        else
            temp[k++] = B[j++];
    }
    while(i<len_A)                    //两个数组中剩余的元素一定是偏大的，直接存入temp中
    {
        temp[k++] = A[i++];
    }
    while(j<len_B)
    {
        temp[k++] = B[j++];            
    }
    for(i=0; i<(len_A+len_B); i++)
        A[i] = temp[i];                //temp再转存入A数组中
}
//递归实现归并排序
void MergeSort1(int *A, int len)
{
    if(len>1)
    {
        // 数组分成两半
        int *list1 = A;
        int list1_len = len/2;
        int *list2 = A + len/2; 
        int list2_len = len - list1_len;
        MergeSort1(list1, list1_len);  //左边部分递归
        MergeSort1(list2, list2_len);  //右边部分递归
        MergeArray(list1, list1_len, list2, list2_len);  //合并两个有序数组
    }
}
```
 
#### （2）迭代方式实现归并排序
 
  
非递归的方法，避免了递归时深度为log2N的栈空间，空间只是用到归并临时申请的跟原来数组一样大小的空间，并且在时间性能上也有一定的提升，因此，使用归并排序是，尽量考虑用非递归的方法。
 
无论是基于递归还是循环的归并排序， 它们调用的核心方法都是相同的：完成一趟合并的算法，即两个已经有序的数组序列合并成一个更大的有序数组序列 （前提是两个原序列都是有序的）
 
  
![][3]


 
```c
//迭代实现归并排序
void MergeSort2(int *A, int len)
{
    int left_min, left_max, right_min, right_max;
    int i, next;
    int *temp = (int *)malloc(len*sizeof(int));
    if(temp == -1) return;
    for(i=1; i<len; i*=2)      //步长从1开始，以2的倍数递增
    {
        for(left_min=0; left_min<len-i; left_min=right_max)  // 每次循环结束后，把letf_min指向right_max;right_max指向right_min+i;
        {
            right_min = left_max = left_min + i;
            right_max = right_min + i;
            if(right_max>len)        // right_max 最大为len，如果超出，则等于len
            {
                right_max = len;
            }
            next = 0;
            while(left_min<left_max && right_min<right_max)  // 合并[left_min, left_max]和[right_min, right_max]两个区间的数组
            {
                if(A[left_min]<A[right_min])
                {
                    temp[next++] = A[left_min++];
                }
                else
                {
                    temp[next++] = A[right_min++];
                }
            }
            while(left_min<left_max)      // 如果是左边的元素还有剩余，则把它们移动到right数组的最右边；如果是右边的数组元素还有剩余，则不用动
            {
                A[--right_min] = A[--left_max];
            }
            while(next>0)                // 再把temp数组填充到left和right数组中
            {
                A[--right_min] = temp[--next];
            }
        }
    }
}
```
 
### 九、基数排序
 
#### （一）首先谈谈计数排序
 
前面所有的排序算法都存在比较，都可以称为”比较排序“。比较排序的下界为o（nlogn）。那么有没有时间复杂度为o（n）的线性时间排序算法呢？计数排序便是很基础的一种线性时间排序，它是基数排序的基础。基本思想是：对每一个元素x，确定小于x的元素个数，就可以把x直接放到它在有序序列中的位置上。过程描述：假设待排序序列a中值的范围[0,k],其中k表示待排序序列中的最大值。首先用一个辅助数组count记录各个值在a中出现的次数，比如count[i]表示i在a中的个数。然后依次改变count中元素值，使count[i]表示a中不大于i的元素个数。然后从后往前扫描a数组，a中的元素根据count中的信息直接放到辅助数组b中。最后把有序序列b复制到a。
 
计数排序是稳定的排序算法；平均时间复杂度、最优时间复杂度和最差时间复杂度都为O(n+k)，空间复杂度为O(n+k)，其中，n为待排元素个数，k为待排元素的范围(0~k)。
 
```c
// 计数排序
void CountSort(int *A, int len)
{
    int min = A[0];
    int max = A[0];
    int i = 0;
    //找出数组中的最大值和最小值，确定哈希表的大小
    for(i=0; i<len; i++)
    {
        if(A[i]<min) min = A[i];
        if(A[i]>max) max = A[i];
    }
    int count_size = max - min + 1;
    int *count_arr = (int *)malloc(sizeof(int) * count_size);   // 创建一个用于计数的数组
    int *temp = (int *)malloc(sizeof(int) * len);
    for(i=0; i<count_size; i++) 
        count_arr[i] = 0;   // 计数数组全部初始化为0
    for(i=0; i<len; i++) 
        count_arr[A[i]-min]++;    // 统计数组A中各元素出现的次数，并放在对应的位置上
    for(i=1; i<count_size; i++) 
        count_arr[i] += count_arr[i-1];  // 储存自己数组下标数值在目标数组对应的位置，保证稳定性 
    for(i=0; i<count_size; i++){
        //printf("%d, ", count_arr[i]);
    }
    //printf("\n");
    for(i=len-1; i>=0; i--)
    {
        temp[count_arr[A[i]-min]-1] = A[i];  //将原数组按大小顺序储存到另一个数组
        count_arr[A[i]-min]--;
        //temp[--count_arr[A[i] - min]] = A[i];
    }
    for(i=0; i<len; i++) 
        A[i] = temp[i];
    
    free(count_arr);
    free(temp);
}
```
 
不过该计数排序不能对负数进行排序，如果需要对负数进行排序，需要进行改进（先一次遍历待排数组，找出负数中的最大值和最小值，正数中的最大值和最小值，创建两个计数数组，negativeCountArray用来统计待排数组中各个不同负数的出现个数，positiveCountArray用来统计待排数组中各个正数出现的个数，先统计总的负数的个数，然后再统计各个不同正数的个数，然后在往sortedArray中放元素的时候对正数和负数区别对待。）
 
#### （一）基数排序
 
  
基数排序的基本思想是:一共有10个"桶",代表各个数位为0~9.在每个桶上,组织一个优先队列,对于输入的一系列正整数和0,按照个位的大小关系分别进入10个"桶"中.然后遍历每个"桶",按照十位的大小关系进行调整,紧接着是百位,千位.......直到到达最大数的最大位数。
 
  
![][4]


 
基数排序只是针对于数字，思想就是将我们需要待排列的元素按照指定的进制将每一位排列，时间复杂度为：P(N+B)，注：其中P为待排列数字的最大位数，N为待排序列的长度，B为进制数。
 
```c
//基数排序
void RadixSort(int *A, int len)
{
    int max_digit = 0;
    int i, j;
    int radix = 10;
    //求数组中的最大位数
    for (i = 0; i < len; ++i)
    {
        while (A[i] > (pow(10, max_digit)))
        {
            max_digit++;
        }
    }
    int flag = 1;
    for(j=1; j<=max_digit; j++)
    {
        //建立数组 统计每个位上不同数字出现的次数
        int digit_count_arr[10] = { 0 };
        for(i=0; i<len; i++)
            digit_count_arr[(A[i] / flag) % radix]++;
        //建立数组 统计A[i]在temp中的起始下标
        int BeginIndex[10] = { 0 };
        for(i=1; i<radix; i++)
            BeginIndex[i] = BeginIndex[i - 1] + digit_count_arr[i - 1];
        //建立临时数组 用于收集数据
        int *tmp = (int *)malloc(sizeof(int) * len);
        //初始化
        for(i=0; i<len; i++)
            tmp[i] = 0;
        //将数据写入临时数组
        for(i=0; i<len; i++)
        {
            int index = (A[i] / flag) % 10;
            tmp[BeginIndex[index]++] = A[i];  // 写入一个同时要把该位置上的计数加1，因为同一个位置可能有多个元素
        }
        //将数据重新写回原数组
        for(i=0; i<len; i++)
            A[i] = tmp[i];
        flag = flag * 10;  // 用于下一位的排序
        free(tmp);
    }
}
```
 
资料
 
[https://www.cnblogs.com/maluning/p/7944809.html][7]
 
常用七大经典排序算法总结(C语言描述)
 
[http://blog.csdn.net/gl486546/article/details/53053069][8]
 
排序算法之希尔排序
 
[https://www.jianshu.com/p/7d037c332a9d][9]
 
数据结构常见的八大排序算法（详细整理）
 
[http://blog.csdn.net/zhangjikuan/article/details/49095533][10]
 
九大排序算法-C语言实现及详解 
 
[https://www.jianshu.com/p/6777a3297e36][11]
 
快速排序的优化 和关于递归的问题，说说我的想法
 
[http://www.cnblogs.com/Anker/archive/2013/03/04/2943498.html][12]
 
递归与尾递归总结
 
[http://blog.csdn.net/touch_2011/article/details/6785881][13]
 
漫谈经典排序算法:四、归并排序(合并排序)（推荐）
 


[5]: https://www.cnblogs.com/0zcl/p/6737944.html
[6]: http://www.cnblogs.com/mengdd/archive/2012/11/30/2796845.html
[7]: https://www.cnblogs.com/maluning/p/7944809.html
[8]: http://blog.csdn.net/gl486546/article/details/53053069
[9]: https://www.jianshu.com/p/7d037c332a9d
[10]: http://blog.csdn.net/zhangjikuan/article/details/49095533
[11]: https://www.jianshu.com/p/6777a3297e36
[12]: http://www.cnblogs.com/Anker/archive/2013/03/04/2943498.html
[13]: http://blog.csdn.net/touch_2011/article/details/6785881
[0]: https://img1.tuicool.com/qAVzmi3.jpg 
[1]: https://img2.tuicool.com/FF3YbmR.jpg 
[2]: https://img0.tuicool.com/3u67Zrj.png 
[3]: https://img2.tuicool.com/zuYNNvq.png 
[4]: https://img1.tuicool.com/QNrUV3n.jpg 