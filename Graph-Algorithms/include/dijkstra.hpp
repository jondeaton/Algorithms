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

template <class WT>
struct CompareDistances {
public:
  explicit CompareDistances(const WT* dists) : distances(dists) {}
  bool operator()(size_t a, size_t b) {
    return distances[a] > distances[b];
  }
private:
  const WT* distances;
};

template <class T, class WT>
class Dijkstra {

public:

  Dijkstra() : data_size(0) {
    prevs = (size_t*) malloc(data_size);
    distances = (WT*) malloc(data_size);
  }

  Path<size_t> run(Graph<T, WT> graph, size_t source, size_t sink) {

    setup_arrays(graph.size());
    distances[source] = 0;

    CompareDistances<WT> cmp(distances);
    std::priority_queue<size_t, std::vector<size_t>, CompareDistances<WT>> queue(cmp);
    queue.push(source);

    while (!queue.empty()) {
      size_t v = queue.top();
      if (v == sink) return make_path(source, sink);
      queue.pop();
      for (Edge<WT> edge : graph[v]) {
        int alt = distances[v] + edge.weight;
        if (alt < distances[edge.to]) {
          distances[edge.to] = alt;
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
    free(distances);
  }

private:
  size_t data_size;
  size_t* prevs;
  WT* distances;

  void setup_arrays(size_t new_size) {
    if (new_size <= data_size) return;
    data_size = new_size;
    prevs = (size_t*) realloc(prevs, data_size);
    distances = (WT*) realloc(distances, data_size);
    set_all(distances, std::numeric_limits<WT>::max(), data_size);
  }
};

template <class T>
static inline void set_all(T* arr, T val, size_t count) {
  for (size_t i = 0; i < count; i++) arr[i] = val;
}

#endif // _DIJKSTRA_HPP_INCLUDED
