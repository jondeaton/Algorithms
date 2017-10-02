/*
 * File: AVL-Tree.tpp
 * ----------------------
 * Presents the template implementation of the self-balancing Binary Search tree.
 */

template <class T>
AVLTree<T>::AVLTree() {}

template <class T>
void AVLTree<T>::insert(const T& element) {
  root = insert(root, elemnt);
}

template <class T>
void AVLTree<T>::rightRotate(const BinaryNode<T>& node) {

  BinaryNode<T>& x = node.left();
  BinaryNode<T>& T2 = x.right();

}

template <class T>
std::shared_ptr<BinaryNode<T>> AVLTree<T>::insert(BinaryNode<T>& node, const T& value) {

  if (value < node.value) node.left = insert(node.left, value);
  if (value > node.value) node.right = insert(node.right, value);
  else return node;// no duplicates

  updateHeight(node);


  int netBalance = getNetBalance(node);
  if (netBalance > 1) { // right is heavy
    int rightBalance = getNetBalance(*node.right);
    if (rightBalance < 0) node.right = rotateRight(node.right);
    return leftRotate(node);
  } else if ( netBalance < 1) { // left is heavy
    int leftBalance = getNetBalance(*node.left);
    if (leftBalance > 0) node.left = rotateLeft(node.left);
    return rightRotate(node);
  }

  return node;
}

void AVLTree<T>::updateHeight(BinaryNode<T>& node) {
  size_t lh = node.left->height;
  size_t rh = node.right->height;
  node.height = 1 + (lh > rh ? lh : rh);
}

void AVLTree<T>::getNetBalance(const BinaryNode<T>& node) {
  return node.right->height - node.left->height;
}