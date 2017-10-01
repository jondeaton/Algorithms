#!/usr/bin/env python

import sys
import argparse


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('-u', '--upper_bound', type=int, default=1000, help="Upper bound on largest prime")
    parser.add_argument('-out', '--output_file', type=str, help="output file name")
    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose Output')
    args = parser.parse_args()

    upper_bound = args.upper_bound
    output = args.output_file
    verbose = args.verbose

    primes = [2] + range(3, upper_bound, 2)

    for p in primes:
        if p in primes:
            primes[:] = [n for n in primes if n % p != 0 or n == p]

    if verbose:
        print primes

    if output:
        open(output, 'w').write(primes.__str__().replace(' ', '')[1: -1])
