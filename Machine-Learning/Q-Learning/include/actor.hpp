/**
 * @file actor.hpp
 */

#ifndef Q_LEARNING_ACTOR_HPP
#define Q_LEARNING_ACTOR_HPP

#include "environment.hpp"
#include <type_traits>
#include <iostream>
#include <tclDecls.h>

enum direction {up, down, left, right};
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
  }
  return os;
}

template <
  class Environment
  std::size_t num_actions=4,
  std::size_t num_states
>
class maze_actor {
public:

  static std::size_t num_actions = num_actions;
  static std::size_t num_states = num_states;

  typedef typename Environment::reward_type reward_type;
  typedef typename location state_type;
  typedef typename move action_type;

  const reward_type& take_action(const action_type& action) {
    return _maze.try_move(action);
  }

  const state_type& current_state() const {
    return _states[_current_state];
  }

  const action_type& action_at(int index) const {
    return _actions[index];
  }

private:
  size_t _current_state;
  move _actions[num_actions];
  location _states[num_states];

  const maze& _maze;
};

#endif //Q_LEARNING_ACTOR_HPP
