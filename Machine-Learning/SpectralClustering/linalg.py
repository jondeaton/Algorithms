#!/usr/bin/env python
"""
File: linalg
Date: 12/20/18 
Author: Jon Deaton (jdeaton@stanford.edu)
"""

import numpy as np


def proj(u, v):
    return np.matmul(u, v) * u / np.matmul(u.T, u)


def cos_angle(u, v):
    return np.dot(u, v) / np.linalg.norm(u) / np.linalg.norm(v)


def rotation_matrix(x, y):
    """
    Finds a rotation matrix which rotates x to y in R^n

    Based on https://math.stackexchange.com/questions/598750/finding-the-rotation-matrix-in-n-dimensions

    :param x: vector in R^n
    :param y: vector in R^n
    :return: rotation matrix in R^(n x n) for rotation
    """
    n, = x.shape

    u = x / np.linalg.norm(x)
    y_hat = y / np.linalg.norm(y)

    v = y_hat - np.dot(u, y_hat) * u
    v /= np.linalg.norm(v)

    cos_t = cos_angle(u, v)
    sin_t = np.sqrt(1 - np.power(cos_t, 2))
    r = np.array([[cos_t, - sin_t], [sin_t, cos_t]])
    up = np.array([u, v]).T

    R = np.eye(n) - np.outer(u, u) - np.outer(v, v)
    R += np.matmul(np.matmul(up, r), up.T)

    return R


def random_rotation(n):
    # u := sampled uniformly on unit sphere
    u = np.random.randn(n)
    u /= np.linalg.norm(u)

    e1 = np.zeros(n)
    e1[0] = 1
    return rotation_matrix(e1, u)


def eig(A, tol=0.01):
    # How doth one finds the eigen-vec-tours?
    # A gotta be symmetric
    X = A
    while True:
        Q, R = qr(X)
        Xn = np.matmul(R, Q)
        if all(np.abs(np.diag(X) - np.diag(Xn)) < tol):
            break
    return Q, np.diag(X)


def orth(B, x):
    # Finds a vector parallel to x orthogonal to the basis B
    if B.size == 0: return x
    p = np.matmul(B.T, x)
    return x - np.sum(p * B.T, axis=0)


def qr(A):
    # yeh know, np.linalg.qr wasn't cutting it
    m, n = A.shape

    Q = np.empty((m, n))
    R = np.zeros((n, n))

    for i in range(n):
        a = A[:, i]
        u = orth(Q[:, :i], a)
        e = u / np.linalg.norm(u)
        Q[:, i] = e

        R[:i+1, i] = np.matmul(Q[:, i+1].T, a)

    return Q, R
