/**
 * @file main.cpp
 * @brief Q-Learning Demo
 */

#include "learner.hpp"
#include "actor.hpp"
#include "environment.hpp"

#include <iostream>

int main() {

  maze env;
  maze_actor< actor;

  learner<maze_actor, environment> l;
  l.learn();

  return 0;
}