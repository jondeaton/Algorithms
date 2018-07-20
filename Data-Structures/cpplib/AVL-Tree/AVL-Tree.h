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


  /**
   * Public Method: empty
   * --------------------
   * Check if the tree is empty
   * @return: True if the heap is empty, false otherwise
   */
  bool empty() { return root == nullptr; }

  /**
   * Public Method: height
   * ---------------------
   * Returns the height of the tree, defined as 
   * the number of edges on the longest path
   * from the root to any leaf node.
   * @return: The height of the tree
   */
  size_t height() { return empty() ? 0 : root->height; }

  /**
   * Public Method: verify
   * ---------------------
   * Verifies that the heap is properly formed and not corrupted
   * @return: True if the heap is well-formed, false otherwise
   */
  bool verify();

private:
  Node<T> root;

  Node<T> insert(Node<T> node, const T& element);
  Node<T> remove(Node<T> node, const T& element);
  Node<T> search(const Node<T> node, const T& element);
  bool contains(const Node<T> node, const T& element);

  Node<T> balance(Node<T> node);
  Node<T> leftRotate(Node<T> node);
  Node<T> rightRotate(Node<T> node);
  void updateHeight(Node<T> node);
  int getNetBalance(const Node<T> node);
  Node<T> next(const Node<T> node);
  size_t getHeight(const Node<T> node);
  bool verify(const Node<T> node);
};

#include "AVL-Tree.tpp"

#endif
