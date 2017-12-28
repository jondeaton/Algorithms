#!/usr/bin/env python
"""
Classic Dynamic Programing Question:

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
"""

'''
Dynamic programing solution without recursion
Time complexity: O(n)
Space complexity: O(n)
'''
def solution(ratings):
	n = len(ratings)
	candies = [0 for _ in xrange(n)]

	for i in xrange(n):
		if candies[i] != 0: continue

		x = ratings[i]
		exceedRight = i < n - 1 and x > ratings[i + 1]
		if exceedRight and candies[i + 1] == 0:

			# Find one that we can get the answer of, or already have the answer to
			for j in xrange(i + 1, n):
				if j == n - 1: break 
				if ratings[j + 1] > ratings[j]: break

			candies[j] = 1

			j =- 1 # back up off of the one we found

			# Count up backwards until we have an answer at candies[i + 1]
			while j > i:
				candies[j] = 1 + candies[j + 1]
				j -= 1

		exceedLeft = i > 0 and x > ratings[i - 1]
		# At this point we have an answer at candies[i + 1] if we need it
		if exceedLeft:
			if exceedRight:
				candies[i] = 1 + max(candies[i - 1], candies[i + 1])
			else:
				candies[i] = 1 + candies[i - 1]
		else:
			if exceedRight:
				candies[i] = 1 + candies[i + 1]
			else:
				candies[i] = 1

	return sum(candies)


'''
Dynamic programing solution with recursion (less good)
Time complecity: O(n)
Space complexity: O(n)
'''
class Solution(object):

	def __init__(self, ratings):
		self.ratings = ratings
		self.n = len(ratings)
		self.candies = [0 for _ in xrange(self.n)]

	def solution(self):
		for i in xrange(self.n):
			self.candies[i] = self.smallest(i)
		return sum(self.candies)

	def smallest(self, i):
		# No candies off the edges
		if i < 0 or i >= self.n: return 0

		# Answer already computed
		if self.candies[i] != 0: return self.candies[i] 

		x = self.ratings[i]
		exceedLeft = i > 0 and x > self.ratings[i - 1]
		exceedRight = i < self.n - 1 and x > self.ratings[i + 1]

		if exceedRight: self.candies[i + 1] = self.smallest(i + 1)

		if exceedLeft:
			if exceedRight: return 1 + max(self.candies[i - 1], self.candies[i + 1])
			else: return 1 + self.candies[i - 1]
		else:
			if exceedRight: return 1 + self.candies[i + 1]
			else: return 1

def main():
	ratings = [100000] + range(100000)
	print solution(ratings)

if __name__ == "__main__":
	main()