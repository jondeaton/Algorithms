/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include "path.hpp"
#include "dijkstra.hpp"

#include <iostream>
using namespace std;

// Static function declaration
template <class T>
static void make_graph(Graph<T> &graph);
static int get_next_int();

int main() {
  int num_nodes = get_next_int(); // Number of nodes
  Graph<int> graph(num_nodes);
  make_graph(graph);

  int start, end;
  cin >> start;
  cin >> end;

  Dijkstra<int> d;
  auto path = d.run(graph, start, end);
  cout << path << endl;
}

template <class T>
static void make_graph(Graph<T> &graph) {
  int num_edges = get_next_int();

  int from, to, weight;
  for (int i = 0; i < num_edges; i++) {
    cin >> from;
    cin >> to;
    cin >> weight;
    graph[from].add_edge(weight, to);
  }
}

static int get_next_int() {
  char* line = nullptr;
  size_t size;
  getline(&line, &size, stdin);
  return (int) strtol(line, NULL, 0);
}