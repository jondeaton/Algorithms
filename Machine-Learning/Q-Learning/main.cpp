/**
 * @file main.cpp
 * @brief Q-Learning Demo
 */

#include "learner.hpp"
#include "agent.hpp"
#include "environment.hpp"

#include <iostream>

int main() {

  typedef typename maze::environment<10> environment;

  environment env;
  maze::agent actor;

  learner<maze::agent, environment> l(actor, env);
  l.learn();

  return 0;
}