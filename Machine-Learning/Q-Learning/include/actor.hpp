/**
 * @file actor.hpp
 */

#ifndef Q_LEARNING_ACTOR_HPP
#define Q_LEARNING_ACTOR_HPP

#include <type_traits>

template <
  class State,
  class Action,
  std::size_t num_actions,
  std::size_t num_states,
  class Environment>
class maze_actor {

  typedef typename Environment::reward_type reward_type;
  typedef typename State state_type;
  typedef typename Action action_type;

  const reward_type& take_action(const Action& action) {

  }

  const state_type& current_state() {
    return _states[current_state];
  }

private:
  size_t _current_state;
  Action _actions[num_actions];
  State _states[num_states];

  Environment& _environment;
};

#endif //Q_LEARNING_ACTOR_HPP
