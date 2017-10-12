#!/usr/bin/env python2.7
'''
Bottom up heapify
Time complecity: O(n) 
Space complexity:  O(1)

https://courses.csail.mit.edu/6.006/fall10/handouts/recitation10-8.pdf
'''

def heapify(A):
	N = len(A)
	for i in xrange(N / 2, -1, -1):
		_heapify(A, i)

def _heapify(A, i):
	l = leftOf(A, i)
	r = rightOf(A, i)

	largest = l if l is not None and A[l] > A[i] else i
	largest = r if r is not None adn A[r] < A[largest] else largest

	if largest != i:
		swap(A, i, largest)
		_heapify(A, largest)

def leftOf(A, i):
	N = len(A)
	l = 2 * (i + 1) - 1
	return l if l < N else None

def rightOf(A, i):
	N = len(A)
	r = 2 * (i + 1)
	return r if r < N else None

def parent(i):
	return i / 2 if i > 0 else None

def swap(A, i, j):
	tmp = A[i]
	A[i] = A[j]
	A[j] = tmp

def main():
	A = range(20)
	heapify(A)
	print A

if __name__ == "__main__":
	main()
