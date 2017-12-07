
#include <node.hpp>

template <class T>
Node<T>::Node(T data) : data(data) {}

template <class T>
void Node<T>::add_vertex() {
  Vertex vertex;
  add_vertex(vertex);
}

template <class T>
void Node<T>::add_vertex(int weight, int to) {
  Vertex vertex(weight, to);
  add_vertex(vertex);
}

template <class T>
void Node<T>::add_vertex(const Vertex &vertex) {
  connections.push_back(vertex);
}

template <class T>
void Node<T>::remove_vertex(int i) {
  connections.erase(connections.begin() + i);
}

template <class T>
Vertex& Node<T>::operator[](int i) {
  return connections[i];
}