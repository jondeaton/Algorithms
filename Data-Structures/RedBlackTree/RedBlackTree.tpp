/*
 * File: RedBlackTree.tpp
 * ----------------------
 * Presents the template implementation of the RedBlackTree data structure.
 *
 * Red-Black Tree is a self-balancing Binary Search Tree (BST) where every node follows following rules.
 * 1) Every node has a color either red or black.
 */

#include "BinaryNode.h"
#include "RedBlackTree.h"
#include <memory>

template <class T>
using Node = std::shared_ptr<BinaryNode<T>>;

// Constructor
template <class T>
RedBlackTree<T>::RedBlackTree() { }

template <class T>
void RedBlackTree<T>::insert(const T& element) {
  root = insertAtBlack(root, element);
  if (root->color == red) {
    root->color = black;
    updateHeight(root);
  }
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
 * Private Method: insertAtBlack
 * ----------------------
 * Inserts an element into a node of a binary search tree, and balances the tree
 * @tparam T: The type of element contained in the node of the BST
 * @param node: Root node to insert element into. If nullptr, a new node will be created and returned
 * @param value: The value to store in the BST
 * @return: The (possibly new) root of the BST after insertion and balancing
 */
template <class T>
Node<T> RedBlackTree<T>::insertAtBlack(Node<T> node, const T& value) {
  if (node == nullptr) return std::shared_ptr<BinaryNode<T>>(new BinaryNode<T>(value, red));
  if (value == node->value) return node; // no duplicates

  if (value < node->value) { // regular insertion on the left
      if (node->left == nullptr || node->left->color == black)
        node->left = insertAtBlack(node->left, value); // black insertion
      else
        return insertAtRed(node->left, node, left, value); // red insertion

    } else { // regular insertion on the right
      if (node->right == nullptr || node->right->color == black)
        node->right = insertAtBlack(node->right, value);
      else
        return insertAtRed(node->right, node, right, value);
    }
  
  return node;
}

template <class T>
Node<T> RedBlackTree<T>::insertAtRed(Node<T> node, Node<T> parent, Side side, const T& value) {
  if (value < node->value) {
    node->left = insertAtBlack(node->left, value); // child must be black
    if (node->color == red) { // Insertion may have caused the black child to turn red
      if (parent->right != nullptr && parent->right->color == red)
        recolor(parent); // recolor if uncle is red
      else
        return rotate(parent, side, left); // rotate if uncle is black

    }
  }

  // Mirror image of the above logic
  if (value > node->value) {
    node->right = insertAtBlack(node->right, value);
    if (node->color == red) {
      if (parent->left != nullptr && parent->left->color == red)
        recolor(parent);
      else
        return rotate(parent, side, right);
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
  (void) value;

  return nullptr;
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

/**
 *
 * @tparam T
 * @param node
 */
template <class T>
void RedBlackTree<T>::recolor(Node<T> node) {
  if (node == nullptr) return;
  node->color = red;
  if (node->left  != nullptr) node->left->color = black;
  if (node->right != nullptr) node->right->color = black;
}

/**
 *
 * @tparam T
 * @param node
 * @param side0
 * @param side1
 * @return
 */
template <class T>
Node<T> RedBlackTree<T>::rotate(Node<T> node, Side side0, Side side1) {
  if (side0 == left) {
    if (side1 == right) node->left = leftRotate(node->left);
    node->color = red;
    node->left->color = black;
    return rightRotate(node);
  } else {
    if (side1 == left) node->right = rightRotate(node->right);
    node->color = red;
    node->right->color = black;
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
  updateHeight(node);
  updateHeight(root);
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
  updateHeight(node);
  updateHeight(root);
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
 * Private Method: getHeight
 * -------------------------
 * Re-calculates the black height of a node. This is defined to be the number of black nodes
 * between the current node (inclusive) and the leaf node. This will be set to the black height
 * of the node's children, if it is red, and one more than this value, if it is black.
 * The height of a null node is defined to be one.
 * @return: The black height of a node.
 */
template <class T>
size_t RedBlackTree<T>::getHeight(const Node<T> node) {
  if (node == nullptr) return 1;
  if (node->left == nullptr) return 1;
  return node->left->height + (node->color == black ? 1 : 0);
}

/**
 * Private Method: verify
 * ----------------------
 * Verifies that a node is properly formed by checking to make sure that:
 *  - It's value is strictly less than and greater than it's left child and right child's values, respectively.
 *  - If it is red, then it does not have a red child (red violation)
 *  - The black heights of its two children are equal (black height violation)
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

  // Check for incorrect heights
  if (node->height != getHeight(node))
    return false;

  // Check for height violation
  if (getHeight(node->left) != getHeight(node->right))
    return false;

  return verify(node->left) && verify(node->right);
}