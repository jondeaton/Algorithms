/**
 * File: graph.tpp
 * ---------------
 *
 */

#ifndef _GRAPH_CPP_INCLUDED
#define _GRAPH_CPP_INCLUDED

#include <graph.hpp>

template <class T, class WT>
Graph<T, WT>::Graph(size_t N) {
  for (size_t i = 0; i < N; i++) add_node();
}

template <class T, class WT>
void Graph<T, WT>::add_node() {
  Node<T, WT> node;
  add_node(node);
}

template <class T, class WT>
void Graph<T, WT>::add_node(T data) {
  Node<T, WT> node(data);
  add_node(node);
}

template <class T, class WT>
void Graph<T, WT>::add_node(Node<T, WT> &node) {
  nodes.push_back(node);
}

template <class T, class WT>
void Graph<T, WT>::add_edge(size_t from, size_t to, WT weight) {
  nodes[from].add_edge(weight, to);
}

template <class T, class WT>
Node<T, WT>& Graph<T, WT>::operator[](int i) {
  return nodes[i];
}

template <class T, class WT>
std::istream& operator>>(std::istream& is, Graph<T, WT>& graph) {
  size_t num_nodes, num_edges;
  is >> num_nodes;
  is >> num_edges;
  for (size_t i = 0; i < num_nodes; ++i) graph.add_node();

  size_t from, to;
  WT weight;

  for (size_t i = 0; i < num_edges; i++) {
    is >> from;
    is >> to;
    is >> weight;
    graph[from].add_edge(weight, to);
  }
  return is;
}

#endif // _GRAPH_HPP_INCLUDED
