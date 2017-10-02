/*
 * File: BinaryNode.h
 * ------------------
 *
 */

#ifndef _binary_node_h
#define _binary_node_h

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
BinaryNode<T>::BinaryNode() : leftNode(nullptr), rightNode(nullptr) { }

template <class T>
BinaryNode<T>::BinaryNode(const T& value) : value(value), leftNode(nullptr), rightNode(nullptr) { }

#endif