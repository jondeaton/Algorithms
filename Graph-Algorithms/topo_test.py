
import topo
import random

def test_partition_one():
    arr = [3]
    i = topo.partition(arr, 0, 0, 0)
    assert i == 0
    assert arr == [3]

def test_partition_two():
    arr = [4, 3]
    i = topo.partition(arr, 0, 1, 1)
    assert i == 0
    assert arr == [3, 4]

def test_partition():
    arr = [0, 3, 2, 1, 3, 1, 0]
    i = topo.partition(arr, 1, 5, 2)
    assert i == 3
    assert arr == [0, 1, 1, 2, 3, 3, 0]

def test_partition_empty_left():
    arr = [0, 1, -1, 1, 1, 1, 0]
    i = topo.partition(arr, 1, 5, 2)
    assert i == 1
    assert arr == [0, -1, 1, 1, 1, 1, 0]


def test_select():
    arr = [10, 7, 5, 2, 5, 7, 0, -10, 23, 8, 6]
    arr_sorted = sorted(arr)
    for i in range(len(arr)):
        assert topo.select(arr, i) == arr_sorted[i]

def test_quicksort():
    arr = [10, 7, 5, 2, 5,  7, 0, -10, 23, 8, 6]
    topo.quicksort(arr)
    assert arr == sorted(arr)

def test_quicksort_big():
    arr = random.choices(range(10), k=1000)
    topo.quicksort(arr)
    assert arr == sorted(arr)


def test_median_of_two_empty():
    assert topo.median_of_two([7], []) == 7
    assert topo.median_of_two([], [7]) == 7


def test_median_of_two_one():
    assert topo.median_of_two([7], [8]) in [7, 8]
    assert topo.median_of_two([8], [7]) in [7, 8]

def test_median_of_two_small():
    assert topo.median_of_two([1, 3], [2]) == 2
    assert topo.median_of_two([2], [1, 3]) == 2

def test_median_of_two_three():
    assert topo.median_of_two([1, 2, 4, 5], [0, 3, 10]) == 3
    assert topo.median_of_two([0, 3, 10], [1, 2, 4, 5]) == 3

# def test_median_of_two():
#     assert topo.median_of_two([1, 2, 3], [4, 5]) == 3


