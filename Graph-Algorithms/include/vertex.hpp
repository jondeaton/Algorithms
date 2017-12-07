

#ifndef _VERTEX_HPP_INCLUDED
#define _VERTEX_HPP_INCLUDED

class Vertex {
public:
  Vertex() = default;
  Vertex(int weight, int to) : weight(weight), to(to) {}
  int weight;
  int to;
};

#include <vertex.tpp>
#endif // _VERTEX_HPP_INCLUDED
