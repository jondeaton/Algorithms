#!/usr/bin/env python2.7
# Algorithm for finding the longest path in a connected, acyclical graph (tree)

class Graph:
	def __init__(self, numVertices, adjacencyList):
		self.N = numVertices
		self.adjacencyList = adjacencyList
		self.visited = [False for _ in xrange(N)]

	def resetVisited(self):
		self.visited = [False for _ in xrange(N)]

def getFurthestAway(graph, start):
	# Simple breadth first search keeping track of visited nodes
	# and the furthest node away
	if graph.N == 0:
		return None

	queue = [(0, start)] # Distance from start to itself is zero!
	maxDistance = 0 # Stores the maximum distance seen thus far
	furthestNode = None # Stores the number of the current node
	while (len(queue) > 0):

		# Pop off the next node to search 
		dist, n = queue[0]
		queue = queue[1:]

		if graph.visited[n]: continue # don't retrace steps
		
		# Remember the furthest away, if we have found it
		if dist > maxDistance:
			maxDistance = dist
			furthestNode = n

		queue += [(dist + 1, c) for c in graph.adjacencyList[n] if not graph.visited[n]]
		graph.visited[n] = True

	return maxDistance, furthestNode

def getLongeastPath(graph):
	# This algorithm takes the form of two breath first searches
	# for the longest node away from a given node, 
	if graph is None: return 0

	dist, n = getFurthestAway(graph, 0)
	graph.resetVisited()
	return getFurthestAway(graph, n)[0]