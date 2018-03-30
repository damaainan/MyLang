#include <stdio.h>

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

int main()
{
    int a[] = {1,3,63,5,78,9,12,52,8};
    int n = sizeof(a)/sizeof(int),i;
    ShellSort(a, n);
    for(i=0; i<n; i++)
        printf("%d ", a[i]);
    return 0;
}