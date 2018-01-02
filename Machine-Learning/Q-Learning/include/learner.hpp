/**
 * @file learner.hpp
 * @brief Q-Learning algorithm
 */

#ifndef Q_LEARNING_LEARNER_HPP
#define Q_LEARNING_LEARNER_HPP

#include <map>

template <class Actor, class Environment>
class learner {
public:
  learner(const Actor& actor, const Environment& environment)
    : _actor(actor), _environment(environment) {}

  typedef typename Actor::reward_type reward_type;
  typedef typename Actor::state_type state_type;
  typedef typename Actor::action_type action_type;

  /**
   * @fn learn
   * @return The maximum reward obtained
   */
  reward_type learn(unsigned int num_repetitions=30) {
    reward_type max_reward = 0;
    for (unsigned int episode = 0; episode < num_repetitions; episode++) {
      reward_type reward = play_episode();
      if (reward > max_reward) max_reward = reward;
    }
    return max_reward;
  }

  /**
   * @fn play_episode
   * @return The total reward achieved during the episode
   */
  reward_type play_episode() {
    _environment.reset();
    _actor.reset();

    reward_type total_reward = 0;
    while (!_actor.is_done()) {
      const state_type& s = _actor.current_state();

      const action_type& optimal_action = _find_optional_aciton();

      reward_type r = _actor.take_action(optimal_action);
      update_Q(s, optimal_action, r, max_v);
      total_reward += r;
    }
    return total_reward;
  }

private:
  Actor _actor;
  Environment _environment;
  Action choose_action();

  double Q[Actor::num_states][Actor::num_actions];

  double learning_rate;
  double gamma_discount;

  std::map<state_type, int> state_map;
  std::map<action_type, int> action_map;

  const action_type& _find_optional_aciton() {

  }

  double update_Q(const state_type& state, const action_type& action, const reward_type& reward, double max_v) {
    auto s = state_map[state];
    auto a = action_map[action];
    Q[s][a] = (1 - learning_rate) * Q[s][a] + learning_rate * (reward + gamma_discount * max_v);
    return Q[s][a];
  }
};


#endif //Q_LEARNING_LEARNER_HPP
