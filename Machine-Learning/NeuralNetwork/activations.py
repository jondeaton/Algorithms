#!/usr/bin/env python
"""
File: activations
Date: 4/14/18 
Author: Jon Deaton (jdeaton@stanford.edu)
"""

import numpy as np
from enum import Enum


class ActivationFunction(Enum):
    relu = 0
    sigmoid = 1
    tanh = 2


def sigmoid(x):
    """
    Compute the sigmoid of x

    :param x:  A scalar or numpy array of any size.
    :return: sigmoid(x)
    """
    return 1 / (1 + np.exp(-x))


def relu(x):
    """
    Rectified Linear Unit

    :param x: A scalar or numpy array of any size.
    :return: relu(x)
    """
    return x * (x > 0)

def tanh(x):
    """
    Hyperbolic Tangent

    :param x: A scalar or numpy array of any size.
    :return: tanh(x)
    """
    return np.tanh(x)


def relu_backward(dA, Z):
    """
    Backward propagation for a single RELU unit.

    :param dA: post-activation gradient, of any shape
    :param Z: pre-activation value computed in forward prop
    :return: Gradient of the cost with respect to Z
    """
    dZ = np.array(dA, copy=True)
    dZ[Z <= 0] = 0
    return dZ


def sigmoid_backward(dA, Z):
    """
    Backward propagation for a single SIGMOID unit.

    :param dA: post-activation gradient, of any shape
    :param Z: pre-activation value computed in forward prop
    :return: Gradient of the cost with respect to Z
    """
    s = sigmoid(Z)
    dZ = dA * s * (1 - s)
    return dZ


def tanh_backward(dA, Z):
    """
    Backward propagation of a single TANH unit.

    :param dA: post-activation gradient, of any shape
    :param Z: pre-activation value computed in forward prop
    :return: Gradient of the cost with respect to Z
    """
    s = tanh(Z)
    dZ = dA * (1 - s ** 2)
    return dZ