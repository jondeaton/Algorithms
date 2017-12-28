#!/usr/bin/env python
"""
Dynamic Programing Algorithms
	- Longest strictly increasing subsequence 
	- Greatest sum of strictly increasing subsequence
"""


'''
Given an array of positive integers find the longet increasing subsequence
'''
def LIS(arr):
	N = len(arr)
	A = [[(0,0) for _ in xrange(N)] for _ in xrange(N)]

	for r in xrange(N):
		for l in xrange(r):
			length, last = A[l][r - 1]
			x = arr[r]
			if x > last:
				A[l][r] = (length + 1, x)
			else:
				A[l][r] = (length, last)

	return A[N][N][0]
			

'''
Given an array find the longest strictly increasing subsequencce
with the longest sum
'''
def MIS(arr):
	N = len(arr)
	A = [[(0,0) for _ in xrange(N)] for _ in xrange(N)]

	for r in xrange(N):
		for l in xrange(r):
