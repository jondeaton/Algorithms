/**
 * @file main.cpp
 * @brief Q-Learning Demo
 */

#include "learner.hpp"
#include "actor.hpp"
#include "environment.hpp"

#include <iostream>

int main() {

  maze<10> env;
  maze_actor actor;

  learner<maze_actor, maze> l(actor, env);
  l.learn();

  return 0;
}