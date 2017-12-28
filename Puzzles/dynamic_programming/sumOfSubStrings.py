#!/usr/bin/env python2.7
"""
Given a string of digits return the sum of all substrings
"""

E = 10**9 + 7

def solution(arr):
    N = len(arr)
    answers = [0 for _ in xrange(N)]

    answers[0] = arr[0]

    for i in xrange(1, N):
        answers[i] = (10 * (answers[i - 1])) % E
        answers[i] += ((i + 1) * arr[i]) % E

    return sum(answers)

def main():
    arr = map(int, raw_input())
    print solution(arr) % E

main()