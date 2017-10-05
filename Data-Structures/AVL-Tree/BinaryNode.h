/*
 * File: BinaryNode.h
 * ------------------
 * The interface of a binary node class useful in implementing binary tree
 * data structures
 *
 * A useful typedef is the following
 *
 * template <class T>
 * using BSTNode = std::shared_ptr<BinaryNode<T>>;
 *
 * Then you can use BSTNode<T> which would be the type of say node.left
 */

#ifndef _BinaryNode_H
#define _BinaryNode_H

#include <memory>

template <class T>
class BinaryNode {

public:
  T value;
  size_t height;

  explicit BinaryNode();
  explicit BinaryNode(const T& value);

  std::shared_ptr<BinaryNode<T>> left;
  std::shared_ptr<BinaryNode<T>> right;
};

template <class T>
BinaryNode<T>::BinaryNode() : left(nullptr), right(nullptr) { }

template <class T>
BinaryNode<T>::BinaryNode(const T& value) : value(value), left(nullptr), right(nullptr) { }

#endif