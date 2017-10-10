/*
 * File: RedBlackTree.h
 * --------------------
 * Presents the interface of a Red Black Tree data structure.
 */

#ifndef _RedBlackTree_H
#define _RedBlackTree_H


#include "BinaryNode.h"
#include <memory>

template <class T>
using Node = std::shared_ptr<BinaryNode<T>>;

enum Side {left, right, none};

template <class T>
class RedBlackTree {

public:
  explicit RedBlackTree();

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
  Node<T> search(const T& element);

  /**
   * Public Method: clear
   * --------------------
   * Clears the tree of all contents
   */
  void clear() { root = nullptr; }


  /**
   * Public Method: empty
   * --------------------
   * Check if the tree is empty
   * @return: True if the heap is empty, false otherwise
   */
  bool empty() { return root == nullptr; }

  /**
   * Public Method: height
   * ---------------------
   * Returns the height of the tree, defined as 
   * the number of edges on the longest path
   * from the root to any leaf node.
   * @return: The height of the tree
   */
  size_t height() { return empty() ? 0 : root->height; }

  /**
   * Public Method: verify
   * ---------------------
   * Verifies that the heap is properly formed and not corrupted
   * @return: True if the heap is well-formed, false otherwise
   */
  bool verify();

private:
  Node<T> root;

  Node<T> insertAtBlack(Node<T> node, const T& element);
  Node<T> insertAtRed(Node<T> node, Node<T> parent, Side side, const T& value);
  Node<T> remove(Node<T> node, const T& element);
  Node<T> search(const Node<T> node, const T& element);
  bool contains(const Node<T> node, const T& element);

  void recolor(Node<T> node);
  Node<T> balance(Node<T> node, Side side0, Side side1);

  Node<T> fixDoubleBlack(Node<T> node, Side side);
  Node<T> rotateDoubleBlack(Node<T> node, Side side0, Side side1);

  Node<T> rotate(Node<T> node, Side direction);
  Node<T> leftRotate(Node<T> node);
  Node<T> rightRotate(Node<T> node);

  void setColor(Node<T> node, Color color); 
  void updateHeight(Node<T> node);
  Node<T> next(const Node<T> node);
  Node<T> childOf(const Node<T> node, Side side);

  Side otherSide(Side side);
  Side redChild(const Node<T> node);
  size_t getHeight(const Node<T> node);

  bool verify(const Node<T> node);
};

#include "RedBlackTree.tpp"
#endif
