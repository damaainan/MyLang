#!/usr/bin/env python
# -*- coding:utf-8 -*-
# Python 3.5
# 快速排序


class SQList:
    def __init__(self, lis=None):
        self.r = lis

    def swap(self, i, j):
        """定义一个交换元素的方法，方便后面调用。"""
        temp = self.r[i]
        self.r[i] = self.r[j]
        self.r[j] = temp

    def quick_sort(self):
        """调用入口"""
        self.qsort(0, len(self.r)-1)

    def qsort(self, low, high):
        """递归调用"""
        if low < high:
            pivot = self.partition(low, high)
            self.qsort(low, pivot-1)
            self.qsort(pivot+1, high)

    def partition(self, low, high):
        """
        快速排序的核心代码。
        其实就是将选取的pivot_key不断交换，将比它小的换到左边，将比它大的换到右边。
        它自己也在交换中不断变换自己的位置，直到完成所有的交换为止。
        但在函数调用的过程中，pivot_key的值始终不变。
        :param low:左边界下标
        :param high:右边界下标
        :return:分完左右区后pivot_key所在位置的下标
        """
        lis = self.r
        pivot_key = lis[low]
        while low < high:
            while low < high and lis[high] >= pivot_key:
                high -= 1
            self.swap(low, high)
            while low < high and lis[low] <= pivot_key:
                low += 1
            self.swap(low, high)
        return low

    def __str__(self):
        ret = ""
        for i in self.r:
            ret += " %s" % i
        return ret

if __name__ == '__main__':
    sqlist = SQList([4, 1, 7, 3, 8, 5, 9, 2, 6, 0, 123, 22])
    sqlist.quick_sort()
    print(sqlist)