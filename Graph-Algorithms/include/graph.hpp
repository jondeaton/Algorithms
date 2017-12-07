/**
 * File: graph.hpp
 * ---------------
 * Presents the interface of a directed, weighed graph
 */

#ifndef _GRAPH_HPP_INCLUDED
#define _GRAPH_HPP_INCLUDED

#include <node.hpp>
#include <vector>

template <class T>
class Graph {
public:
  Graph() = default;
  explicit Graph(int N);

  void add_node();
  void add_node(T data);
  void add_node(Node<T>& node);
  Node<T>& operator[](int i);

  Node<T>* store;
  std::size_t size = 0;
  typedef Node<T>* iterator;
  typedef const Node<T>* const_iterator;

  iterator begin() { return &store[0]; }
  const_iterator begin() const { return &store[0]; }
  iterator end() { return &store[size]; }
  const_iterator end() const { return &store[size]; }

private:
  std::vector<Node<T>> nodes;
};

#include <graph.tpp>
#endif // _GRAPH_HPP_INCLUDED
