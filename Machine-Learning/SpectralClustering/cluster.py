#!/usr/bin/env python
"""
File: cluster
Date: 12/17/18
Author: Jon Deaton (jdeaton@stanford.edu)

Inspired by "A Tutorial on Spectral Clustering" by Ulrike von Luxburg
http://www.kyb.mpg.de/fileadmin/user_upload/files/publications/attachments/Luxburg07_tutorial_4488%5b0%5d.pdf
"""

from enum import Enum

import scipy
import numpy as np
import matplotlib.pyplot as plt

from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.metrics.cluster import completeness_score, homogeneity_score
from sklearn.neighbors import NearestNeighbors


class Similarity(Enum):
    eps_neighborhood = 1
    knn = 2
    fully_connected = 3


class LaplacianNorm(Enum):
    symmetric = 1
    random_walk = 2


def draw_points(m, n, k):
    # Sample m points from an n dimensional mixture of k Gaussians
    mu = np.random.random((k, n)) * 8

    # random covariance matrices
    sigma = np.empty((k, n, n))
    for j in range(k):
        s = np.random.randn(n, n)
        sigma[j] = np.matmul(s, s.T) / 30
        # sigma[j] = np.eye(n) / 10

    phi = np.random.random(k)
    phi /= phi.sum()

    Z = list(range(k))  # latent space
    z = np.random.choice(Z, m, p=phi)

    X = np.empty((m, n))
    for j in range(k):
        X[z == j] = np.random.multivariate_normal(mu[j], sigma[j], X[z == j].shape[0])
    return X, z


def fully_connected_similarity(X, neighborhood_width=1):
    sigma = neighborhood_width
    m, n = X.shape
    S = np.empty((m, m))
    for i in range(m // 2 + 1):
        x = X[i]
        dists = np.linalg.norm(X - x, ord=2, axis=1)
        S[i, :] = np.exp(- dists / (2 * pow(sigma, 2)))
        S[:, i] = S[i, :]
    return S


def epsilon_neighborhood_similarity(X, epsilon=1.7):
    m, n = X.shape
    S = np.empty((m, m))
    for i in range(m // 2 + 1):
        x = X[i]
        dists = np.linalg.norm(X - x, ord=2, axis=1)
        S[i, :] = (dists < epsilon).astype(float)
        S[:, i] = S[i, :]
    return S


def k_nearest_neighbor_graph(X, k=5, mutual=False):
    m, n = X.shape

    knn = NearestNeighbors(n_neighbors=k)
    nbrs = knn.fit(X)
    _, indices = nbrs.kneighbors(X)

    S = np.zeros((m, m), dtype=int)
    for i in range(m):
        S[i, indices[i]] += 1

    S = S + S.T
    if mutual:
        # mutual nearest neighbors
        S = np.where(S == 2, 1, 0)
    else:
        S = np.where(S > 0, 1, 0)

    return S


def similarity_matrix(X, similarity_method=Similarity.fully_connected, **kwargs):
    if similarity_method == Similarity.fully_connected:
        S = fully_connected_similarity(X, **kwargs)
    elif similarity_method == Similarity.eps_neighborhood:
        S = epsilon_neighborhood_similarity(X, **kwargs)
    elif similarity_method == Similarity.knn:
        S = k_nearest_neighbor_graph(X, **kwargs)
    else:
        raise ValueError("Unknown similarity method %s" % similarity_method)
    return S


def spectral_clustering(S, k, normalization=None, generalized_eigenproblem=False, norm_rows=False):
    m, _ = S.shape

    W = S.copy()
    d = W.sum(axis=1)
    D = None

    if normalization is None:
        # un-normalized graph Laplacian
        D = np.diag(d)
        L = D - W
    elif normalization == LaplacianNorm.symmetric:
        D_sqrt_neg = np.diag(np.power(d, -0.5))
        I = np.eye(m)
        L = I - np.matmul(np.matmul(D_sqrt_neg, W), D_sqrt_neg)  # I - D^{-1/2} W D^{-1/2}
    elif normalization == LaplacianNorm.random_walk:
        D_inv = np.diag(1 / d)
        I = np.eye(m)
        L = I - np.matmul(D_inv, W)  # I - D^{-1} W
    else:
        raise ValueError("Unrecognized Laplacian normalization: %s" % normalization)

    if generalized_eigenproblem:
        if D is None:
            D = np.diag(d)
        w, v = scipy.linalg.eig(L, D)
    else:
        w, v = np.linalg.eig(L)

    order = w.argsort()
    U = v[:, order[:k]]  # first k eigenvalues

    if norm_rows:
        row_sums = np.linalg.norm(U, axis=1)
        U = U / row_sums[:, np.newaxis]

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
    if n == 0 or m == 0: return

    if n > 2:
        pca = PCA(n_components=2)
        x = pca.fit_transform(X)
        return show_points(x, z, title=title)

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
    m = 2000 # number of points
    n = 50 # Number of dimensions
    k = 30 # Number of latent clusters

    np.random.seed(3)
    X, z_true = draw_points(m, n, k=k)
    show_points(X, z_true, title="True")

    S = fully_connected_similarity(X)

    # Unnormalized spectral clustering
    # A = spectral_clustering(S, k)

    # Normalized spectral clustering according to Shi and Malik (2000)
    # A = spectral_clustering(S, k, normalization=LaplacianNorm.symmetric, generalized_eigenproblem=True)

    # Normalized spectral clustering according to Ng, Jordan, and Weiss (2002)
    A = spectral_clustering(S, k, normalization=LaplacianNorm.symmetric, norm_rows=True)

    show_points(X, A, title="Spectral Clustering")

    complete_score = completeness_score(z_true, A)
    homog_score = homogeneity_score(z_true, A)
    print("Completeness score: %s" % complete_score)
    print("Homogeneity score: %s" % homog_score)


if __name__ == "__main__":
    main()
