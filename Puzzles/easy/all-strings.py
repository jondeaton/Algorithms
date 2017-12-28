#!/usr/bin/env python2.7
"""
Write a program which loops through all lowercase strings, returning true
when it has found a target string.
"""

import sys
import string
chars = string.ascii_lowercase

def search(target):
	"""
	Breath first search!
	"""
	queue = [c for c in chars]	
	while queue:
		prefix = queue[0]
		queue = queue[1:] # pop
		for c in chars:
			word = c + prefix
			if word == target: return True
			queue.append(word)
	return False

def main():
	target = sys.argv[1]
	print search(target)

if __name__ == "__main__": main()
