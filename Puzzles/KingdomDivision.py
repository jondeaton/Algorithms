#!/usr/bin/env python2.7
"""
Kingdom Division

Number of ways a tree can be colored two colors without
any node being connected to only nodes of a different color
"""

import sys


class Solution(object):

	def __init__(self, adj):
		self.adj = adj
		self.N = len(adj)
		self.visited = [False for _ in xrange(self.N)]

	def solution(self):
		result = self.ways(0)
		return (result[0] + result[1]) % (10**9 + 7)

	def ways(self, i):
		self.visited[i] = True

		answers = [] 

		red = 1
		blue = 1
		d_red = 1
		d_blue = 1

		for c in self.adj[i]:
			if self.visited[c]: continue

			c_red, c_blue, c_d_red, c_d_blue = self.ways(c)
			
			red *= (c_red + c_blue + c_d_red)
			blue *= (c_red + c_blue + c_d_blue)
			d_red *= c_blue
			d_blue *= c_red

		red -= d_red
		blue -= d_blue

		return red, blue, d_red, d_blue


def getAdj(N, data): 
    adj = [[] for _ in xrange(N)]

    for i in xrange(N - 1):
        u, v = map(lambda x: int(x) - 1, data[i].split())
        adj[u].append(v)
        adj[v].append(u)
    return adj


def main():
    N = int(raw_input())
    sys.setrecursionlimit(max(1500, N))
    data = sys.stdin.readlines()
    adj = getAdj(N, data)

    s = Solution(adj)
    print s.solution()


main()