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

template <class T, class WT>
class Node {
public:
  Node() = default;
  explicit Node(T data);

  T data;

  void add_edge();
  void add_edge(const Edge<WT> &edge);
  void add_edge(int weight, size_t to);
  void remove_edge(int i);
  size_t num_edges() { return edges.size(); }
  Edge<WT>& operator[](int i);

  typedef typename std::vector<Edge<WT>>::iterator iterator;
  typedef typename std::vector<Edge<WT>>::const_iterator const_iterator;

  iterator begin() { return edges.begin(); }
  const_iterator begin() const { return edges.begin(); }
  iterator end() { return edges.end(); }
  const_iterator end() const { return edges.end(); }

private:
  std::vector<Edge<WT>> edges;

  template <class U, class WU>
  friend std::ostream& operator<<(std::ostream &os, const Node<U, WU> &node);
  template <class U, class WU>
  friend std::istream& operator>>(std::istream &is, Node<U, WU> &node);
};

template <class T, class WT>
inline std::ostream& operator<<(std::ostream &os, const Node<T, WT> &node) {
  return os << node.data;
}

template <class T, class WT>
inline std::istream& operator>>(std::istream &is, Node<T, WT> &node) {
  return node.data >> is;
}

#include <node.tpp>
#endif // _NODE_HPP_INCLUDED
