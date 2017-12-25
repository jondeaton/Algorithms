/**
 * @file coordinate.h
 * @brief Simple class for a 2D coordinate system
 * @details Tried using boost::geometry... didn't go well, so now im using this
 */

#ifndef GRAPH_ALGORITHMS_COORDINATE_H
#define GRAPH_ALGORITHMS_COORDINATE_H

#include <vector>
#include <iostream>
#include <cmath>

template <class T, std::size_t I>
class Coordinate {
public:
  Coordinate() = default;
  explicit Coordinate(T components[]) {
    set(components);
  }
  void set(T components[]) {
    memcpy(this->components, components, sizeof(T) * I);
  }
  double distance_to(const Coordinate<T, I> &x) const {
    T sq_diff = 0;
    for (size_t i = 0; i < I; ++i) {
      T diff = x.components[i] - components[i];
      sq_diff += diff * diff;
    }
    return sqrt(sq_diff);
  }
  T components[I];

private:
  template <class U, std::size_t N>
  friend std::istream& operator>>(std::istream& is, Coordinate<U, N>& coordinate);
};

template <class T, std::size_t I>
std::istream& operator>>(std::istream& is, Coordinate<T, I>& coordinate) {
  T x;
  for (size_t i = 0; i < I; ++i) {
    is >> x;
    coordinate.components[i] = x;
  }
  return is;
}

#endif //GRAPH_ALGORITHMS_COORDINATE_H
