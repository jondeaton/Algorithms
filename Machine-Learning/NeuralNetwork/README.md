# Deep Neural Network

Here I demonstrate the implementation of a deep, fully connected neural network using only the linear algebra/matrix operation primitives provided by Numpy (i.e. no automatic gradients). 
This implementation provides the ability to have arbitrary neural network structure, by specifying the number a sizes of each layer as well as the activation function used in each layer.
In addition, I have implemented standard Gradient Descent optimization and ADAM optimizers, as well as optionally allowing for Dropout to be used at any layer.
Finally, this Neural Network implementation uses He initialization, optional L2 regularization and mini-batch gradient descent.


The implementation of the Neural Network is in `NeuralNetwork.py`

Where noted, some of the code in this repository originates from Andrew Ng's Deep Learning course on Coursera.
The implementation of the Deep Neural Network was NOT taken from the Coursera course, but implemented in isolation.


