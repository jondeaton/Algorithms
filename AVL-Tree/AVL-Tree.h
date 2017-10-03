/**
 * File: AVL-tree.h
 * ----------------
 * Interface of a self-balancing Binary Search tree.
 */

#ifndef _avl_tree_h
#define _avl_tree_h

#include "BinaryNode.h"
#include <memory>

template <class T>
typedef std::shared_ptr<BinaryNode<T>> BSTNode;

template <class T>
class AVLTree {

public:
    explicit AVLTree();

    void insert(const T& element);
    void remove(const T& element);
    BSTNode search(const T& element);

private:
    BSTNode root;

    BSTNode leftRotate(BSTNode node);
    BSTNode rightRotate(BSTNode node);

    BSTNode insert(BSTNode node, const T& element);
    BSTNode remove(BSTNode node, const T& element);
    BSTNode search(const BSTNode node, const T& element);
};

#include "AVL-Tree.cpp"
#endif