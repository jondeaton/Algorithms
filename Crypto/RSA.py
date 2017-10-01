#!/usr/bin/env python
# RSA.py
# This module provides functionality for the RSA cryptosystem
# Dependencies: numpy, argparse
# Jonathan Deaton, 12/25/2015

import sys, argparse, random, time
import numpy as np

# Fermat Primality Test
# False if candidate is definitely composite, True if candidate is probably prime
def fermat_primality(candidate, k = 70):
    for _ in xrange(k):
        a = random.randint(2, candidate - 2)
        if not pow(a, candidate - 1, candidate) == 1:
            return False
    return True

# Miller-Rabin Primality Test
# False if candidate is definitely composite, True if candidate is probably prime
def miller_rabin(candidate, k = 70):
    if candidate <= 7: #Store answers for small primes
        return [False, False, True, True, False, True, False, True][candidate]

    if candidate & 1 == 0:
        return False

    # Candidate = d * 2^s + 1
    s = 0
    d = candidate - 1
    while not d & 1: #Factor 2 out of n - 1 until d is odd
        d /= 2
        s += 1

    for _ in xrange(k):
        a = random.randint(2, candidate - 2)
        x = pow(a, d, candidate)
        if x == 1 or x + 1 == candidate:
            continue

        for r in xrange(1, s):
            x = pow(x, 2, candidate)
            if x == 1:
                return False
            if x == candidate  - 1:
                continue
        return False
    return True

# Tests the primality of a number exhaustively
# Not used for RSA key-generation but interesting and useful in debugging
def is_prime(N):
        if not N & 1:
                return False
        n = 3
        while n <= int(pow(N, 0.5)):
                if N % n == 0:
                        return False
                n += 2
        return True

# Returns a list of all primes below a given integer
def primes_below(N):
    primes = np.array([2])
    for n in xrange(3, N, 2):
        if 0 not in n % primes:
            primes = np.append(primes, n)
    return list(primes)

# Returns a random odd number between low and high, inclusively
def random_odd(low, high):
    if low > high or (high == low and not low & 1): # low > high, or both equal and
        raise
    elif high - low == 1:
        return [low, high][high & 1]
    else:
        a=2
        while not a & 1:
            a = random.randint(low, high)
        return a

# Returns a number between low and high that is probably prime
def random_probably_prime(low, high):
    low_primes = np.array(primes_below(1000))
    candidate = random_odd(low, high)
    while True:
        if candidate in low_primes:
            return candidate
        if 0 in candidate % low_primes or not fermat_primality(candidate)or not miller_rabin(candidate):
            candidate += 2
            if candidate > high:
                candidate = low
        else:
            return candidate

# Returns a number that is probably prime having num_bits number of bits
def probably_prime(num_bits):
    low = pow(2, num_bits - 1) + 1
    high = pow(2, num_bits) - 1
    return random_probably_prime(low, high)

# Extended Euclidian Algorithm
# Solves as + bt = gcd(a,b) for s,t given a,b
def extended_euclidian_algorithm(a, b):
    r = [a, b]
    s = [1, 0]
    t = [0, 1]
    while not r[1] == 0:
        q = r[0] / r[1]
        euclidian_step(r, q)
        euclidian_step(s, q)
        euclidian_step(t, q)
    return s[0], t[0]

# Performs the calculation of a single "step" in the Extended Euclidian Algorithm
def euclidian_step(r, q):
    next = r[0] - q * r[1]
    r[0] = r[1]
    r[1] = next

# Modular Multiplicitave Inverse
# Returns d such that de = 1 (mod z)
# Method: rearranging the above: de - 1 = qz, thus de - qz = 1
def modular_multiplicitave_inverse(e, z):
    d, q = extended_euclidian_algorithm(e, z)
    return d

# Euler's Toitent Function, phi(n) = (p-1)(q-1), if n = p*q
# Counts the positive integers less than or equal to n that are relatively prime to n
def toitent_function(p, q):
    return (p - 1) * (q - 1)

# Returns the public key, private key, and modulus for
# the RSA cryptosystem defined by p and q: two primes
def get_keys(p, q):
    n = p * q
    z = toitent_function(p, q)
    e = random_probably_prime(7, z)
    d = modular_multiplicitave_inverse(e, z)
    if d < 0:
        d += z
    return e, d, n

# Generates a new keyset with prime numbers that have num_bits number of bits
def new_keyset(num_bits):
    if num_bits < 3:
        raise
    p = probably_prime(num_bits)
    q = p
    while q == p:
        q = probably_prime(num_bits)
    print p
    print q
    return get_keys(p, q)

# Integer Modular Exponentiation
def mod_pow(b, p, m):
    if m == 1:
        return 0

    c = 1
    while p > 0:
            if p & 1:
                c = (c * b) % m
            b = pow(b, 2) % m
            p /= 2
    return c

# Integer Encryption and Decryption
# This function encrypts integer x given a key and modulus
def crypt(x, key, modulus):
    return pow(x, key, modulus)

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('-b', '--num_bits', type=int, default=56, help='Number of bits in prime numbers')
    args = parser.parse_args()
    num_bits = args.num_bits

    if num_bits <= 2:
        print "Choose a bit size > 2"
        sys.exit()

    if num_bits == 64:
        print "This program has trouble finding 64-bit prime numbers"
        print "If you can figure out why, please email me at jonpauldeaton@gmail.net"
        print "Proceeding with prime bit-length of 65..."
        num_bits = 65
        time.sleep(5)

    print 'Generating 1st %d bit prime... ' % num_bits,
    sys.stdout.flush()
    start = time.clock()
    p = probably_prime(num_bits)
    print '%.3f seconds' % (time.clock() - start)
    print 'p:\t%d' % p

    print 'Generating 2nd %d bit prime... ' % num_bits,
    sys.stdout.flush()
    start = time.clock()
    q = p
    while q == p:
        q = probably_prime(num_bits)
    print '%.3f seconds' % (time.clock() - start)
    print 'q:\t%d' % q

    print 'Generating RSA keys... ',
    sys.stdout.flush()
    start = time.clock()
    public_key, private_key, modulus = get_keys(p, q)
    print '%.3f seconds' % (time.clock() - start)
    print 'Public key:\t%d' % public_key
    print 'Private key:\t%d' % private_key
    print 'Modulus (N):\t%d' % modulus


    print "Encryption / Decryption Example"
    message = random.randint(2, modulus)

    print "Encrypting message:\t%d" % message
    start = time.clock()
    encrypted = crypt(message, public_key, modulus)
    print "Encrypted message:\t%d" % encrypted
    decrypted = crypt(encrypted, private_key, modulus)
    print "Decrypted message:\t%d" % decrypted

    if decrypted == message:
        print "Encryption successful (%.2f sec)" % (time.clock() - start)
    else:
        print "Encryption failure"