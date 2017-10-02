/*
 * File: AVL-tree.h
 * ----------------
 * Interface of a self-balancing Binary Search tree
 */

#ifndef _avl_tree_h
#define _avl_tree_h

#include "BinaryNode.h"

template <class T>
class AVLTree<T> {
public:

  explicit AVLTree();

  void insert(T& element);

private:
  BinaryNode<T> root;
};

#include "AVL-Tree.tpp"
#endif