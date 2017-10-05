/**
 * File: AVL-tree.h
 * ----------------
 * Interface of a self-balancing Binary Search Tree (BST)
 *
 * This data structure guarantees O(log(N)) time complexity for insertion, deletion, and search
 * through self balancing in the insertion and deletion algorithms.
 */

#ifndef _AVLTree_H
#define _AVLTree_H

#include "BinaryNode.h"
#include <memory>

template <class T>
using Node = std::shared_ptr<BinaryNode<T>>;

template <class T>
class AVLTree {

public:
  explicit AVLTree();

  /**
   * Public Method: insert
   * ---------------------
   * Insert a copy of an element into the Binary tree
   * Time complexity: O(log(N))
   * @param element: The element to insert
   */
  void insert(const T& element);

  /**
   * Public Method: remove
   * ---------------------
   * Remove an element from the binary tree
   * Time complexity: O(log(N))
   * @param element: The element to remove
   */
  void remove(const T& element);

  /**
   * Public Method: contains
   * -----------------------
   * Check if the binary tree contains an element
   * Time complexity: O(log(N))
   * @param element: The element to search for
   * @return: True if the tree contains an element equivalent to the passed element
   */
  bool contains(const T& element);

  /**
   * Public Method: search
   * ---------------------
   * Retrieve a node from the tree containing a specified element
   * @param element: The element to search for
   * @return: A pointer to a node that contains an element equivalent to the specified node
   */
  Node<T> search(const T& element);

  /**
   * Public Method: clear
   * --------------------
   * Clears the tree of all contents
   */
  void clear() { root = nullptr; }

  // for testing...
  bool verify();

private:
  Node<T> root;

  bool verify(Node<T> node);

  Node<T> insert(Node<T> node, const T& element);
  Node<T> remove(Node<T> node, const T& element);
  Node<T> search(const Node<T> node, const T& element);
  bool contains(const Node<T> node, const T& element);

  Node<T> balance(Node<T> node);
  Node<T> leftRotate(Node<T> node);
  Node<T> rightRotate(Node<T> node);
  void updateHeight(Node<T> node);
  int getNetBalance(Node<T> node);
  Node<T> next(Node<T> node);
  size_t getHeight(Node<T> node);
};

#include "AVL-Tree.tpp"

#endif
