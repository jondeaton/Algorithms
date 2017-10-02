/*
 * File: BinaryNode.tpp
 * --------------------
 */


template <class T>
BinaryNode<T>::BinaryNode() {}

template <class T>
BinaryNode<T>::BinaryNode(T& value) : value(value) {}

template <class T>
void BinaryNode<T>::insertLeft(T& value) {
  BinaryNode<T>* node = new BinaryNode<T>(value);
  left = std::shared_ptr(node);
}

template <class T>
void BinaryNode<T>::insertRight(T& value) {
  BinaryNode<T>* node = new BinaryNode<T>(value);
  right = std::shared_ptr(node);
}