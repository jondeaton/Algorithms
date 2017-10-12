#!/usr/bin/env python
'''
Determine if there is a path between two nodes in a graph
'''

# Object representation traversal
def findPathObject(Node A, Node B):
	q = [A]
	while q:
		
		n = q.pop()

		for c in c.connections:
			if c.visited: continue
			if c is b:
				return true
			q.append(c)

		n.visited = True

	return False

# Adjacency list traversal
def findPathAdjacency(A, i, j):
	q = [i]
	visited = {i}
	while q:
		
		n = q.pop()
		
		for c in A[n]:
			if c == j: return True
			if c in visited: continue
			q.append(c)
			visited.add(c)
	return False

# Weight matric traversal
def findPathWeighted(A, i, j):
	pass
	# todo

def main():
	A = [[0, 1, 2, 3], [3, 2], [3], [0]]
	findPathAdjacency(A)

if __name__ == "__main__":
	main()