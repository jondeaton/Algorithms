/**
 * File: graph.hpp
 * ---------------
 * Presents the interface of a directed, weighed graph
 */

#ifndef _GRAPH_HPP_INCLUDED
#define _GRAPH_HPP_INCLUDED

#include <vector>
#include <memory>

template <class T>
class Graph {
public:
    Graph(int N);
    void add_node();
private:
    std::vector<std::shared_ptr<Node<T>>> nodes;
};

template <class T>
class Node {
public:
    T data;
    std::vector<Vertex> connections;
};

class Vertex {
public:
    int weight;
    int to;
    Vertex(int weight, int from, int to) : weight(weight), from(from), to(to) {}
};

template <class T>
Graph::Graph(int N) {
    for (int i = 0; i < N; i++) add_node();
}

template <class T>
void Graph::add_node() {
    std::shared_ptr<Node<T>> node = make_shared();
    nodes.push_back(node);
}

#endif _GRAPH_HPP_INCLUDED
