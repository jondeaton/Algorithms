/**
 * File: node.hpp
 * --------------
 * Presents the interface of a graph in a node
 */

#ifndef _NODE_HPP_INCLUDED
#define _NODE_HPP_INCLUDED

#include <vertex.hpp>
#include <vector>

template <class T>
class Node {
public:
  Node() = default;
  explicit Node(T data);

  T data;

  void add_vertex();
  void add_vertex(const Vertex& vertex);
  void add_vertex(int weight, int to);
  void remove_vertex(int i);
  Vertex& operator[](int i);
private:
  std::vector<Vertex> connections;
  friend std::ostream& operator<<(std::ostream &os, const Node<T> &node);
  friend std::istream& operator>>(std::istream &is, Node<T> &node);
};

template <class T>
std::ostream& operator<<(std::ostream &os, const Node<T> &node) {
  return os << node.data;
}

template <class T>
std::istream& operator>>(std::istream &is, Node<T> &node) {
  return node.data >> is;
}

#include <node.tpp>
#endif // _NODE_HPP_INCLUDED
