/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include "path.hpp"
#include "graph-search.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

// Static function declaration
template <class T, class WT>
static void make_graph(Graph<T, WT> &graph);

void test_dijkstra() {
  ifstream in("/Users/jonpdeaton/GitHub/Algorithms/Graph-Algorithms/dinkstra-test");
  cin.rdbuf(in.rdbuf());

  size_t num_nodes;
  cin >> num_nodes;
  Graph<int, int> graph(num_nodes);
  make_graph(graph);

  size_t start, end;
  cin >> start;
  cin >> end;

  GraphSearcher<int, int> searcher;
  auto path = searcher.find_path(graph, start, end);
  cout << path << endl;
}

/**
 * Functor: DistanceToEnd
 * ----------------------
 * Defines a functor that can calculate the distance from
 * @tparam T:
 */
template <class T, class CMP>
class DistanceToEnd {
  DistanceToEnd(T distances[], size_t i): distances(distances) { };

  T operator()(int i) {
    if (set[i]) return distances[i];
    set[i] = true;
    return distances[i] = cmp();
  }

private:
  CMP cmp;
  bool set[];
  T distances[];
};

void test_Astar() {
  ifstream in("/Users/jonpdeaton/GitHub/Algorithms/Graph-Algorithms/Astar-test");
  cin.rdbuf(in.rdbuf());

  GraphSearcher<int, int, float> searcher;

}

int main() {
  clock_t begin = clock();
  test_dijkstra();
  test_Astar();
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Elapsed time: " << elapsed_secs << endl;
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