/**
 * File: graph-search.hpp
 * ----------------------
 * Presents the interface of graph searching class
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

template <class T, class WT, class Heuristic>
class PathFinderDijkstra {
public:
  WT* priorities;
  Heuristic distance_to_end;
};

/**
 * @class  PathFinder
 * @brief  Provides functionality for path finding in directed, weighted graphs
 * @tparam T  Type of data stored in the nodes of the graph
 * @tparam WT The type of data stored in the weights of the graphs
 * @tparam Heuristic The type of function used to get a heuristic
 */
template <class T, class WT, class Heuristic=void>
class PathFinder : if_<std::is_void<Heuristic>::value, Empty, PathFinderDijkstra<T, WT, Heuristic>>::value {
public:
  static constexpr bool use_Astar = !std::is_void<Heuristic>::value;

  PathFinder();

  template <bool enable=use_Astar>
  PathFinder(const typename std::enable_if<enable, Heuristic>& heuristic) : data_size(0) {
    prevs = (size_t*) malloc(data_size * sizeof(size_t));
    distances = (WT*) malloc(data_size * sizeof(WT));
    if (use_Astar) this->priorities = (WT*) malloc(data_size * sizeof(WT));
    this->distance_to_end = heuristic;
  }

  Path<size_t> find_path(Graph<T, WT> graph, size_t source, size_t sink);
  Path<size_t> make_path(size_t start, size_t end);
  ~PathFinder();

private:
  size_t data_size;
  size_t* prevs;
  WT* distances;
  void setup_arrays(size_t new_size);
};

#include <path-finder.cpp>
#endif // _PATH_FINDER_HPP_INCLUDED
