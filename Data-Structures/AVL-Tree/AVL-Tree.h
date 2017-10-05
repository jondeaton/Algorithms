/**
 * File: AVL-tree.h
 * ----------------
 * Interface of a self-balancing Binary Search Tree (BST)
 *
 * This data structure guarantees O(log(N)) insertion, deletion, and search times
 * through self balancing in the insertion and deletion algorithms.
 */

#ifndef _AVLTree_H
#define _AVLTree_H

#include "BinaryNode.h"
#include <memory>

template <class T>
using BSTNode = std::shared_ptr<BinaryNode<T>>;

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
  BSTNode<T> search(const T& element);

private:
  BSTNode<T> root;

  BSTNode<T> insert(BSTNode<T> node, const T& element);
  BSTNode<T> remove(BSTNode<T> node, const T& element);
  BSTNode<T> search(const BSTNode<T> node, const T& element);
  BSTNode<T> contains(const BSTNode<T> node, const T& element);

  BSTNode<T> balance(BSTNode<T> node);
  BSTNode<T> leftRotate(BSTNode<T> node);
  BSTNode<T> rightRotate(BSTNode<T> node);
  void updateHeight(BSTNode<T> node);
  int getNetBalance(BSTNode<T> node);

  BSTNode<T> next(BSTNode<T> node);
};

#include "AVL-Tree.cpp"

#endif