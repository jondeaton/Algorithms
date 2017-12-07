
#ifndef _PATH_HPP_INCLUDED
#define _PATH_HPP_INCLUDED

#include <vector>
#include <iostream>

template <class T>
class Path {
public:
  std::vector<T> nodes;
private:
  template <class U>
  friend std::ostream& operator<<(std::ostream& os, const Path<U>& path);

  template <class U>
  friend std::istream& operator>>(std::istream& is, Path<U>& path);
};

template <class T>
std::ostream& operator<<(std::ostream &os, const Path<T>& path) {
  for (int node : path.nodes) os << node << ", ";
  return os;
}

template <class T>
std::istream& operator>>(std::istream& is, Path<T>& path) {
  for (int node : path.nodes) is >> node;
  return is;
}

#endif // _PATH_HPP_INCLUDED
