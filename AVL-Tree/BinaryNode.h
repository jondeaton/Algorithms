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

  explicit BinaryNode();
  explicit BinaryNode(const T& value);

  void insert(const T& value);
  void insertLeft(const T& value);
  void insertRight(const T& value);

  BinaryNode<T>& left();
  BinaryNode<T>& right();

private:
  std::shared_ptr<BinaryNode<T>> leftNode;
  std::shared_ptr<BinaryNode<T>> rightNode;
};

#include "BinaryNode.tpp"
#endif