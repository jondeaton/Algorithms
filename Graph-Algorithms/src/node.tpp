
#include <node.hpp>

template <class T>
Node<T>::Node(T data) : data(data) {}

template <class T>
void Node<T>::add_edge() {
  Edge vertex;
  add_edge(vertex);
}

template <class T>
void Node<T>::add_edge(int weight, int to) {
  Edge vertex(weight, to);
  add_edge(vertex);
}

template <class T>
void Node<T>::add_edge(const Edge &edge) {
  connections.push_back(edge);
}

template <class T>
void Node<T>::remove_edge(int i) {
  connections.erase(connections.begin() + i);
}

template <class T>
Edge& Node<T>::operator[](int i) {
  return connections[i];
}