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

/**
 * @class  PathFinder
 * @brief  Provides functionality for path finding in directed, weighted graphs
 * @tparam T  Type of data stored in the nodes of the graph
 * @tparam WT The type of data stored in the weights of the graphs
 * @tparam Heuristic The type of function used to get a heuristic
 */
template <class T, class WT, class Heuristic=void>
class PathFinder {
public:
  static constexpr bool use_Astar = !std::is_void<Heuristic>::value;

  PathFinder() = default;

  PathFinder(typename std::enable_if<use_Astar, const Heuristic&>::type heuristic) : distance_to_end(heuristic) {}

  Path<size_t> find_path(Graph<T, WT> graph, size_t source, size_t sink);
  Path<size_t> make_path(size_t start, size_t end);
  ~PathFinder();

private:
  size_t data_size;
  size_t* prevs;
  WT* distances;
  void setup_arrays(size_t new_size);

  typename std::enable_if<use_Astar, WT*>::type priorities;
  typename std::enable_if<use_Astar, Heuristic>::type distance_to_end;
};

#include <path-finder.cpp>
#endif // _PATH_FINDER_HPP_INCLUDED
