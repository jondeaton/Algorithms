/*
 * File: BinaryNode.h
 * ------------------
 * The interface of a binary node class useful in implementing binary tree
 * data structures
 *
 * A useful typedef is the following
 *
 * template <class T>
 * using Node = std::shared_ptr<BinaryNode<T>>;
 *
 * Then you can use Node<T> which would be the type of say node.left
 */

#ifndef _BinaryNode_H
#define _BinaryNode_H

#include <memory>

enum Color { red, black };

template <class T>
class BinaryNode {

public:
  T value;
  size_t height;
  Color color;

  std::shared_ptr<BinaryNode<T>> left;
  std::shared_ptr<BinaryNode<T>> right;

  explicit BinaryNode(const T& value, Color color=red);

  /**
   * Public method: setColor
   * -----------------------
   * Sets the color of the node while updating it's height
   * @param newColor: The new color to set the node
   */
  void setColor(Color newColor);
};

template <class T>
BinaryNode<T>::BinaryNode(const T& value, Color color) : value(value), height(1), color(red),
                                                         left(nullptr), right(nullptr) {
  setColor(color);
}

template <class T>
void BinaryNode<T>::setColor(Color newColor) {
  if (color == newColor) return; // nothing to do
  if (newColor == red) height--; // demotion
  else height++; // promotion
  color = newColor;
}

#endif
