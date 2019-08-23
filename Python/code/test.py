#!/usr/bin/env python3
# -*- coding: utf-8 -*-

''' 测试 '''

items = [1, 10, 7, 4, 5, 9]
def sum(items):
    head, *tail = items
    return head + sum(tail) if tail else head

print(sum(items))