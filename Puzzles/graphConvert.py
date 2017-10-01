#!/usr/bin/env python
# For converting between different representation of a graph

class Graph()
	def __init__(self, numVertices, adjacencyList):
		self.N = numVertices
		self.adjacencyList = adjacencyList
		self.visited = [False for _ in xrange(numVertices)]

	def resetVisited(self):
		self.visited = [False for _ in xrange(numVertices)]

class Node:
	def __init__(self, value=None, connections=[])
		self.value = value
		self.connections = connections
		self.visited = False

def adjacencyPairs2Obj(adjacencyPairs, valueList=None):
	pass

def adjacencyList2Obj(adjacencyList, valueList=None):
	N = len(adjacencyList)
	if N <= 0: return None

	if valueList is None:
		nodes = [Node() for _ in xrange(N)]
	else:
		nodes = [Node(value=valueList[i]) for i in xrange(N)]

	for i in xrange(N):
		nodes[i].connections = [nodes[j] for j in adjacencyList[i]]

	return nodes[0]
