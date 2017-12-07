/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include "path.hpp"
#include "dijkstra.hpp"
#include <iostream>
#include <fstream>
using namespace std;

// Static function declaration
template <class T, class WT>
static void make_graph(Graph<T, WT> &graph);

int main() {
  ifstream in("/Users/jonpdeaton/GitHub/Algorithms/Graph-Algorithms/test");
  cin.rdbuf(in.rdbuf());

  size_t num_nodes;
  cin >> num_nodes;
  Graph<int, int> graph(num_nodes);
  make_graph(graph);

  size_t start, end;
  cin >> start;
  cin >> end;

  Dijkstra<int, int> d;
  auto path = d.run(graph, start, end);
  cout << path << endl;
}

template <class T, class WT>
static void make_graph(Graph<T, WT> &graph) {
  size_t num_edges;
  cin >> num_edges;

  size_t from, to;
  WT weight;

  for (size_t i = 0; i < num_edges; i++) {
    cin >> from;
    cin >> to;
    cin >> weight;
    graph[from].add_edge(weight, to);
  }
}