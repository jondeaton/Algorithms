/**
 * File: graph.tpp
 * ---------------
 *
 */

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