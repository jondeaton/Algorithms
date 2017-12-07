/**
 * File: graph.tpp
 * ---------------
 *
 */

#include <graph.hpp>

template <class T>
Graph<T>::Graph(int N) {
  for (int i = 0; i < N; i++) add_node();
}

template <class T>
void Graph<T>::add_node() {
  Node<T> node;
  add_node(node);
}

template <class T>
void Graph<T>::add_node(T data) {
  Node<T> node(data);
  add_node(node);
}

template <class T>
void Graph<T>::add_node(Node<T> &node) {
  nodes.push_back(node);
}

template <class T>
Node<T>& Graph<T>::operator[](int i) {
  return nodes[i];
}
