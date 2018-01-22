/**
 * @file environment.hpp
 * @brief The interface of the actor's environment
 *
 * @author Jonathan Deaton
 * @date 12/31/17
 */

#ifndef Q_LEARNING_ENVIRONMENT_HPP
#define Q_LEARNING_ENVIRONMENT_HPP

#include "agent.hpp"

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

  template <std::size_t num_rows, std::size_t num_columns=num_rows, class Reward=double>
  class environment {
  public:

    typedef Reward reward_type;
    static constexpr size_t rows = num_rows;
    static constexpr size_t columns = num_columns;
    static constexpr size_t size = num_rows * num_columns;

    environment() {}

    location try_move(const location& from, maze::direction direction) {
      location new_location;

      return new_location;
    }

    bool free[num_rows][num_columns];

    friend std::ostream& operator<<(std::ostream& os, const environment& maze);
  };

  std::ostream& operator<<(std::ostream& os, const environment& maze) {
    // todo: this!
    return os;
  }
}

#endif //Q_LEARNING_ENVIRONMENT_HPP
