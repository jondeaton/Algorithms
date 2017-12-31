//
// Created by Jonathan Deaton on 12/31/17.
//

#ifndef Q_LEARNING_ACTOR_HPP
#define Q_LEARNING_ACTOR_HPP

#include <tuple>

template <class State, class Action, class Environment>
class actor {
public:
  const actions get_actions();
  virtual const std::tuple<State, Reward> take_action(const Action& action);

private:
  State _currentState;
  Action _actions[5];
};

class maze_actor : actor {

};

#endif //Q_LEARNING_ACTOR_HPP
