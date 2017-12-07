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

template <class T>
static inline void set_all(T* arr, T val, size_t count);

struct CompareDistances {
public:
  explicit CompareDistances(const int* dists) : dists(dists) {}
  bool operator()(size_t a, size_t b) {
    return dists[a] > dists[b];
  }
private:
  const int* dists;
};

template <class T, class WT>
class Dijkstra {

public:

  Dijkstra() : size(0) {
    prevs = (size_t*) malloc(size);
    dists = (int*) malloc(size);
  }

  Path<size_t> run(Graph<T, WT> graph, size_t source, size_t sink) {

    setup_arrays(graph.size());
    dists[source] = 0;

    CompareDistances cmp(dists);
    std::priority_queue<size_t, std::vector<size_t>, CompareDistances> queue(cmp);
    queue.push(source);

    while (!queue.empty()) {
      size_t v = queue.top();
      if (v == sink) return make_path(source, sink);
      queue.pop();
      for (Edge<WT> edge : graph[v]) {
        int alt = dists[v] + edge.weight;
        if (alt < dists[edge.to]) {
          dists[edge.to] = alt;
          prevs[edge.to] = v;
          queue.push(edge.to);
        }
      }
    }
    Path<size_t> path;
    return path;
  }

  Path<size_t> make_path(size_t start, size_t end) {
    Path<size_t> path;
    for (size_t v = end; v != start; v = prevs[v]) path.nodes.push_back(v);
    path.nodes.push_back(start);
    std::reverse(path.nodes.begin(), path.nodes.end());
    return path;
  }

  ~Dijkstra(){
    free(prevs);
    free(dists);
  }

private:
  size_t size;
  size_t* prevs;
  int* dists;

  void setup_arrays(size_t new_size) {
    if (new_size <= size) return;
    size = new_size;
    prevs = (size_t*) realloc(prevs, size);
    dists = (int*) realloc(dists, size);
    set_all(dists, std::numeric_limits<int>::max(), size);
  }
};

template <class T>
static inline void set_all(T* arr, T val, size_t count) {
  for (size_t i = 0; i < count; i++) arr[i] = val;
}

#endif // _DIJKSTRA_HPP_INCLUDED
