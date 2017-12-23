/**
 * @file path-finder.cpp
 * @brief Presents the implementation of the graph searching class
 */

#ifndef _PATH_FINDER_CPP_INCLUDED
#define _PATH_FINDER_CPP_INCLUDED

#include <path-finder.hpp>

template <class T>
static inline void set_all(T* arr, T val, size_t count);

/**
 * @fn CompareDistances
 * @brief Functor for comparing distances without re-computing
 * @tparam WT
 */
template <class WT>
struct ComparePriorities {
public:
  ComparePriorities() : priorities(nullptr) {}
  explicit ComparePriorities(const WT* dists) : priorities(dists) {}
  bool operator()(size_t a, size_t b) {
    return priorities[a] > priorities[b];
  }
public:
  const WT* priorities;
};

template <class T, class WT, class Heuristic>
PathFinder<T, WT, Heuristic>::PathFinder() : data_size(0) {
  prevs = (size_t*) malloc(data_size * sizeof(size_t));
  distances = (WT*) malloc(data_size * sizeof(WT));
  if constexpr (use_Astar) this->priorities = (WT*) malloc(data_size * sizeof(WT));
}

template <class T, class WT, class Heuristic>
Path<size_t> PathFinder<T, WT, Heuristic>::find_path(Graph<T, WT> graph, size_t source, size_t sink) {

  setup_arrays(graph.size());
  distances[source] = 0;

  ComparePriorities<WT> cmp;
  if constexpr (use_Astar) cmp.priorities = this->priorities;
  else cmp.priorities = distances; // in dijkstra's path distance *is* priority

  priority_queue<size_t, true, ComparePriorities<WT>> queue(cmp);
  queue.push(source);

  while (!queue.empty()) {
    size_t v = *queue.top();
    if (v == sink) return make_path(source, sink);
    queue.pop();
    for (Edge<WT> edge : graph[v]) {
      WT alt_distance = distances[v] + edge.weight;

      if (alt_distance < distances[edge.to]) { // found a faster way to get to this node
        prevs[edge.to] = v; // Mark the new predecessor

        distances[edge.to] = alt_distance;
        if constexpr (use_Astar) this->priorities[edge.to] = alt_distance + this->distance_to_end(edge.to);

        if (queue.contains(v)) queue.update_priority(v); // Update node priority to new value
        else queue.push(edge.to); // Add node for the first time
      }
    }
  }
  Path<size_t> path;
  return path; // return empty path - no path found
}

template <class T, class WT, class Heuristic>
Path<size_t> PathFinder<T, WT, Heuristic>::make_path(size_t start, size_t end) {
    Path<size_t> path;
  for (size_t v = end; v != start; v = prevs[v]) path.nodes.push_back(v);
  path.nodes.push_back(start);
  std::reverse(path.nodes.begin(), path.nodes.end());
  return path;
}

template <class T, class WT, class Heuristic>
void PathFinder<T, WT, Heuristic>::setup_arrays(size_t new_size)  {
  if (new_size <= data_size) return;
  data_size = new_size;
  prevs = (size_t*) realloc(prevs, data_size * sizeof(size_t));
  distances = (WT*) realloc(distances, data_size * sizeof(WT));
  if constexpr (use_Astar) this->priorities = (WT*) realloc(this->priorities);
  set_all(distances, std::numeric_limits<WT>::max(), data_size);
}

template <class T, class WT, class Heuristic>
PathFinder<T, WT, Heuristic>::~PathFinder() {
  free(prevs);
  free(distances);
  if constexpr (use_Astar) free(this->priorities);
}

/**
 * @brief  Sets all of elements of an array to a specified value
 *
 * @tparam T  The type of element stored in the array
 * @param arr  The array to set the values of
 * @param val  The value to set all elements in the array to
 * @param count  The number of elements to set in the array
 */
template <class T>
static inline void set_all(T arr[], T val, size_t count) {
  for (size_t i = 0; i < count; i++) arr[i] = val;
}

#endif // _PATH_FINDER_CPP_INCLUDED