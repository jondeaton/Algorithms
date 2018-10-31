/**
 * @file main.cpp
 * @brief Tests search algorithms
 */

#include "graph.hpp"
#include "path.hpp"
#include "path-finder.hpp"
#include "coordinate.hpp"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum algorithm {
  a_star,
  dijkstra
};

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
  DistanceToEnd(const vector<Coordinate>& coordinates, size_t end_index)
    : end_index(end_index), coordinates(coordinates) {

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

  const vector<Coordinate> coordinates;
  Distance* distances;
};

void run_astar() {
//  ifstream in("../test/d1");
//  cin.rdbuf(in.rdbuf());

  typedef Graph<int, int> graph;
  typedef Coordinate<int, 2> coordinate;
  typedef DistanceToEnd<double, coordinate, DistanceBetween<int, 2>> distance_fn;

  size_t start, end;
  cin >> start;
  cin >> end;

  graph g;
  cin >> g;

  vector<coordinate> coordinates;
  get_coordinates(coordinates, g.size());

  // Find the path
  distance_fn h(coordinates, end);
  PathFinder<graph, distance_fn> path_finder(h);
  auto path = path_finder.find_path(g, start, end);
  cout << path << endl;
}

void run_dijkstra() {
  typedef Graph<int, int> graph;

  size_t start, end;
  cin >> start;
  cin >> end;

  graph g;
  cin >> g;

  PathFinder<graph> path_finder;
  auto path = path_finder.find_path(g, start, end);
  cout << path << endl;
}

int main(int argc, char* argv[]) {
  (void) argv;
  algorithm alg = argc > 1 ? a_star : dijkstra;
//  run_astar(); return 0;
  if (alg == a_star) run_astar();
  else run_dijkstra();
}
