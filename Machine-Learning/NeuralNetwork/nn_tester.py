#!/usr/bin/env python
"""
File: nn_tester
Date: 4/15/18 
Author: Jon Deaton (jdeaton@stanford.edu)
"""

import os

import numpy as np
from numpy.linalg import norm
from sklearn.decomposition import PCA
from sklearn import linear_model
import matplotlib.pyplot as plt

from activations import ActivationFunction
from NeuralNetwork import NeuralNetwork
from NeuralNetwork import HyperParameters
from NeuralNetwork import OptimizationStrategy


def lasso(X, y):
    lassocv = linear_model.LassoCV()
    lassocv.fit(X.T, np.squeeze(y))
    idx = np.abs(lassocv.coef_) > 20
    return X[idx, :], y


def load_virus_data(virus_file="~/Datasets/viruses/virus.kmer", bacteria_file="~/Datasets/viruses/bacteria.kmer"):

    def extract_X(file):
        content = np.loadtxt(file, delimiter=',', dtype=str)
        counts = content[:, 1:].astype(float)
        for i in range(counts.shape[0]):
            counts[i, :] /= np.sum(counts[i, :])
        return counts.T

    virus_file = os.path.expanduser(virus_file)
    bacteria_file = os.path.expanduser(bacteria_file)

    X_vir = extract_X(virus_file)
    X_bac = extract_X(bacteria_file)
    X = np.concatenate((X_vir, X_bac), axis=1)

    num_vir = X_vir.shape[1]
    num_bac = X_bac.shape[1]
    Y_vir = np.ones((1, num_vir))
    Y_bac = np.zeros((1, num_bac))

    Y = np.concatenate((Y_vir, Y_bac), axis=1).astype(int)

    return X, Y



def load_simple_data():

    X1 = np.random.randn(2, 500)
    X2 = np.random.randn(2, 500) + 4

    X = np.concatenate((X1, X2), axis=1)

    Y1 = np.zeros((1, X1.shape[1]), dtype=int)
    Y2 = np.ones((1, X2.shape[1]), dtype=int)
    y = np.concatenate((Y1, Y2), axis=1)

    return X, y


def load_ring_data():

    X1 = np.random.randn(2, 500)
    X1 = X1[:, norm(X1, axis=0) < 2]
    X1 = X1[:, norm(X1, axis=0) > 1]

    X2 = np.random.randn(2, 500)
    X2 = X2[:, norm(X2, axis=0) > 2]
    X2 = X2[:, norm(X2, axis=0) < 3]

    X = np.concatenate((X1, X2), axis=1)

    y1 = np.zeros((1, X1.shape[1]), dtype=int)
    y2 = np.ones((1, X2.shape[1]), dtype=int)
    y = np.concatenate((y1, y2), axis=1)
    return X, y


def show_data(X, Y):
    if X.shape[0] > 2:
        v = PCA(n_components=2).fit_transform(X.T)
        # v = TSNE(n_components=2).fit_transform(X.T)
    else:
        v = X.T

    plt.figure()
    plt.scatter(v[:, 0], v[:, 1], c=np.squeeze(Y))
    plt.title("Principal Component Analysis")
    plt.xlabel("PC 1")
    plt.ylabel("PC 2")
    plt.show()


def plot_decision_boundary(model, X, y):
    # Set min and max values and give it some padding
    x_min, x_max = X[0, :].min() - 1, X[0, :].max() + 1
    y_min, y_max = X[1, :].min() - 1, X[1, :].max() + 1
    h = 0.01
    # Generate a grid of points with distance h between them
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    # Predict the function value for the whole grid
    Z = model(np.c_[xx.ravel(), yy.ravel()].T) > 0.5
    Z = Z.reshape(xx.shape)
    # Plot the contour and training examples
    plt.contourf(xx, yy, Z)
    plt.ylabel('x2')
    plt.xlabel('x1')
    plt.scatter(X[0, :], X[1, :], c=np.squeeze(y))


def sample(X, y, n_samples):
    idx = np.random.randint(X.shape[1], size=n_samples)
    return X[:, idx], y[:, idx]


def main():
    X, y = load_virus_data()
    # X, y = load_simple_data()
    # X, y = load_ring_data()

    # X, y = sample(X, y, 500)
    # X = PCA(n_components=10).fit_transform(X.T).T

    X, y = lasso(X, y)
    # show_data(X, y)

    print("Features: %d" % X.shape[0])
    nx = X.shape[0]
    ny = y.shape[0]
    dims = [nx, 50, 8, ny]

    layers = [ActivationFunction.relu,
              ActivationFunction.relu,
              ActivationFunction.sigmoid]

    model = NeuralNetwork(dims, layers)

    # Hyper-Parameters
    params = HyperParameters()
    params.regularize =True
    params.mini_batch_size = 512
    params.num_epochs = 20000
    params.dropout = False

    params.optimization_strategy = OptimizationStrategy.adam
    params.initial_learning_rate = 0.001

    costs = model.train(X, y, hyper_params=params)

    plot_decision_boundary(model.predict, X, y)

    plt.figure()
    plt.plot(costs)
    plt.xlabel("iteration")
    plt.ylabel("Cost")
    plt.title("Training cost")
    plt.show()

    predictions = model.predict(X)
    accuracy = model.compute_accuracy(predictions, y)
    print("Accuracy: %f" % accuracy)


if __name__ == "__main__":
    main()
