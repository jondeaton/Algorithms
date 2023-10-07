"""Algorithms."""

from typing import *
import bisect
from dataclasses import dataclass, field


@dataclass
class Node:
    children: list["Node"] = field(default_factory=list)
    visited: bool = False


def topo_sort(nodes: list[Node]) -> list[Node]:
    out = []
    def dfs(node):
        if node.visited: return
        node.visited = True
        for child in node.children:
            dfs(child)
        out.append(node)

    for node in nodes:
        dfs(node)

    return out


def _swap(arr, i, j):
    value = arr[i]
    arr[i] = arr[j]
    arr[j] = value


def partition(
    arr: list[Any],
    l: int,
    r: int,
    pivot: int,
) -> int:
    """Partitions array."""
    assert arr
    assert 0 <= l <= pivot <= r < len(arr)
    _swap(arr, pivot, r)
    for i in range(l, r):
        if arr[i] < arr[r]:
            _swap(arr, l, i)
            l += 1
    _swap(arr, r, l)
    return l


def quicksort(arr: list[Any], l: int = 0, r: int | None = None):
    r = r if r is not None else len(arr) - 1
    if not l < r: return
    mid = l + (r - l) // 2
    pivot = partition(arr, l, r, mid)
    quicksort(arr, l, pivot - 1)
    quicksort(arr, pivot + 1, r)


def select(arr: list[Any], k: int):
    n = len(arr)
    assert -n < k < n
    l = 0
    r = n - 1
    i = -1
    while i != k:
        i = l + (r - l) // 2
        i = partition(arr, l, r, i)
        if i < k:
            l = i + 1
        elif i > k:
            r = i - 1
    return arr[i]


def median_of_two(a: list[int], b: list[int]) -> int:
    """Find the median of two sorted arrays in O(log(m+n))
    https://leetcode.com/problems/median-of-two-sorted-arrays/
    """
    return combine_kth(a, b, (0, len(a)), (0, len(b)))

def combine_kth(a, b, a_bound, b_bound):
    alo, ahi = a_bound
    med_a = alo + (ahi - alo) // 2

    # If we were to merge b into a maintaining sort, how many elements of b
    # would be inserted before the median of a?
    a_ins_left = bisect.bisect_left(b, a[med_a])
    if a_ins_left > len(b) // 2:
        # more elements inserted left than right
        ahi = med_a
    elif a_ins_left < len(b) // 2:
        alo = med_a
    else:
        return a[med_a]

    blo, bhi = b_bound
    med_b = blo + (bhi - blo) // 2
    b_ins_left = bisect.bisect_left(a, b[med_b])
    if b_ins_left > len(a) // 2:
        bhi = med_b
    elif b_ins_left < len(a) // 2:
        blo = med_b
    else:
        return b[med_b]

    return combine_kth(a, b, (alo, ahi), (blo, bhi))


def topk(arr: list[Any], k: int):
    kth = select(arr, k)
    out = []
    for x in arr:
        if x < kth:
            out.append(x)
    return out + [kth] * (k - len(out))

