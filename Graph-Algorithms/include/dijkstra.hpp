/**
 * File: dijkstra.hpp
 * ------------------
 *
 */

#ifndef _DIJKSTRA_HPP_INCLUDED
#define _DIJKSTRA_HPP_INCLUDED

#include "graph.hpp"
#include "node.hpp"
#include "path.hpp"

#include <queue>
#include <set>
#include <algorithm>
#include <limits>
#include <vector>

class CompareDistances {
public:
  explicit CompareDistances(const int* dists) : dists(dists) {}
  bool operator()(int a, int b) {
    return dists[a] < dists[b];
  }
private:
  const int* dists;
};

template <class T>
class Dijkstra {

public:

  Dijkstra() : size(0) {
    prevs = (int*) malloc(size);
    dists = (int*) malloc(size);
  }

  Path<T> run(Graph<T> graph, int source, int sink) {
    setup_arrays(graph.size());
    dists[source] = 0;

    std::priority_queue<int, std::vector<int>, CompareDistances> queue(CompareDistances(dists));
    for (int i = 0; i < graph.size(); i++) queue.push(i);

    while (!queue.empty()) {
      int v = queue.top();
      queue.pop();
      for (Edge edge : graph[v]) {
        int alt = dists[edge.to] + edge.weight;
        if (alt < dists[edge.to]) {
          dists[edge.to] = alt;
          prevs[edge.to] = v;
        }
      }
    }
    return make_path(source, sink);
  }

  Path<T> make_path(int start, int end) {
    Path<int> path;
    for (int v = end; v != start; v = prevs[v]) path.nodes.push_back(v);
    std::reverse(path.nodes.begin(), path.nodes.end());
    return path;
  }

  ~Dijkstra(){
    free(prevs);
    free(dists);
  }

private:
  size_t size;
  int* prevs;
  int* dists;

  void setup_arrays(size_t new_size) {
    if (new_size <= size) return;
    size = new_size;
    prevs = (int*) realloc(prevs, size);
    dists = (int*) realloc(dists, size);
    memset(dists, std::numeric_limits<int>::max(), size);
    memset(prevs, -1, size);
  }
};

#endif // _DIJKSTRA_HPP_INCLUDED
