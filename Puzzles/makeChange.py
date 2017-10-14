#!/usr/bin/env python
'''
You have m types of coins with values given in array C of size m
With infinitely many of each coin, how many ways can you select 
coins who's values sum up to n

"How many ways can you make chagne for n with the given m coin values"
'''


"""

time complecity: O(mn)
space complexity: O(mn)
"""
def solution(C, n):
	M = len(C)

	A = [[0 for _ in xrange(M)] for _ in xrange(n + 1)]
	A[0] = [1 for _ in xrange(M)] # one way to make zero

	for m in xrange(M):
		coin = C[m]
		for s in xrange(1, n + 1):
			if m > 0:
				A[s][m] += A[s][m - 1] # exclude the coin
			if s >= coin:
				A[s][m] += A[s - coin][m] # include the coin

	return A[n][M - 1]


def main():
	coins = [1, 5, 10, 25, 50, 100]
	print solution(coins, 100030)

if __name__ == "__main__":
	main()