

#ifndef _VERTEX_HPP_INCLUDED
#define _VERTEX_HPP_INCLUDED

class Edge {
public:
  Edge() = default;
  Edge(int weight, int to) : weight(weight), to(to) {}
  int weight;
  int to;
};

#endif // _VERTEX_HPP_INCLUDED
