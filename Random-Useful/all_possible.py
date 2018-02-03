#!/usr/bin/env python

import numpy as np

def all_possible(A, index=0):
	if index == A.shape[0]: yield
	else:
		for _ in all_possible(A, index + 1):
			for i in xrange(2):
				A[index] = i
				yield

N = 5
A = np.zeros(N)
for _ in all_possible(A):
	print A
