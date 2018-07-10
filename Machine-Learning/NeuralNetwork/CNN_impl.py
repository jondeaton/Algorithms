#!/usr/bin/env python
"""
File: CNN_impl
Date: 5/7/18 
Author: Jon Deaton (jdeaton@stanford.edu)

Adapted from Andrew Ng's Deep Learning Course on Coursera
"""

import numpy as np

def zero_pad(X, pad):
    """
    Pad with zeros all images of the dataset X. The padding is applied to the height and width of an image,
    as illustrated in Figure 1.

    :param X: python numpy array of shape (m, n_H, n_W, n_C) representing a batch of m images
    :param pad: integer, amount of padding around each image on vertical and horizontal dimensions
    :return: padded image of shape (m, n_H + 2*pad, n_W + 2*pad, n_C)
    """
    return np.pad(X, ((0, 0), (pad, pad), (pad, pad), (0, 0)), 'constant', constant_values=(0, 0))


def conv_single_step(a_slice_prev, W, b):
    """
    Apply one filter defined by parameters W on a single slice (a_slice_prev) of the output activation
    of the previous layer.

    :param a_slice_prev: slice of input data of shape (f, f, n_C_prev)
    :param W: Weight parameters contained in a window - matrix of shape (f, f, n_C_prev)
    :param b: Bias parameters contained in a window - matrix of shape (1, 1, 1)
    :return: a scalar value, result of convolving the sliding window (W, b) on a slice x of the input data
    """
    s = a_slice_prev * W
    Z = np.sum(s.reshape(np.prod(s.shape)))
    Z = Z + float(b)
    return Z


def conv_forward(A_prev, W, b, hparameters):
    """
    Implements the forward propagation for a convolution function

    :param A_prev: output activations of the previous layer, numpy array of shape (m, n_H_prev, n_W_prev, n_C_prev)
    :param W: Weights, numpy array of shape (f, f, n_C_prev, n_C)
    :param b: Biases, numpy array of shape (1, 1, 1, n_C)
    :param hparameters: python dictionary containing "stride" and "pad"
    :return: Tuple containing
        - conv output, numpy array of shape (m, n_H, n_W, n_C)
        - cache of values needed for the conv_backward() function
    """
    (m, n_H_prev, n_W_prev, n_C_prev) = A_prev.shape
    (f, f, n_C_prev, n_C) = W.shape

    stride = hparameters["stride"]
    pad = hparameters["pad"]

    n_H = int((n_H_prev + 2 * pad - f) / 2) + 1
    n_W = int((n_W_prev + 2 * pad - f) / 2) + 1

    Z = np.zeros((m, n_H, n_W, n_C))
    A_prev_pad = zero_pad(A_prev, pad)

    for i in range(m):
        for h in range(n_H):
            for w in range(n_W):
                for c in range(n_C):
                    v_start = stride * h
                    v_end = v_start + f
                    h_start = stride * w
                    h_end = h_start + f
                    a_slice_prev = A_prev_pad[i, v_start:v_end, h_start:h_end]
                    Z[i, h, w, c] = conv_single_step(a_slice_prev, W[:, :, :, c], b[:, :, :, c])

    assert (Z.shape == (m, n_H, n_W, n_C))
    cache = (A_prev, W, b, hparameters)
    return Z, cache


def pool_forward(A_prev, hparameters, mode="max"):
    """
    Implements the forward pass of the pooling layer

    :param A_prev: Input data, numpy array of shape (m, n_H_prev, n_W_prev, n_C_prev)
    :param hparameters: python dictionary containing "f" and "stride"
    :param mode: the pooling mode you would like to use, defined as a string ("max" or "average")
    :return: Tuple containing:
                output of the pool layer, a numpy array of shape (m, n_H, n_W, n_C)
                cache used in the backward pass of the pooling layer, contains the input and hparameters
    """
    (m, n_H_prev, n_W_prev, n_C_prev) = A_prev.shape
    f = hparameters["f"]
    stride = hparameters["stride"]

    n_H = int(1 + (n_H_prev - f) / stride)
    n_W = int(1 + (n_W_prev - f) / stride)
    n_C = n_C_prev

    A = np.zeros((m, n_H, n_W, n_C))

    for i in range(m):
        for h in range(n_H):
            for w in range(n_W):
                for c in range(n_C):
                    v_start = stride * h
                    v_end = v_start + f
                    h_start = stride * w
                    h_end = h_start + f
                    a_prev_slice = A_prev[i, v_start:v_end, h_start:h_end]
                    if mode == "max":
                        A[i, h, w, c] = np.max(a_prev_slice[:, :, c])
                    elif mode == "average":
                        A[i, h, w, c] = np.mean(a_prev_slice[:, :, c])
                    else:
                        raise ValueError(mode)

    cache = (A_prev, hparameters)
    assert (A.shape == (m, n_H, n_W, n_C))
    return A, cache

