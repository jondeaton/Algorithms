#!/usr/bin/env python
# Build a queue using only two stacks

class queue:
	def __init__(self):
		self.stack0 = Stack()
		self.stack1 = Stack()

	def enqueue(self, el):
		self.stack0.push(el)

	def dequeue(self):
		if self.stack1.empty():
			while not self.stack0.empty():
				self.stack1.push(self.stack0.pop())
		return self.stack1.pop()