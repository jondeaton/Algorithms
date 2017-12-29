/**
 * @file graph-search.hpp
 * @brief Presents the interface of graph searching class
 */

#ifndef _PATH_FINDER_HPP_INCLUDED
#define _PATH_FINDER_HPP_INCLUDED

#include "graph.hpp"
#include "node.hpp"
#include "path.hpp"
#include "priority-queue.hpp"
#include "type-traits.hpp"

#include <set>
#include <algorithm>
#include <limits>
#include <vector>


template <class T>
static inline void set_all(T* arr, T val, size_t count);

/**
 * @fn CompareDistances
 * @brief Functor for comparing priorities for a priority queue
 * @tparam priority: The type of the priorities that are compared
 */
template <class priority>
struct ComparePriorities : public std::binary_function<size_t, size_t, bool> {
public:
  ComparePriorities() : priorities(nullptr) {}
  explicit ComparePriorities(const priority* priorities) : priorities(priorities) {}
  bool operator()(size_t a, size_t b) {
    return priorities[a] < priorities[b];
  }
  priority* priorities;
};

template <class Graph, class Heuristic>
class AstarPathFinderBase {
public:
  AstarPathFinderBase() = default;
  explicit AstarPathFinderBase(const Heuristic& heuristic) : heuristic(heuristic), priorities(nullptr) {}
protected:
  Heuristic heuristic;
  double* priorities = nullptr;
};

/**
 * @class  PathFinder
 * @brief  Provides functionality for path finding in directed, weighted graphs
 * @tparam T  Type of data stored in the nodes of the graph
 * @tparam WT The type of data stored in the weights of the graphs
 * @tparam Heuristic The type of function used to get a heuristic
 */
template <class Graph, class Heuristic=void>
class PathFinder : public if_<std::is_void<Heuristic>::value, Empty, AstarPathFinderBase<Graph, Heuristic>>::value {
public:
  static constexpr bool use_Astar = !std::is_void<Heuristic>::value;

  typedef typename Graph::data_type value_type;
  typedef typename Graph::weight_type weight_type;
  typedef typename if_<use_Astar, double, weight_type>::value priority_type;

  explicit PathFinder(size_t data_size=0) : data_size(data_size) {
    prevs = (size_t*) malloc(data_size * sizeof(size_t));
    distances = (weight_type*) malloc(data_size * sizeof(weight_type));
    if constexpr (use_Astar) this->priorities = (weight_type*) malloc(data_size * sizeof(weight_type));
  }

  template <bool enable=use_Astar>
  explicit PathFinder(const typename std::enable_if<enable, Heuristic>::type& heuristic, size_t data_size=0)
    : AstarPathFinderBase<Graph, Heuristic>(heuristic) {
    this->data_size = data_size;
    prevs = (size_t*) malloc(data_size * sizeof(size_t));
    distances = (weight_type*) malloc(data_size * sizeof(weight_type));
    if constexpr (use_Astar)
      this->priorities = (priority_type*) malloc(data_size * sizeof(priority_type));
  }

  Path<size_t> find_path(Graph graph, size_t source, size_t sink) {

    setup_arrays(graph.size());
    distances[source] = 0;

    ComparePriorities<priority_type> cmp;
    if constexpr (use_Astar) cmp.priorities = this->priorities;
    else cmp.priorities = distances; // in dijkstra's path distance *is* priority

    priority_queue<size_t, true, ComparePriorities<priority_type>> queue(cmp);
    queue.push(source);

    while (!queue.empty()) {
      size_t v = queue.top();
      if (v == sink) return make_path(source, sink);
      queue.pop();
      for (Edge<weight_type> edge : graph[v]) {
        weight_type alt_distance = distances[v] + edge.weight;

        if (alt_distance < distances[edge.to]) { // found a faster way to get to this node
          if (queue.contains(edge.to)) queue.erase(edge.to); // need to remove in order to update it

          prevs[edge.to] = v; // Mark the new predecessor

          distances[edge.to] = alt_distance;
          if constexpr (use_Astar) this->priorities[edge.to] = alt_distance + this->heuristic(edge.to);

          queue.push(edge.to); // Queue the node for processing
        }
      }
    }

    Path<size_t> path;
    return path; // return empty path - no path found
  }

  Path<size_t> make_path(size_t start, size_t end) {
    Path<size_t> path;
    for (size_t v = end; v != start; v = prevs[v]) path.nodes.push_back(v);
    path.nodes.push_back(start);
    std::reverse(path.nodes.begin(), path.nodes.end());
    return path;
  }

  ~PathFinder() {
    free(prevs);
    free(distances);
    if constexpr (use_Astar) free(this->priorities);
  }

private:
  size_t data_size;
  size_t* prevs;
  weight_type* distances;
  void setup_arrays(size_t new_size) {
    if (new_size <= data_size) return;
    data_size = new_size;
    prevs = (size_t*) realloc(prevs, data_size * sizeof(size_t));
    distances = (weight_type*) realloc(distances, data_size * sizeof(weight_type));
    if constexpr (use_Astar)
      this->priorities = (priority_type*) realloc(this->priorities, data_size * sizeof(priority_type));
    set_all(distances, std::numeric_limits<weight_type>::max(), data_size);
  }
};

/**
 * @fn set_all
 * @brief  Sets all of elements of an array to a specified value
 * @tparam T  The type of element stored in the array
 * @param arr  The array to set the values of
 * @param val  The value to set all elements in the array to
 * @param count  The number of elements to set in the array
 */
template <class T>
static inline void set_all(T arr[], T val, size_t count) {
  for (size_t i = 0; i < count; i++) arr[i] = val;
}

#endif // _PATH_FINDER_HPP_INCLUDED
