/**
 * @file environment.hpp
 * @brief The interface of the actor's environment
 *
 * @author Jonathan Deaton
 * @date 12/31/17
 */

#ifndef Q_LEARNING_ENVIRONMENT_HPP
#define Q_LEARNING_ENVIRONMENT_HPP

#include "maze.hpp"

#include <vector>
#include <iostream>

namespace maze {

  class location {
  public:
    location(): row(0), column(0){}
    location(int row, int column) : row(row), column(column) {}
    int row;
    int column;
    friend std::ostream& operator<<(std::ostream& os, const location& location);
  };

  std::ostream& operator<<(std::ostream& os, const location& location) {
    os << "row: " << location.row << ", column: " << location.column;
    return os;
  }

  template <class Reward=double, std::size_t rows, std::size_t columns=rows>
  class environment {
  public:

    typedef typename Reward reward_type;
    static size_t rows = rows;
    static size_t columns = columns;
    static size_t size = rows * columns;

    environment() {

    }

    location try_move(const location& from, environment::direction dir) {
      location new_location;

    }

    bool free[rows][columns];

    friend std::ostream& operator<<(std::ostream& os, const environment& maze);
  };

  std::ostream& operator<<(std::ostream& os, const environment& maze) {
    // todo: this!
    return os;
  }
}

#endif //Q_LEARNING_ENVIRONMENT_HPP
