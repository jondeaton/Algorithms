/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include "path.hpp"
#include "path-finder.hpp"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/distance_result.hpp>

#include <tuple>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iostream>
using namespace std;

// Static function declaration
template <class Graph>
static void make_graph(Graph &graph);

template <class Coordinate>
static void get_coordinates(vector<Coordinate> coords);

/**
 * @fn DistanceToEnd
 * @brief Defines a functor that can calculate the distance from any two arbitrary points
 * @tparam T The type of the difference between coordinates
 * @tparam CMP The function type used to compare two coordinates
 * @tparam Coordinate
 */
template <class Distance, class Coordinate, class DistanceFn>
class DistanceToEnd {
  DistanceToEnd(Distance distances[], size_t numel, size_t end_index
                DistanceFn f, Coordinate) :
  distances(distances), end_index(end_index), f(f) {
    set = (bool*) calloc(numel * sizeof(bool), 1);
    distances[end_index] = 0;
    set[end_index] = true;
  };

  Distance operator()(int i) {
    if (set[i]) return distances[i];

    distances[i] = f(coordinates[end_index], coordinates[i]);
    set[i] = true;
    return distances[i];
  }

  ~DistanceToEnd(){
    free(set);
  }

private:
  bool* set;
  Distance distance_to;
  size_t end_index;

  DistanceFn f;

  const Coordinate* coordinates;
  Distance* distances;
};

void test_Astar() {
  ifstream in("/Users/jonpdeaton/GitHub/Algorithms/Graph-Algorithms/Astar-test");
  cin.rdbuf(in.rdbuf());

  typedef typename boost::geometry::cs::cartesian cartesian;
  typedef typename boost::geometry::model::point<double, 2, cartesian> point;
  typedef typename boost::geometry::default_distance_result<cartesian, cartesian> distance;

  Graph<float, float> graph;
  make_graph(graph);
  
  vector<point> coordinates;
  get_coordinates(coordinates);

  size_t start, end;
  cin >> start;
  cin >> end;



  // Find the path
  DistanceToEnd<> h();
  PathFinder<Graph<int, int>, DistanceToEnd<float, point, distance>> path_finder(h);
  auto path = path_finder.find_path(graph, start, end);
  cout << path << endl;
}

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

  PathFinder<Graph<int, int>> path_finder;
  auto path = path_finder.find_path(graph, start, end);
  cout << path << endl;
}

int main() {
  clock_t begin = clock();
  test_dijkstra();
  test_Astar();
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Elapsed time: " << elapsed_secs << endl;
}

template <class Graph>
static void make_graph(Graph &graph) {

  size_t num_nodes, num_edges;
  cin >> num_nodes;
  cin >> num_edges;

  for (size_t i = 0; i < num_nodes; ++i) graph.add_node();

  size_t from, to;
  typename Graph::weight_type weight;

  for (size_t i = 0; i < num_edges; i++) {
    cin >> from;
    cin >> to;
    cin >> weight;
    graph[from].add_edge(weight, to);
  }
}

template <class Coordinate>
static void get_coordinates(vector<Coordinate>& coordinates) {

  // todo
}