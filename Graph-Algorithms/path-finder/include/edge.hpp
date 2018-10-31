

#ifndef _VERTEX_HPP_INCLUDED
#define _VERTEX_HPP_INCLUDED

#include <cstdlib>

template <class T>
class Edge {
public:
  Edge() = default;
  Edge(T weight, size_t to) : weight(weight), to(to) {}
  T weight;
  size_t to;
};

#endif // _VERTEX_HPP_INCLUDED
