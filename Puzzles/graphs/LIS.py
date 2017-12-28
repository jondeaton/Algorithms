#!/usr/bin/env python2.7
"""
Find the strictly increasing subsequence with the greatest sum
"""

def LIS(arr):
	N = len(arr)
	answers = [1 for _ in xrange(N)]

	for r in xrange(N):
		longest = 1
		for i in xrange(r):
			if arr[r] > arr[i] and answers[i] + 1 > longest:
				longest = answers[i] + 1
		answers[r] = longest

	return max(answers)


# strictly increasing subsequence with greatest sum
def MIS(arr):
	N = len(arr)
	sums = [x for x in arr]

	for r in xrange(N):
		greatest = arr[0]
		for i in xrange(r):
			if arr[r] > arr[i]:
				greatest = max(greatest, arr[r] + sums[i])
		sums[r] = greatest
	return max(sums)

def main():
	l = [1, 2, 3, 4, 5, 0, 3, 4, 10, 11, 5, 12, 0, 200]
	print LIS(l)
	print MIS(l)



if __name__ == "__main__":
	main()