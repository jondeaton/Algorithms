/**
 * @file main.cpp
 * @brief Q-Learning Demo
 */

#include "learner.hpp"
#include "actor.hpp"
#include "environment.hpp"

#include <iostream>

int main() {

  typedef typename maze::environment<10> environment;

  environment env;
  maze::actor actor;

  learner<maze::actor, environment> l(actor, env);
  l.learn();

  return 0;
}