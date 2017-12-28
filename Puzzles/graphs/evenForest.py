#!/usr/bin/env python
"""
Given a tree, find the number of cuts that could be made
so that all graphs formed have an even number of nodes
"""

import sys

visited = set()

def getChildren(A, i):
    children = []
    for node in A[i]:
        if node != 0:
            children += [node]
    return children

def evenForstSize(A):
    return subForest(A, 1)[1]

def subForest(A, i):
    visited.add(i) # mark this node as visited first since we are DFS
    children = getChildren(A, i)
    
    if len(children) == 1:
        return 1, 0 # Forest is size 1, no disconnections
    
    size_of_forest = 1
    numDisconnects = 0
    for j in getChildren(A, i):
        if j in visited: continue # skip already visited node (parents)
        size, numDisconnects = subForest(A, j)
        if (size % 2): # odd child, must connect to it
            size_of_forest += size
        else:
            numDisconnects += 1 + nunDisconnects
            
    return size_of_forest, numDisconnects
   
def makeAdjacencyMatrix(data):
    N = int(data[0].split()[0])
    M = int(data[0].split()[1])
    A = [[0 for _ in xrange(N + 1)] for _ in xrange(N + 1)]
    for line in data[1:]:
        u = int(line.split()[0])
        v = int(line.split()[1])
        A[u][v] = 1
        A[v][u] = 1
    return A
    
def main():
    data = sys.stdin.readlines()
    A = makeAdjacencyMatrix(data)
    return evenForstSize(A)
    
    
print main()