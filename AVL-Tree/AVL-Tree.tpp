/*
 * File: AVL-Tree.tpp
 * ----------------------
 * Presents the template implementation of the self-balancing Binary Search tree.
 */

template <class T>
AVLTree<T>::AVLTree() {}

template <class T>
void AVLTree<T>::insert(const T& element) {
  root.insert(element);

}

template <class T>
void AVLTree<T>::rightRotate(const BinaryNode<T>& node) {

  BinaryNode<T>& x = node.left();
  BinaryNode<T>& T2 = x.right();

  x.right =

}


template <class T>
void BinaryNode<T>::insert(const T& value) {
  if (value == this->value) return; // no duplicates
  auto child = value < this->value ? leftNode : rightNode;
  if (child == nullptr) {
    auto childSetter = value < this->value ? &BinaryNode<T>::setLeft : &BinaryNode<T>::setRight;
    childSetter(child);
  } else child.insert(value);
}