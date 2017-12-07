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

  size_t size() { return nodes.size(); }
  void add_node();
  void add_node(T data);
  void add_node(Node<T>& node);
  Node<T>& operator[](int i);

  Node<T>* store;
  std::size_t it_size;
  typedef Node<T>* iterator;
  typedef const Node<T>* const_iterator;

  iterator begin() { return &store[0]; }
  const_iterator begin() const { return &store[0]; }
  iterator end() { return &store[it_size]; }
  const_iterator end() const { return &store[it_size]; }

private:
  std::vector<Node<T>> nodes;
};

#include <graph.tpp>
#endif // _GRAPH_HPP_INCLUDED
