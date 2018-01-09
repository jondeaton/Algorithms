/**
 * @file environment.hpp
 * @brief The interface of the actor's environment
 *
 * @author Jonathan Deaton
 * @date 12/31/17
 */

#ifndef Q_LEARNING_ENVIRONMENT_HPP
#define Q_LEARNING_ENVIRONMENT_HPP

#include <vector>
#include <iostream>

class location {
public:
  int row;
  int column;
  friend std::ostream& operator<<(std::ostream& os, const location& location);
};

std::ostream& operator<<(std::ostream& os, const location& location) {
  os << "row: " << location.row << ", column: " << location.column;
  return os;
}

template <class Reward=double, std::size_t rows, std::size_t columns=rows>
class maze {
public:

  static size_t rows = rows;
  static size_t columns = columns;

  maze() {

  }

  location try_move(const location& from, direction dir) {
    location new_location;


  }

  bool free[rows][columns];

  friend std::ostream& operator<<(std::ostream& os, const maze& maze);
};

std::ostream& operator<<(std::ostream& os, const maze& maze) {
  // todo: this!
  return os;
}



#endif //Q_LEARNING_ENVIRONMENT_HPP
