//
// Created by Jonathan Deaton on 12/31/17.
//

#ifndef Q_LEARNING_ACTOR_HPP
#define Q_LEARNING_ACTOR_HPP

#include <tuple>

template <class State, class Action, size_t N, class Environment>
class actor {
public:
  typedef typename Environment::reward_type reward_type;

  const Action* get_actions();
  virtual const std::tuple<State, reward_type> take_action(const Action& action);

private:
  State _currentState;
  Action _actions[N];
};

class maze_actor : actor {

};

#endif //Q_LEARNING_ACTOR_HPP
