#!/usr/bin/env python
'''
Given a template and a pattern where the pattern is 
a string of "a" and "b" characters, determine if
there is some way to replace "a" and "b" with 
some string in the pattern to produce the tempalte.
'''

def isMatch(template, pattern):
	print "template: %s, pattern: %s --> %s" % (template, pattern, matching(template, pattern))

def matching(template, pattern):
	na = pattern.count("a")
	nb = pattern.count("b")
	n = len(template)

	Na = (n - nb) / na # largest possible value for sizeA
	for sizeA in xrange(1, Na + 1):
		if (n - sizeA * na) % nb != 0:
			continue
		sizeB = (n - sizeA * na) / nb
		if matches(template, pattern, sizeA, sizeB):
			return True
	return False

def matches(template, pattern, sizeA, sizeB):
	i = 0
	a = None
	b = None
	for x in pattern:
		if x == "a" and a is None:
			a = template[i : i + sizeA]
		if x == "b" and b is None:
			b = template[i : i + sizeB]

		word = a if x == "a" else b
		if not template[i:].startswith(word):
			return False
		i += len(word)

	return True

if __name__ == "__main__":
	isMatch("catcatgogocat", "aabba")
	isMatch("owiejfowiejfoeiw", "ab")
	isMatch("catgocatgo", "abab")
	isMatch("going", "aba")
	isMatch("12345", "aba")
	isMatch("121212122", "abab")