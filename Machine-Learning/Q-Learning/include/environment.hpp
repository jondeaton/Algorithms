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

class maze {
public:
  const State& observe();
};


#endif //Q_LEARNING_ENVIRONMENT_HPP
