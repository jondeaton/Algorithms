#!/usr/bin/env python2.7
"""
Kingdom Division

Number of ways a tree can be colored two colors without
any node being connected to only nodes of a different color
"""

import sys

def computeAnswer(adj, answers, completed, n):
    # compute the answer    
    red, blue, d_red, d_blue = 1, 1, 1, 1       
    
    for c in adj[n]:
        if not completed[c]: continue
        c_red, c_blue, c_d_red, c_d_blue = answers[c]
        red *= (c_red + c_blue + c_d_red)
        blue *= (c_red + c_blue + c_d_blue)
        d_red *= c_blue
        d_blue *= c_red
    red -= d_red
    blue -= d_blue

    return red, blue, d_red, d_blue

"""
Dynamic programing without recursion
"""
def solution(adj):
    N = len(adj)
    visited = [False for _ in xrange(N)]
    completed = [False for _ in xrange(N)]
    answers = {}

    queue = [0]
    while queue:
        n = queue[-1]
        visited[n] = True

        # All children are computed
        all_completed = True
        for c in adj[n]:
            if visited[c]: continue
            if not completed[c]:
                all_completed = False
                break

        if all_completed:
            answers[n] = computeAnswer(adj, answers, completed, n)
            completed[n] = True
            queue.pop() # done with this one

        else:
            # Some child has not been calculated... requeue
            for c in adj[n]:
                if not visited[c] and not completed[c]:
                    queue.append(c)

        # print "Queue: %s" % queue
        # print "Answers: %s" % answers

    return answers[0][0] + answers[0][1]


class Solution(object):

    def __init__(self, adj):
        self.adj = adj
        self.N = len(adj)
        self.visited = [False for _ in xrange(self.N)]

    def computeAnswer(self, n):
        # Compute the answer
        for c in self.adj[i]:
            if c == n: continue # Don't compute self
            c_red, c_blue, c_d_red, c_d_blue = self.ways(c)
            red *= (c_red + c_blue + c_d_red)
            blue *= (c_red + c_blue + c_d_blue)
            d_red *= c_blue
            d_blue *= c_red
        red -= d_red
        blue -= d_blue

    """
    Dynamic programing with recursion
    """
    def solution(self):
        result = self.ways(0)
        return (result[0] + result[1])

    def ways(self, i):
        self.visited[i] = True

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
    data = sys.stdin.readlines()
    adj = getAdj(N, data)

    # s = Solution(adj)
    # print s.solution() % (10**9 + 7)
    print solution(adj) % (10**9 + 7)


main()