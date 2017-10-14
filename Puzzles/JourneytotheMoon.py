#!/usr/bin/env python2.7
"""
The member states of the UN are planning to send  people to
the Moon. But there is a problem. In line with their principles of 
global unity, they want to pair astronauts of  different countries.

There are  trained astronauts numbered from  to . But those in charge 
of the mission did not receive information about the citizenship of each astronaut.
The only information they have is that some particular pairs of astronauts belong 
to the same country.

Your task is to compute in how many ways they can pick a pair of astronauts 
belonging to different countries. 
"""


def solution(adj, N, P): 
    visited = [False for _ in xrange(N)]    
    
    num_covered = 0
    total = 0
    for n in xrange(N):
        if visited[n]: continue
        country_size = 0

        queue = [n]
        while queue:
            k = queue.pop()
            if visited[k]: continue
            visited[k] = True

            country_size += 1
            for c in adj[k]:
                if visited[c]: continue    
                queue.append(c)
                
        total += num_covered * country_size
        num_covered += country_size
    return total


def getAdj(N, P): 
    adj = [[] for _ in xrange(N)]
    for i in xrange(P):
        a, b = map(int, raw_input().split())
        adj[a].append(b)
        adj[b].append(a)
    return adj

def main(): 
    N,P = map(int,raw_input().split())
    adj = getAdj(N, P)
    print solution(adj, N, P)

if __name__ == "__main__":
    main()


