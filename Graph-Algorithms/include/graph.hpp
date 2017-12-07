/**
 * File: graph.hpp
 * ---------------
 * Presents the interface of a directed, weighed graph
 */

#ifndef _GRAPH_HPP_INCLUDED
#define _GRAPH_HPP_INCLUDED

#include <node.hpp>
#include <vector>

template <class T, class WT>
class Graph {
public:
  Graph() = default;
  explicit Graph(size_t N);

  size_t size() { return nodes.size(); }
  void add_node();
  void add_node(T data);
  void add_node(Node<T, WT>& node);
  Node<T, WT>& operator[](int i);

  typedef typename std::vector<Node<T, WT>>::iterator iterator;
  typedef typename std::vector<Node<T, WT>>::const_iterator const_iterator;

  iterator begin() { return nodes.begin(); }
  const_iterator begin() const { return nodes.begin(); }
  iterator end() { return nodes.end(); }
  const_iterator end() const { return nodes.end(); }

private:
  std::vector<Node<T, WT>> nodes;
};

#include <graph.tpp>
#endif // _GRAPH_HPP_INCLUDED
