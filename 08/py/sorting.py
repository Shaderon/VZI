# sorting some stuff 1
# https://www.youtube.com/watch?v=98oMvKF-78Y

import sys
import stack
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

def bubble_sort(lst):
    for i in range(len(lst)-1):
        for j in range(len(lst) - i - 1):

            if (lst[j] >= lst[j+1]):
                swap(lst, j, j+1)

        # print(lst, i, len(lst) - i - 1)


def insertion_sort(lst):
    for i in range(len(lst)-1):
        j = i+1
        tmp = lst[j]

        while ((j > 0) and (tmp > lst[j-1])):
            lst[j] = lst[j-1]
            j = j - 1

            # print(lst, i, tmp)

        lst[j] = tmp
    lst.reverse()




def partition(lst, left, right):
    pivot = lst[right]
    tmp = left

    for i in range(left, right):
        if (lst[i] <= pivot):
            swap(lst, tmp, i)
            # print(lst,i, tmp, '---', pivot)
            tmp = tmp + 1


    swap(lst, tmp, right)
    # print(lst)
    return tmp

def quick_sort_recursive(lst, left, right):
    if (left < right):
        split = partition(lst, left, right)
        quick_sort_recursive(lst, left, split-1)
        quick_sort_recursive(lst, split+1, right)

def quick_sort(lst, left, right):
    s = stack.Stack()
    s.push(left)
    s.push(right)

    while not s.isEmpty():
        r = s.pop()
        l = s.pop()

        if (r <= l):
            continue

        i = partition(lst, l, r)

        if (i-1 > r-1):
            s.push(i+1)
            s.push(r)
            s.push(l)
            s.push(i-1)
        else:
            s.push(l)
            s.push(i-1)
            s.push(i+1)
            s.push(r)


# main

print(nums)
s = time.time()

# bubble_sort(nums)
# insertion_sort(nums)
quick_sort_recursive(nums, 0, len(nums)-1)
# quick_sort(nums, 0, len(nums)-1)

e = time.time()
print(nums)

print(e-s)
