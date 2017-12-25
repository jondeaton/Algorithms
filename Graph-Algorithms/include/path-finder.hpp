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

#include <set>
#include <algorithm>
#include <limits>
#include <vector>

template <bool, class if_true, class if_false>
struct if_{};

template <class if_true, class if_false>
struct if_<true, if_true, if_false> {
  typedef if_true value;
};

template <class if_true, class if_false>
struct if_<false, if_true, if_false> {
  typedef if_false value;
};

class Empty {};

template <class Graph, class Heuristic>
class PathFinderDijkstra {
public:
  explicit PathFinderDijkstra(const Heuristic& heuristic) : distance_to_end(heuristic) {}
  typename Graph::weight_type* priorities;
  Heuristic distance_to_end;
};

/**
 * @class  PathFinder
 * @brief  Provides functionality for path finding in directed, weighted graphs
 * @tparam T  Type of data stored in the nodes of the graph
 * @tparam WT The type of data stored in the weights of the graphs
 * @tparam Heuristic The type of function used to get a heuristic
 */
template <class Graph, class Heuristic=void>
class PathFinder : public if_<std::is_void<Heuristic>::value, Empty, PathFinderDijkstra<Graph, Heuristic>>::value {
public:
  typedef typename Graph::data_type T;
  typedef typename Graph::weight_type WT;
  static constexpr bool use_Astar = !std::is_void<Heuristic>::value;

  explicit PathFinder(size_t data_size=0) : data_size(data_size) {
    prevs = (size_t*) malloc(data_size * sizeof(size_t));
    distances = (WT*) malloc(data_size * sizeof(WT));
    if constexpr (use_Astar) this->priorities = (WT*) malloc(data_size * sizeof(WT));
  }

  template <bool enable=use_Astar>
  explicit PathFinder(const typename std::enable_if<enable, Heuristic>::type& heuristic)
    : PathFinderDijkstra<Graph, Heuristic>(heuristic) {
    prevs = (size_t*) malloc(data_size * sizeof(size_t));
    distances = (WT*) malloc(data_size * sizeof(WT));
    if constexpr (use_Astar) this->priorities = (WT*) malloc(data_size * sizeof(WT));
  }

  template <bool enable=use_Astar>
  void set_heuristic(const typename std::enable_if<enable, Heuristic>::type& heuristic) {
    this->distance_to_end = heuristic;
  }

  Path<size_t> find_path(Graph graph, size_t source, size_t sink);
  Path<size_t> make_path(size_t start, size_t end);
  ~PathFinder();

private:
  size_t data_size;
  size_t* prevs;
  WT* distances;
  void setup_arrays(size_t new_size);
  void initialize_arrays() {

  }
};

#include <path-finder.cpp>
#endif // _PATH_FINDER_HPP_INCLUDED
