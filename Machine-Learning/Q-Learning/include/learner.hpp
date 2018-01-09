/**
 * @file learner.hpp
 * @brief Q-Learning algorithm
 */

#ifndef Q_LEARNING_LEARNER_HPP
#define Q_LEARNING_LEARNER_HPP

#include <map>
#include <iostream>

template <class Actor, class Environment, class Quality=double>
class learner {
public:

  typedef typename Actor::reward_type reward_type;
  typedef typename Actor::state_type state_type;
  typedef typename Actor::action_type action_type;
  typedef typename Quality quality_type;

  learner(const Actor& actor, const Environment& environment)
    : _actor(actor), _environment(environment) {}

  /**
   * @fn learn
   * @breif Executes a series of episodes
   * @return The maximum reward obtained
   */
  reward_type learn(unsigned int num_episodes=30) {
    reward_type max_reward = 0;
    for (unsigned int episode = 0; episode < num_episodes; episode++) {
      std::clog << "Episode: " << episode << std::endl;
      reward_type reward = play_episode();
      std::clog << "Episode reward: " << reward << std::endl;
      if (reward > max_reward) max_reward = reward;
    }
    return max_reward;
  }

  /**
   * @fn play_episode
   * @breif Plays a single episode
   * @return The total reward achieved during the episode
   */
  reward_type play_episode() {
    _environment.reset();
    _actor.reset();

    std::clog << "Starting state: " << _actor.current_state() << std::endl;

    reward_type total_reward = 0;
    while (!_actor.is_done()) {
      const state_type& old_state = _actor.current_state();
      const action_type& optimal_action = _find_optional_action(old_state);

      reward_type reward = _actor.take_action(optimal_action);
      const state_type& new_state = _actor.current_state();

      std::clog << "Action: " << optimal_action
                << ", new state: " << new_state
                << ", reward: " << reward << std::endl;

      update_Q(old_state, new_state, optimal_action, reward);
      total_reward += reward;
    }
    return total_reward;
  }

private:
  Actor _actor;
  Environment _environment;
  quality_type Q[Actor::num_states][Actor::num_actions];

  quality_type learning_rate;
  quality_type gamma_discount;

  std::map<state_type, int> state_map;
  std::map<action_type, int> action_map;

  const action_type& _find_optional_action(const state_type& state) {
    quality_type max = std::min<quality_type>;
    int index = 0;
    for (int i=0; i < Actor::num_actions; ++i) {
      quality_type q = Q[state][i];
      if (q > max) {
        max = q;
        index = i;
      }
    }
    return _actor.action_at(index);
  }

  quality_type update_Q(const state_type& new_state, const state_type& old_state, const action_type& action, const reward_type& reward) {
    int new_s = state_map[new_state];
    int a = action_map[action];
    int old_s = state_map[old_state];

    quality_type q = Q[new_s][a];

    Q[old_s][a] = (1 - learning_rate) * Q[old_s][a] + learning_rate * (reward + gamma_discount * q);
    return Q[old_s][a];
  }
};


#endif //Q_LEARNING_LEARNER_HPP