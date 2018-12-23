#!/usr/bin/env python
"""
File: sample
Date: 12/20/18 
Author: Jon Deaton (jdeaton@stanford.edu)
"""

import numpy as np
import linalg


def random_bernoilu(m, k):
    phi = np.random.random(k)
    phi /= phi.sum()

    Z = list(range(k))  # latent space
    z = np.random.choice(Z, m, p=phi)
    return z


def sample_coils(m, n, k):
    z = random_bernoilu(m, k)

    position = np.random.uniform(-1, 1, (k, n))
    radius = 1 + np.random.randn(k) * 10
    freq = np.random.randn(k) * 6
    height = 1 + np.random.rand(k) * 10

    X = np.empty((m, n))
    for j in range(k):
        mj, _ = X[z == j].shape
        t = np.random.uniform(0, 1, mj)

        spiral = np.empty((mj, n))
        tangent = np.empty((mj, n))

        spiral[:, 0] = height[j] * t
        tangent[:, 0] = height[j]

        w = 2 * np.pi * freq[j]
        r = radius[j]
        for i in range(1, n):
            phi = (i - 1) * np.pi / 4
            spiral[:, i] = r * np.sin(w * t + phi)
            tangent[:, i] = r * w * np.sin(w * t + phi + np.pi / 4)

        # error term off the coil's axis
        eps = np.random.randn(mj, n) / 50
        er = eps - np.matmul(tangent.T, np.sum(eps * tangent, axis=1)).T

        R = linalg.random_rotation(n)
        X[z == j] = position[j] + np.matmul(spiral + er, R)
    return X, z


def sample_gmm(m, n, k):
    # Sample m points from an n dimensional mixture of k Gaussians
    mu = np.random.random((k, n)) * 5

    # random covariance matrices
    sigma = np.empty((k, n, n))
    for j in range(k):
        s = np.random.randn(n, n)
        sigma[j] = np.matmul(s, s.T) / 10
        # sigma[j] = np.eye(n) / 10

    z = random_bernoilu(m, k)

    X = np.empty((m, n))
    for j in range(k):
        X[z == j] = np.random.multivariate_normal(mu[j], sigma[j], X[z == j].shape[0])
    return X, z
