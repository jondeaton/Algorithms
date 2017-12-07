/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include <iostream>
using namespace std;

// Static function declaration
static int get_next_int();

//template <class T>
//class Path {
//public:
//  std::vector<int> nodes;
//private:
//  friend std::ostream& operator<<(std::ostream& os, const Path& path);
//  friend std::istream& operator>>(std::istream& is, Path& path);
//};
//
//template <class T>
//std::ostream& operator<<(std::ostream &os, const Path<T>& path) {
//  for (int node : path.nodes) os << node << ", ";
//  return os;
//}
//
//template <class T>
//std::istream& operator>>(std::istream& is, Path<T>& path) {
//  for (int node : path.nodes) is >> node;
//  return is;
//}
//
//template <class T>
//void make_graph(Graph<T> &graph) {
//  (void) graph;
//}
//
//template <class T>
//Path<T> dijkstra(Graph<T> graph, int source, int sink) {
//  (void) source;
//  (void) sink;
//
//  for (const Node<T> & node : graph) cout << "Node: " << node << endl;
//
//  Path<T> path;
//  return path;
//}

int main() {
  int N = get_next_int();
  int start = get_next_int();
  int end  = get_next_int();

  Graph<int> graph(N);
  cout << graph[0] << endl;
//  make_graph(graph);

  // Path<int> path = dijkstra(graph, start, end);
//  cout << path << endl;
}

static int get_next_int() {
  char* line = nullptr;
  size_t size;
  getline(&line, &size, stdin);
  return (int) strtol(line, NULL, 0);
}