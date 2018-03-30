#include <stdio.h>
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
int main()
{
    int a[] = {1,3,63,5,78,9,12,52,8};
    int n = sizeof(a)/sizeof(int),i;
    BinaryInsertSort(a, n);
    for(i=0; i<n; i++)
        printf("%d ", a[i]);
    return 0;
}