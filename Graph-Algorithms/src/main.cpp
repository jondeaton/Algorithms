/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include "path.hpp"
#include "path-finder.hpp"

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
static void get_coordinates(vector<Coordinate> &coordinates, size_t N);

template <size_t I, class T, class... Ts>
typename enable_if<I < sizeof...(Ts) + 1, T>::type
euclidian_square_distance(const tuple<T, Ts...>& x, const tuple<T, Ts...>& y) {
  auto diff = get<0>(x) - get<0>(y);
  return diff * diff + euclidian_square_distance<I+1, T, Ts...>(x, y);
}

template <size_t I, class T, class... Ts>
typename enable_if<I == sizeof...(Ts) + 1, T>::type
euclidian_square_distance(const tuple<T, Ts...>& x, const tuple<T, Ts...>& y) {
  (void) x;
  (void) y;
  return 0;
}

template <class Coordinate>
class distance_function {
public:
  double operator() (const Coordinate& x, const Coordinate& y) {
    return sqrt(euclidian_square_distance(x, y));
  }
};

/**
 * @fn DistanceToEnd
 * @brief Defines a functor that can calculate the distance from any two arbitrary points
 * @tparam T The type of the difference between coordinates
 * @tparam CMP The function type used to compare two coordinates
 * @tparam Coordinate
 */
template <class Distance, class Coordinate, class DistanceFn>
class DistanceToEnd {
public:
  DistanceToEnd(const vector<Coordinate>& coordinates, size_t end_index) : end_index(end_index) {
    size_t numel = coordinates.size();
    set = (bool*) calloc(numel * sizeof(bool), 1);

    distances = (Distance*) malloc(numel * sizeof(Distance));
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
    free(distances);
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

  typedef Graph<float, float> graph;
  typedef tuple<float, float> coordinate;
  typedef DistanceToEnd<float, coordinate, distance_function<coordinate>> distance_fn;

  graph g;
  make_graph(g);

  vector<coordinate> coordinates;
  get_coordinates(coordinates, g.size());

  size_t start, end;
  cin >> start;
  cin >> end;

  // Find the path
  distance_fn h(coordinates, end);
//  PathFinder<graph, distance_fn> path_finder(h);
//  auto path = path_finder.find_path(g, start, end);
//  cout << path << endl;
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
static void get_coordinates(vector<Coordinate> &coordinates, size_t N) {
  for (size_t i = 0; i < N; ++i) {
    Coordinate c;
    // cin >> c;
    coordinates.push_back(c);
  }
}