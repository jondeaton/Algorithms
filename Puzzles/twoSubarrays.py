#!/usr/bin/env python
'''
https://www.hackerrank.com/challenges/two-subarrays/problem
'''


def maxf(arr):
	N = len(arr)
	A = [0 for _ in xrange(N)]

	for r in xrange(N):
		greatest = 0
		for i in xrange(r):
			if A[[r] < A[i]:
