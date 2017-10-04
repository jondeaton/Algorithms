/**
 * File: AVL-tree.h
 * ----------------
 * Interface of a self-balancing Binary Search Tree (BST).
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
    bool contains(const T& element);
    BSTNode search(const T& element);

private:
    BSTNode root;

    BSTNode insert(BSTNode node, const T& element);
    BSTNode remove(BSTNode node, const T& element);
    BSTNode search(const BSTNode node, const T& element);
    BSTNode contains(const BSTNode node, const T& element);

    BSTNode balance(BSTNode node);
    BSTNode leftRotate(BSTNode node);
    BSTNode rightRotate(BSTNode node);
    void updateHeight(BSTNode node);
    int getNetBalance(BSTNode node);

    BSTNode next(BSTNode node);

};

#include "AVL-Tree.cpp"
#endif