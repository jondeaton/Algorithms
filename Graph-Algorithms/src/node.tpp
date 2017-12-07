
#include <node.hpp>

template <class T, class WT>
Node<T, WT>::Node(T data) : data(data) {}

template <class T, class WT>
void Node<T, WT>::add_edge() {
  Edge<WT> vertex;
  add_edge(vertex);
}

template <class T, class WT>
void Node<T, WT>::add_edge(int weight, size_t to) {
  Edge<WT> vertex(weight, to);
  add_edge(vertex);
}

template <class T, class WT>
void Node<T, WT>::add_edge(const Edge<WT> &edge) {
  edges.push_back(edge);
}

template <class T, class WT>
void Node<T, WT>::remove_edge(int i) {
  edges.erase(edges.begin() + i);
}

template <class T, class WT>
Edge<WT>& Node<T, WT>::operator[](int i) {
  return edges[i];
}