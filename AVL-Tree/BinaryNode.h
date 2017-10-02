/*
 * File: BinaryNode.h
 * ------------------
 *
 */

#ifndef _binady_node_H
#define _binary_node_h

template <class T>
class BinaryNode<T> {

public:
  T value;

  explicit BinaryNode();
  explicit BinaryNode(T& value);

  void insertLeft(T& value);
  void insertRight(T& value);

  T& left();
  T& right();

private:
  std::shared_ptr<BinaryNode<T>> left;
  std::shared_ptr<BinaryNode<T>> right;
};

#include "BinaryNode.tpp"
#endif