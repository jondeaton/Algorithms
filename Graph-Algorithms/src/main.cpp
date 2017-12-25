/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.hpp"
#include "path.hpp"
#include "path-finder.hpp"
#include "coordinate.hpp"

#include <fstream>
#include <iostream>

using namespace std;

template <class T, size_t I>
static void get_coordinates(vector<Coordinate<T, I>> &coordinates, size_t N) {
  Coordinate<T, I> c;
  for (size_t i = 0; i < N; ++i) {
    cin >> c;
    coordinates.push_back(c);
  }
}

template <class T, size_t I>
struct DistanceBetween {
  double operator()(const Coordinate<T, I>& x, const Coordinate<T, I>& y) {
    return x.distance_to(y);
  }
};

/**
 * @fn DistanceToEnd
 * @brief Defines a functor that can calculate the distance from any two arbitrary points
 * @tparam Distance The type of the distance measurement between coordinates
 * @tparam Coordinate The type of the coordinate
 * @tparam DistanceFn The function which finds the distance between two coordinates
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
    distances[i] = distanceFn(coordinates[end_index], coordinates[i]);
    set[i] = true;
    return distances[i];
  }

  ~DistanceToEnd(){
    free(set);
    free(distances);
  }

private:
  bool* set;
  size_t end_index;

  DistanceFn distanceFn;

  const Coordinate* coordinates;
  Distance* distances;
};

void test_Astar() {
  ifstream in("/Users/jonpdeaton/GitHub/Algorithms/Graph-Algorithms/Astar-test");
  cin.rdbuf(in.rdbuf());

  typedef Graph<int, int> graph;
  typedef Coordinate<int, 2> coordinate;
  typedef DistanceToEnd<double, coordinate, DistanceBetween<int, 2>> distance_fn;

  graph g;
  cin >> g;

  vector<coordinate> coordinates;
  get_coordinates(coordinates, g.size());

  size_t start, end;
  cin >> start;
  cin >> end;

  // Find the path
  distance_fn h(coordinates, end);
  PathFinder<graph, distance_fn> path_finder(h);
  auto path = path_finder.find_path(g, start, end);
  cout << path << endl;
}

void test_dijkstra() {
  ifstream in("/Users/jonpdeaton/GitHub/Algorithms/Graph-Algorithms/dinkstra-test");
  cin.rdbuf(in.rdbuf());

  typedef Graph<int, int> graph;
  graph g;
  cin >> g;

  size_t start, end;
  cin >> start;
  cin >> end;

  PathFinder<graph> path_finder;
  auto path = path_finder.find_path(g, start, end);
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