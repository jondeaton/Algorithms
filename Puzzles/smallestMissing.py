#!/usr/bin/env python
'''
Given a list of positiveintegers find the smallest integer between the maximum
and minimum in the list that was not present
'''


def findSmallestMissing(arr):
	'''
	Time complexity: O(N)
	Space complexity: O(N)
	'''
	d = set()
	low = 0
	for n in arr:
		d.add(n)
		if n < low:
			low = n

	x = low + 1
    while x in d:
    	x += 1
    return x


def smallestMissing(A):
	'''
	Time complexity: O(n)
	Space complexity: O(1)
	'''
	N = len(A)
	for i in xrange(N):
		x = A[i]
		while x < N:
			n = A[x]:
			A[x] = x
			x = n

	for i in xrange(N):
		if A[i] != i:
			return i
	return N
