#!/usr/bin/env python2.7
"""

"""

def LIS(arr):
	N = len(arr)
	answers = [1 for _ in xrange(N)]

	for r in xrange(N):
		longest = 0
		for i in xrange(r):
			if arr[r] > arr[i] and answers[i] + 1 > longest:
				longest = answers[i] + 1
		answers[r] = longest

	return max(answers)


# strictly increasing subsequence with greatest sum
def MIS(arr):
	N = len(arr)
	sums = [0 for _ in xrange(N)]

	for r in xrange(N):
		greatest = 0
		for i in xrange(r):
			if arr[r] > arr[i]:
				greatest = max(greatest, arr[r] + sums[i])

	return max(sums)



def main():
	l = [1, 2, 3, 4, 5]
	print LIS(arr)



if __name__ == "__main__":
	main()