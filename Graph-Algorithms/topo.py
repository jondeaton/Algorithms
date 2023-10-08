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
    return find_median(a, b, 0, len(a) - 1, 0, len(b) - 1)

def find_median(a, b, alo, ahi, blo, bhi):
    # If we were to merge b into a maintaining sort, how many elements of b
    # would be inserted before the median of a?
    print(alo, ahi, blo, bhi)

    med_idx = (len(a) + len(b)) // 2

    if alo <= ahi:
        med = alo + (ahi - alo) // 2
        merged_idx = _merge_index(a, b, med)
        if merged_idx == med_idx:
            return a[med]
        elif merged_idx < med_idx:
            # This number is less than the median
            alo = med
        elif merged_idx > med_idx:
            # this number is more than the median
            ahi = med

    if blo <= bhi:
        med = blo + (bhi - blo) // 2
        merged_idx = _merge_index(b, a, med)
        if merged_idx == med_idx:
            return b[med]
        elif merged_idx < med_idx:
            # This number is less than the median
            blo = med
        elif merged_idx > med_idx:
            # this number is more than the median
            bhi = med

    return find_median(a, b, alo, ahi, blo, bhi)

def _merge_index(a, b, i):
    """index where a[i] is after sorted merge with b"""
    return i + bisect.bisect_left(b, a[i])


def topk(arr: list[Any], k: int):
    kth = select(arr, k)
    out = []
    for x in arr:
        if x < kth:
            out.append(x)
    return out + [kth] * (k - len(out))

