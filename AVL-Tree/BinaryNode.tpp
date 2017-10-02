/*
 * File: BinaryNode.tpp
 * --------------------
 */

template <class T>
BinaryNode<T>::BinaryNode() {}

template <class T>
BinaryNode<T>::BinaryNode(const T& value) : value(value) {}

template <class T>
void BinaryNode<T>::insert(const T& value) {
  if (value < this->value) this->left.insertLeft(value);
}

template <class T>
void BinaryNode<T>::insertLeft(const T& value) {
  BinaryNode<T>* node = new BinaryNode<T>(value);
  leftNode = std::shared_ptr<BinaryNode<T>>(node);
}

template <class T>
void BinaryNode<T>::insertRight(const T& value) {
  BinaryNode<T>* node = new BinaryNode<T>(value);
  rightNode = std::shared_ptr<BinaryNode<T>>(node);
}