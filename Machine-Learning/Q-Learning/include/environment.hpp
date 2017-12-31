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

template <class State>
class environment {
public:

  const State& observe();

protected:
  std::vector<Stae> states;
};


#endif //Q_LEARNING_ENVIRONMENT_HPP
