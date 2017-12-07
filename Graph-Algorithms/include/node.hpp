/**
 * File: node.hpp
 * --------------
 * Presents the interface of a graph in a node
 */

#ifndef _NODE_HPP_INCLUDED
#define _NODE_HPP_INCLUDED

#include <edge.hpp>
#include <vector>
#include <iostream>

template <class T>
class Node {
public:
  Node() = default;
  explicit Node(T data);

  T data;

  void add_edge();
  void add_edge(const Edge &edge);
  void add_edge(int weight, int to);
  void remove_edge(int i);
  size_t num_edges() { return connections.size(); }
  Edge& operator[](int i);

  Edge* store = nullptr;
  std::size_t it_size;
  typedef Edge* iterator;
  typedef const Edge* const_iterator;

  iterator begin() { return &store[0]; }
  const_iterator begin() const { return &store[0]; }
  iterator end() { return &store[it_size]; }
  const_iterator end() const { return &store[it_size]; }

private:
  std::vector<Edge> connections;
  template <class U>
  friend std::ostream& operator<<(std::ostream &os, const Node<U> &node);
  template <class U>
  friend std::istream& operator>>(std::istream &is, Node<U> &node);
};

template <class T>
inline std::ostream& operator<<(std::ostream &os, const Node<T> &node) {
  return os << node.data;
}

template <class T>
inline std::istream& operator>>(std::istream &is, Node<T> &node) {
  return node.data >> is;
}

#include <node.tpp>
#endif // _NODE_HPP_INCLUDED
