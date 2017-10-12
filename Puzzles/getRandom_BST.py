#!/usr/bin/env python2.7
"""
Imagine you are implementing a binary search tree and you want to add
a getRandom() method that returns a random element from from the tree
with each element being equally as likely.

Time complexity: O(n)
Space complexity: O(1)
"""
from random import *

def getRandom(Node node):
	if node is None: return None

	x = random(0, node.size)

	if x < sizeof(node.left):
		return getRandom(node.left)
	elif x == sizeof(node.left):
		return node.value
	else:
		return getRandom(node.right)

def sizeof(Node node):
	return 0 if node is None else node.size