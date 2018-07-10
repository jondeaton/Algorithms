#!/usr/bin/env python
"""
File: tf_example
Date: 4/24/18 
Author: Jon Deaton (jdeaton@stanford.edu)

Adapted from Andrew Ng's deep learning Coursera course
"""

import numpy as np
import tensorflow as tf


def main():
    coefficients = np.array([[1.], [-10.], [25.]])

    w = tf.Variable(0, dtype=tf.float32)
    x = tf.placeholder(tf.float32, [3, 1])

    cost = x[0][0] * w ** 2 + x[1][0] * w + x[2][0]

    # cost = w ** - 10 * w + 25

    train = tf.train.GradientDescentOptimizer(0.01).minimize(cost)

    init = tf.global_variables_initializer()
    with tf.Session() as sess:
        sess.run(init)
        result = sess.run(w, feed_dict={x: coefficients})
        print(result)

        for i in range(1000):
            sess.run(train, feed_dict={x: coefficients})
        result = sess.run(w)
        print (result)


if __name__ == "__main__":
    main()
