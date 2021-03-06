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

  typedef T data_type;
  typedef WT weight_type;

  size_t size() { return nodes.size(); }
  void add_node();
  void add_node(T data);
  void add_node(Node<T, WT>& node);
  void add_edge(size_t from, size_t to, WT weight);
  Node<T, WT>& operator[](int i);

  typedef typename std::vector<Node<T, WT>>::iterator iterator;
  typedef typename std::vector<Node<T, WT>>::const_iterator const_iterator;

  iterator begin() { return nodes.begin(); }
  const_iterator begin() const { return nodes.begin(); }
  iterator end() { return nodes.end(); }
  const_iterator end() const { return nodes.end(); }

  template <class U, class WU>
  friend std::istream& operator>>(std::istream& is, Graph<U, WU>& graph);

protected:
  std::vector<Node<T, WT>> nodes;
};

#include <graph.cpp>
#endif // _GRAPH_HPP_INCLUDED
