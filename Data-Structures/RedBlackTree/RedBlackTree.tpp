/*
 * File: RedBlackTree.tpp
 * ----------------------
 * Presents the template implementation of the RedBlackTree data structure.
 *
 * Red-Black Tree is a self-balancing Binary Search Tree (BST) where every node follows following rules.
 * 1) Every node has a color either red or black.
 */

#include "BinaryNode.h"
#include <memory>

template <class T>
using Node = std::shared_ptr<BinaryNode<T>>;

enum Side {left, right};

// Constructor
template <class T>
RedBlackTree<T>::RedBlackTree() { }

template <class T>
void RedBlackTree<T>::insert(const T& element) {
  root = insert(root, element);
  root->color = black;
}

template <class T>
void RedBlackTree<T>::remove(const T& element) {
  root = remove(root, element);
}

template <class T>
bool RedBlackTree<T>::contains(const T& element) {
  return contains(root, element);
}

template <class T>
Node<T> RedBlackTree<T>::search(const T& element) {
  return search(root, element);
}

template <class T>
bool RedBlackTree<T>::verify() {
  return verify(root);
}

// Private members

/**
 * Private Method: insert
 * ----------------------
 * Inserts an element into a node of a binary search tree, and balances the tree
 * @tparam T: The type of element contained in the node of the BST
 * @param node: Root node to insert element into. If nullptr, a new node will be created and returned
 * @param value: The value to store in the BST
 * @return: The (possibly new) root of the BST after insertion and balancing
 */
template <class T>
Node<T> RedBlackTree<T>::insert(Node<T> node, const T& value) {
  if (node == nullptr) return std::shared_ptr<BinaryNode<T>>(new BinaryNode<T>(value, color=red));
  if (value == node->value) return node; // no duplicates

  if (value < node->value) { // regular insertion on the left
      if (node->left == nullptr || node->left->color == black)
        node->left = insert(node->left, value); // black insertion
      else
        node->left = insert(node->left, node, Left, value); // red insertion

    } else { // regular insertion on the right
      if (node->right == nullptr || node->right->color == black)
        node->right = isnert(node->right, value);
      else
        node->left = insert(node->right, node, Right, value);
    }
  
  return node;
}

template <class T>
Node<T> insert(Node<T> node, Node<T> parent, Side side, value) {
  
  if (value < node->value) {
    node->left = insert(node->left, value); // child must be black
    if (node->color == red) { // Insertion may have caused the black child to turn red
      if (parent->right->color == red)
        recolor(node, parent, side); // recolor if uncle is red
      else
        return rotate(parent, side, Left); // rotate if uncle is black
    }
  }

  // Mirror image of the above logic
  if (value > node->value) {
    node->right = insert(node->right, value);
    if (node->color == red) {
      if (parent->left->color == red)
        recolor(node, parent, side);
      else
        return rotate(parent, side, Right);
    }
  }

  return node;
}

/**
 * Private Method: remove
 * ----------------------
 * Removes a specified element from a binary search tree (BST) and re-balances the tree
 * @tparam T: Type of the element stored in the BST
 * @param node: The node to remove the value from
 * @param value: The value to remove the the node
 * @return: A new node after the removal and re-balancing
 */
template <class T>
Node<T> RedBlackTree<T>::remove(Node<T> node, const T& value) {
  if (node == nullptr) return nullptr;

  // TODO

}

/**
 * Private Method: contains
 * ------------------------
 * Determines if the binary search tree contains a certain element.
 * @param node: The root node to search below
 * @param element: The element to search for
 * @return: True if the element is contained in the tree, false otherwise
 */
template <class T>
bool RedBlackTree<T>::contains(const Node<T> node, const T& element) {
  if (node == nullptr) return false;
  if (node->value == element) return true;
  if (element < node->value) return contains(node->left, element);
  if (element > node->value) return contains(node->right, element);
  return false;
}

/**
 * Private Method: search
 * ----------------------
 * If the element is stored in the binary search tree, then the node containing the element
 * will be returned, otherwise a null pointer will be returned.
 * @tparam T: Type of the elements stored in the BST
 * @param node: Root node to search for the element in.
 * @param element: The element to search for
 * @return: A pointer to a node containing an equivalent element
 */
template <class T>
Node<T> RedBlackTree<T>::search(Node<T> node, const T& element) {
  if (node == nullptr) return nullptr;
  if (node->value == element) return node;
  if (element < node->value) return search(node->left, element);
  if (element > node->value) return search(node->right, element);
  return nullptr;
}

void RedBlackTree<T>::recolor(Node<T> node) {
  if (node == nullptr) return;
  node->color = red;
  if (node->left  != nullptr) node->left->color = black;
  if (node->right != nullptr) node->right->color = black;
}

Node<T> RedBlackTree<T>::rotate(Node<T> node, Side side0, Side side1) {
  if (side0 == left) {
    if (side1 == right) node->left = leftRotate(node->left);
    node->color = red;
    node->left->color = black;
    return rightRotate(node);
  }

  if (side0 == right) {
    if (side1 == left) node->right = rightRotate(node->right);
    node->color = red;
    node->left->color = black;
    return leftRotate(node);
  }
}


/**
 * Private Method: leftRotate
 * --------------------------
 * Rotates the tree counter-clockwise, returning the new root
 * @tparam T: Type of element stored in the tree node
 * @param node: Pointer to a binary search tree node to rotate
 * @return: The new root after having been rotated
 */
template <class T>
Node<T> RedBlackTree<T>::leftRotate(Node<T> node) {
  if (node->right == nullptr) return node; // Nothing to rotate onto
  auto root = node->right;
  node->right = node->right->left;
  root->left = node;
  return root;
}

/**
 * Private Method: rightRotate
 * --------------------------
 * Rotates the tree clockwise, returning the new root
 * @tparam T: Type of element stored in the tree node
 * @param node: Pointer to a binary search tree node to rotate
 * @return: The new root after having been rotated
 */
template <class T>
Node<T> RedBlackTree<T>::rightRotate(Node<T> node) {
  if (node->left == nullptr) return node; // Nothing to rotate onto
  auto root = node->left;
  node->left = root->right;
  root->right = node;
  return root;
}

/**
 * Private Method: next
 * --------------------
 * Returns the (ordered) next node in the binary search tree.
 * @param node: The root node to get the next node from
 * @return: The next node in order
 */
template <class T>
Node<T> RedBlackTree<T>::next(const Node<T> node) {
  if (node == nullptr) return nullptr;
  if (node->left == nullptr) return node;
  else return next(node->left);
}

/**
 * Private Method: updateHeight
 * ----------------------------
 * Updates the height of a node to be the one plus the
 * maximum of the heights of it's two children. Nodes with
 * no children have a height of zero.
 * @param node: A node to update the height on
 */
template <class T>
void RedBlackTree<T>::updateHeight(Node<T> node) {
  node->height = getHeight(node);
}

/**
 * Private Method: getNetBalance
 * -----------------------------
 * Gets the difference in heights of the right and left children of a node
 * @param node: Node to get the net balance at
 * @return: Difference between height of right and left children
 */
template <class T>
int RedBlackTree<T>::getNetBalance(const Node<T> node) {
  if (node == nullptr) return 0;
  if (node->height == 0) return 0;
  if (node->right == nullptr) return -(1 + node->left->height);
  if (node->left == nullptr) return 1 + node->right->height;
  return node->right->height - node->left->height;
}

/**
 * Private Method: getHeight
 * -------------------------
 * Re-calculates the height of a node to be one more than
 * the maximum of the heights of it's two children. The height
 * of a node with no children is defined to be zero. Note that
 * this method will *not* change the height value stored in the node.
 * @param node: The node to calculate the height of
 * @return: The height of the node.
 */
template <class T>
size_t RedBlackTree<T>::getHeight(const Node<T> node) {
  if (node == nullptr) return 0;
  int lh = node->left == nullptr ? -1 : node->left->height;
  int rh = node->right == nullptr ? -1 : node->right->height;
  return 1 + (lh > rh ? lh : rh);
}

/**
 * Private Method: verify
 * ----------------------
 * Verifies that a node is properly formed by checking to make sure that:
 *  - It's height is equal to one more than the maximum of the heights of it's children
 *  - It's value is strictly less than and greater than it's left child and right child's values, respectively.
 *  - The heights of it's two children differ by no more than one
 *  - Both child nodes are properly formed
 * @param node: The node to check for corruption
 * @return: True if the node (and all of it's children) are well formed, false otherwise
 */
template <class T>
bool RedBlackTree<T>::verify(const Node<T> node) {
  if (node == nullptr) return true;

  // Check for correct value placements
  if (node->left != nullptr && node->left->value >= node->value)
    return false;

  if (node->right != nullptr && node->right->value <= node->value)
    return false;

  // Check for red violation
  if (node->color == red) {
    if (node->left != nullptr && node->left->color == red)
      return false;
    if (node->right != nullptr && node->right->color == red)
      return false;
  }

  // todo: check for black height violation
  return verify(node->left) && verify(node->right);
}