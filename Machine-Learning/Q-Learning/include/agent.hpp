/**
 * @file actor.hpp
 */

#ifndef Q_LEARNING_ACTOR_HPP
#define Q_LEARNING_ACTOR_HPP

#include "maze.hpp"
#include "environment.hpp"

#include <type_traits>
#include <iostream>

namespace maze {

  enum direction {up, down, left, right, stay} ;

  class move {
  public:
    maze::direction direction;
    explicit move(maze::direction direction) : direction(direction) {}
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

  template <class Environment, class Observation, std::size_t N_actions=5>
  class agent {
  public:

    static constexpr std::size_t num_actions = N_actions;
    static constexpr std::size_t num_states = Environment::num_states;

    typedef typename Environment::reward_type reward_type;
    typedef typename location state_type;
    typedef typename move action_type;
    typedef typename maze::location observation_type;

    agent(Environment& maze) : _maze(maze), _current_state(0) {
      _init_actions();
    }

    void _init_actions() {
      _actions[0] = move(up);
      _actions[1] = move(down);
      _actions[2] = move(left);
      _actions[3] = move(right);
      _actions[4] = move(stay);
    }

    const reward_type& try_action(const action_type &action) {
      return _maze.try_move(_states[_current_state], action.direction);
    }

    const observation_type& observe() {

    }

    inline const state_type& current_state() const {
      return _states[_current_state];
    }

    const action_type& action_at(int index) const {
      return _actions[index];
    }

  private:
    size_t _current_state;
    move _actions[N_actions];
    state_type _states[num_states];
    Environment& _maze;
  };
}


#endif //Q_LEARNING_ACTOR_HPP
