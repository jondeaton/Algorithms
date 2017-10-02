/*
 * File: AVL-tree.h
 * ----------------
 * Interface of a self-balancing Binary Search tree.
 *
 * This tree is self-balancing in that
 *
 */

#ifndef _avl_tree_h
#define _avl_tree_h

#include "BinaryNode.h"

template <class T>
class AVLTree {

public:

    explicit AVLTree();

    void insert(const T& element);
    void remove(const T& element);
    void contains(const T& query);

private:
    std::shared_ptr<BinaryNode<T>> root;

    void leftRotate(const BinaryNode<T>& node);
    void rightRotate(const BinaryNode<T>& node);

};

#include "AVL-Tree.cpp"
#endif