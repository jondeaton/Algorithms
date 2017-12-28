#!/usr/bin/env python
"""
Find a path through a maze
"""

def answer(isFree):
	c = len(isFree[0])
	r = len(isFree)
	A = [[False for x in range(c)] for y in range(r)]
	return existsPath(isFree, A, [0, 0])

def existsPath(isFree, wasVisited, start):
	r = start[0]
	c = start[1]
	R = len(isFree)
	C = len(isFree[0])

	if r == R or c == C:
		return False

	if not isFree[r][c]:
		return False

	if wasVisited[r][c]:
		return False

	if r + 1 == R and c + 1 == C:
		return True

	wasVisited[r][c] = True
	return existsPath(isFree, wasVisited, [r + 1, c]) or existsPath(isFree, wasVisited, [r, c + 1])

def main():
	maze = [[True, True, True] for _ in range(3)]
	print(answer(maze))

	maze = [[True, False, True] for _ in range(10)]
	print(answer(maze))


	maze = [[True, False, True] for _ in range(10)]
	maze[5][1] = True
	print(answer(maze))

if __name__ == "__main__": main()
