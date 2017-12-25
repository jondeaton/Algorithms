/**
 * @file coordinate.h
 */

#ifndef GRAPH_ALGORITHMS_COORDINATE_H
#define GRAPH_ALGORITHMS_COORDINATE_H

#include <vector>
#include <iostream>
#include <cmath>

template <class T, size_t I>
class Coordinate {
public:
  Coordinate() = default;
  explicit Coordinate(T components[]) {
    set(components);
  }

  void set(T components[]) {
    memcpy(this->components, components, sizeof(T) * I);
  }

  double distance_to(const Coordinate<T, I> &x) {
    T sq_diff;
    for (int i = 0; i < I; ++i) sq_diff += (x.components[i] - components[i]);
    return sqrt(sq_diff);
  }

  T components[I];

private:
  template <class U>
  friend std::istream& operator>>(std::istream& is, Coordinate<U, I>& coordinate);
};

template <class T, size_t I>
std::istream& operator>>(std::istream& is, Coordinate<T, I>& coordinate) {
  T x;
  for (int i = 0; i < I; ++i) {
    is >> x;
    coordinate.components[i] = x;
  }
}

#endif //GRAPH_ALGORITHMS_COORDINATE_H
