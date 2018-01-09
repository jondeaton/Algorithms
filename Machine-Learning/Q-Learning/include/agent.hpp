/**
 * @file actor.hpp
 */

#ifndef Q_LEARNING_ACTOR_HPP
#define Q_LEARNING_ACTOR_HPP

#include "maze.hpp"

#include <type_traits>
#include <iostream>

namespace maze {

  typedef enum {up, down, left, right, stay} direction;

  class move {
  public:
    direction direction;
    friend std::ostream& operator<< (std::ostream& os, const move& move);
  };
  std::ostream& operator<< (std::ostream& os, const move& move) {
    switch(move.direction) {
      case up:
        os << "move up";
        break;
      case down:
        os << "move down";
        break;
      case left:
        os << "move left";
        break;
      case right:
        os << "move right";
        break;
      case stay:
        os << "stay";
        break;
    }
    return os;
  }

  template <std::size_t num_actions=4>
  class agent {
  public:

    static constexpr std::size_t num_actions = num_actions;
    static constexpr std::size_t num_states = num_states;

    typedef typename environment::reward_type reward_type;
    typedef typename location state_type;
    typedef typename move action_type;

    const reward_type& take_action(const action_type& action) {
      return _maze.try_move(_states[_current_state], action.direction);
    }

    inline const state_type& current_state() const {
      return _states[_current_state];
    }

    const action_type& action_at(int index) const {
      return _actions[index];
    }

  private:
    size_t _current_state;
    move _actions[num_actions];
    location _states[num_states];
    environment& _maze;
  };
}


#endif //Q_LEARNING_ACTOR_HPP
