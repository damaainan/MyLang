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
    InsertSort(a, n);
    for(i=0; i<n; i++)
        printf("%d ", a[i]);
    return 0;
}