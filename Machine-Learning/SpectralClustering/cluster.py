#!/usr/bin/env python
"""
File: cluster
Date: 12/17/18 
Author: Jon Deaton (jdeaton@stanford.edu)
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import SpectralClustering
from sklearn.mixture import GaussianMixture
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.metrics.cluster import completeness_score


def draw_points(m, n, k):

    mu = np.random.random((k, n)) * 10

    # random covariance matrices
    sigma = np.empty((k, n, n))
    for j in range(k):
        s = np.random.randn(n, n)
        # sigma[j] = np.matmul(s, s.T)
        sigma[j] = np.eye(n) / 20

    phi = np.random.random(k)
    phi /= phi.sum()

    Z = list(range(k))  # latent space
    z = np.random.choice(Z, m, p=phi)

    X = np.empty((m, n))
    for j in range(k):
        X[z == j] = np.random.multivariate_normal(mu[j], sigma[j], X[z == j].shape[0])
    return X, z


def similarity_matrix(X):
    m, n = X.shape

    sigma = 1  # neighborhood width

    S = np.empty((m, m))
    for i in range(m // 2):
        x = X[i]
        dists = np.linalg.norm(X - x, ord=2, axis=1)
        S[i, :] = np.exp(- dists / (2 * pow(sigma, 2)))
        S[:, i] = S[i, :]
    return S


def spectral_clustering(S, k):
    W = S.copy()
    D = np.diag(W.sum(axis=1))
    L = D - W  # Laplacian

    w, v = np.linalg.eig(L)
    order = w.argsort()
    U = v[:, order[:k]]  # first k eigenvalues

    plt.figure()
    plt.plot(sorted(w))
    plt.title("Eigenvalues")
    plt.show()

    plt.figure()
    for i in range(k):
        plt.plot(sorted(v[:, order[i]]))
    plt.legend(["Eigenvector %d" % i for i in range(k)])
    plt.show()

    kmeans = KMeans(n_clusters=k)
    A = kmeans.fit_predict(U)
    return A


def show_points(X, z, title=None):
    m, n = X.shape

    if n > 2:
        pca = PCA(n_components=2)
        x = pca.fit_transform(X)
        show_points(x, z, title=title)

    if n == 1:
        plt.figure()
        plt.hist(X, bins=np.linspace(-1, 10, 150))
    else:
        plt.figure()
        plt.scatter(X[:, 0], X[:, 1], c=z)

    if title is not None:
        plt.title(title)
    plt.show()


def main():
    np.random.seed(1)
    m = 1000
    n = 2
    k = 2

    X, z_true = draw_points(m, n, k=k)
    show_points(X, z_true, title="True")

    S = similarity_matrix(X)

    A = spectral_clustering(S, k)

    show_points(X, A, title="Spectral Clustering")

    score = completeness_score(z_true, A)
    print("Score: %s" % score)


if __name__ == "__main__":
    main()
