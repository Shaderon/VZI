# sorting some stuff 2
# https://www.youtube.com/watch?v=-xXvxj0SaQ4

import sys
import random
import time
# import timeit

# v pripade max. recursion limitu
# sys.setrecursionlimit(1500)
# viz. https://stackoverflow.com/questions/3323001/maximum-recursion-depth

nums = list()

n = 10
for i in range(0, n):
    # print(random.random())
    # nums.append(round(random.uniform(0, 100)))
    nums.append(round(random.uniform(0, n)))

def swap(lst, a, b):
    tmp = lst[a]
    lst[a] = lst[b]
    lst[b] = tmp

def print_list(lst):
    for i in range(0, len(lst)):
        # print(lst[i])
        pprint(lst[i])



def merge(left, right):
    result = list()

    while (len(left) > 0) and (len(right) > 0):
        if left[0] > right[0]:
            result.append(right.pop(0))
        else:
            result.append(left.pop(0))

    result.extend(left+right)
    return result

def merge_sort(lst):
    left = list()
    right = list()

    if len(lst) <= 1:
        return lst
    else:
        middle = len(lst) // 2
        left= lst[middle:]
        right= lst[:middle]

        left = merge_sort(left)
        right = merge_sort(right)

        result = merge(left, right)
        return result


print(nums)
# s = time.time()

lst = merge_sort(nums)
print(lst)

# e = time.time()
# print(nums)
# print(e-s)
