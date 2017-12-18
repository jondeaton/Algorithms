/**
 * File: graph-search.hpp
 * ----------------------
 * Presents the interface of graph searching class
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

/**
 * Class: GraphSearch
 * ------------------
 * Provides functionality for path finding in directed, weighted graphs
 * @tparam T: Type of data stored in the nodes of the graph
 * @tparam WT: The type of data stored in the weights of the graphs
 */
template <class T, class WT, class ... Ts>
class GraphSearcher {
public:
  GraphSearcher();
  Path<size_t> find_path(Graph<T, WT> graph, size_t source, size_t sink);
  Path<size_t> make_path(size_t start, size_t end);
  ~GraphSearcher();

private:
  size_t data_size;
  size_t* prevs;
  WT* distances;
  void setup_arrays(size_t new_size);
};

#endif // _DIJKSTRA_HPP_INCLUDED
