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

from sklearn.cluster import KMeans, SpectralClustering
from sklearn.decomposition import PCA
from sklearn.metrics.cluster import completeness_score, homogeneity_score
from sklearn.neighbors import NearestNeighbors
from sklearn.mixture import GaussianMixture

import sample

class Similarity(Enum):
    eps_neighborhood = 1
    knn = 2
    fully_connected = 3


class LaplacianNorm(Enum):
    symmetric = 1
    random_walk = 2


class Distance(Enum):
    euclidian = 1
    cosine_similarity = 2


def fully_connected_similarity(X, dist=Distance.euclidian, neighborhood_width=1):
    sigma = neighborhood_width
    m, n = X.shape

    S = np.empty((m, m))
    for i in range(m):
        xi = X[i]

        if dist == Distance.euclidian:
            dists = np.linalg.norm(X - xi, ord=2, axis=1)
            S[i, :] = np.exp(- dists / (2 * pow(sigma, 2)))

        elif dist == Distance.cosine_similarity:
            dists = 1 + np.matmul(X, xi) / (np.linalg.norm(xi) * np.linalg.norm(X, axis=1))
            dists = dists.real
            S[i, :] = np.power(dists, 2)

        else:
            raise ValueError("Unrecognized distance metric: %s" % dist)
    return S


def epsilon_neighborhood_similarity(X, dist=Distance.euclidian, epsilon=1.7):
    m, n = X.shape
    S = np.empty((m, m))
    for i in range(m):
        x = X[i]
        dists = np.linalg.norm(X - x, ord=2, axis=1)
        S[i, :] = (dists < epsilon).astype(float)
    return S


def k_nearest_neighbor_graph(X, dist=Distance.euclidian, k=5, mutual=False):
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


def similarity_matrix(X, dist=Distance.euclidian, similarity_method=Similarity.fully_connected, **kwargs):
    if similarity_method == Similarity.fully_connected:
        S = fully_connected_similarity(X, dist=dist, **kwargs)
    elif similarity_method == Similarity.eps_neighborhood:
        S = epsilon_neighborhood_similarity(X, dist=dist, **kwargs)
    elif similarity_method == Similarity.knn:
        S = k_nearest_neighbor_graph(X,  dist=dist, **kwargs)
    else:
        raise ValueError("Unknown similarity method %s" % similarity_method)
    return S


def laplacian(S, normalization=None):
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

    return L


def spectral_clustering(S, k, normalization=None, generalized_eigenproblem=False, norm_rows=False):

    L = laplacian(S, normalization=normalization)

    if generalized_eigenproblem:
        D = np.diag(S.sum(axis=1))
        w, v = scipy.linalg.eig(L, D)
    else:
        w, v = np.linalg.eig(L)

    order = w.argsort()
    U = v[:, order[:k]]  # first k eigenvalues

    if norm_rows:
        row_sums = np.linalg.norm(U, axis=1)
        U = U / row_sums[:, np.newaxis]

    kmeans = KMeans(n_clusters=k)
    A = kmeans.fit_predict(U)
    return A


def recursive_spectral_clustering(S, k, depth=2,
                                  normalization=None, generalized_eigenproblem=False, norm_rows=False):

    L = laplacian(S, normalization=normalization)

    if generalized_eigenproblem:
        D = np.diag(S.sum(axis=1))
        w, v = scipy.linalg.eig(L, D)
    else:
        w, v = np.linalg.eig(L)

    order = w.argsort()
    U = v[:, order[:k]]  # first k eigenvalues

    if norm_rows:
        row_sums = np.linalg.norm(U, axis=1)
        U = U / row_sums[:, np.newaxis]

    if depth > 0:
        _S = similarity_matrix(U, dist=Distance.cosine_similarity, similarity_method=Similarity.fully_connected)
        return recursive_spectral_clustering(_S, k, depth=depth - 1,
                                             normalization=normalization,
                                             generalized_eigenproblem=generalized_eigenproblem,
                                             norm_rows=norm_rows)
    else:
        return KMeans(n_clusters=k).fit_predict(U)


def spectral_visualization(S, k, z_true, normalization=None):
    L = laplacian(S, normalization=normalization)

    w, v = np.linalg.eig(L)
    order = w.argsort()
    U = v[:, order[:k]]  # first k eigenvalues

    plt.figure()
    u = PCA(n_components=2).fit_transform(U)
    plt.scatter(u[:, 0], u[:, 1], c=z_true)
    plt.title("PCA of Spectral Decomposition")
    plt.show()

    plt.figure()
    plt.plot(sorted(w))
    plt.title("Eigenvalues")
    plt.show()

    plt.figure()
    for i in range(k):
        plt.plot(sorted(v[:, order[i]]))
    plt.legend(["Eigenvector %d" % i for i in range(k)])
    plt.show()


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


def evaluate(z_true, A, name):
    print("%s:" % name)
    complete_score = completeness_score(z_true, A)
    homog_score = homogeneity_score(z_true, A)
    print("Completeness score: %s" % complete_score)
    print("Homogeneity score: %s" % homog_score)


def main():
    m = 1500  # number of points
    n = 2  # Number of dimensions
    k = 2  # Number of latent clusters

    np.random.seed(3)
    X, z_true = sample.sample_coils(m, n, k)
    show_points(X, z_true, title="True")

    S = k_nearest_neighbor_graph(X, k=20)

    gmm = GaussianMixture(n_components=k)
    gmm.fit(X)
    A_gmm = gmm.predict(X)
    evaluate(z_true, A_gmm, name="Guassian Mixtures EM")

    A_kmeans = KMeans(n_clusters=k).fit_predict(X)
    evaluate(z_true, A_kmeans, "KMeans")

    spec = SpectralClustering(n_clusters=k, affinity='precomputed')
    A_spec = spec.fit_predict(S)
    evaluate(z_true, A_spec, "sklearn.cluster.SpectralClustering")

    # Unnormalized spectral clustering
    # A = spectral_clustering(S, k)

    # Normalized spectral clustering according to Shi and Malik (2000)
    # A = spectral_clustering(S, k, normalization=LaplacianNorm.symmetric, generalized_eigenproblem=True)

    # Normalized spectral clustering according to Ng, Jordan, and Weiss (2002)
    A = spectral_clustering(S, k, normalization=LaplacianNorm.symmetric, norm_rows=True)

    spectral_visualization(S, k, z_true, normalization=LaplacianNorm.symmetric)

    show_points(X, A, title="Spectral Clustering")
    evaluate(z_true, A, "Normalized spectral clustering")

    A_rec = recursive_spectral_clustering(S, k, depth=2,
                                          normalization=LaplacianNorm.symmetric, norm_rows=True)

    evaluate(z_true, A_rec, "Recursive spectral clustering")
    show_points(X, A_rec, title="Recursive Spectral Clustering")


if __name__ == "__main__":
    main()
