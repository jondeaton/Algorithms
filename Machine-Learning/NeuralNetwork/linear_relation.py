#!/usr/bin/env python
"""
File: test
Date: 4/20/18 
Author: Jon Deaton (jdeaton@stanford.edu)
"""

import  numpy as np
import tensorflow as tf

def get_linear_relationship(x_shape, y_shape):
    W = np.random.random((y_shape[0], x_shape[0]))
    b = np.random.random(y_shape)
    x = np.random.random(x_shape)
    y = np.matmul(W, x) + b
    return x, y, W, b

def with_matricies():
    with tf.Session() as sess:
        x_shape = (3, 1)
        y_shape = (3, 1)
        _x, _y, _W, _b = get_linear_relationship(x_shape, y_shape)

        W = tf.Variable(np.random.random((y_shape[0], x_shape[0])), dtype=tf.float32)
        b = tf.Variable(np.random.random(y_shape), dtype=tf.float32)
        x = tf.placeholder(shape=x_shape, dtype=tf.float32)
        model = tf.matmul(W, x) + b

        y = tf.placeholder(shape=y_shape, dtype=tf.float32)
        loss = tf.reduce_sum(tf.square(model - y))

        optimizer = tf.train.GradientDescentOptimizer(0.001)
        train = optimizer.minimize(loss)

        # initialization
        init = tf.global_variables_initializer()
        sess.run(init)

        result = sess.run(loss, {x: _x, y: _y})
        print("Random: ", result)

        for i in range(1000):
            sess.run(train, {x: _x, y: _y})

        print("Actual W, b:\n", _W, _b)
        print("Learned:\n", sess.run([W, b]))

        trained_result = sess.run(loss, {x: _x, y: _y})
        print("Training loss: ", trained_result)


def main():
    pass


if __name__ == "__main__":
    main()
