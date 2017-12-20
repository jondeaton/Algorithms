/**
 * @file priority-queue.hpp
 * @brief Presents the interface of a mutable priority queue
 *
 * @author Jon Deaton
 * @date December 13, 2017
 * @version 1.0
 *
 * @details  An implementation of a priority queue that supports for removal and priority
 * update in logarithmic time while
 *
 */

#ifndef _PRIORITY_QUEUE_INCLUDED_HPP
#define _PRIORITY_QUEUE_INCLUDED_HPP

#include <set>
#include <vector>

#include <queue>
std::priority_queue<int> e;

/**
 * @brief  A priority queue that supports removal and priority-
 * @tparam T  Type of element.
 * @tparam Container  The container to use to store the elements. Must support insert, find, end/begin, and erase
 * @tparam Compare  Comparison function object type, defaults to
 *                  less<_Sequence::value_type>.
 */
template<class T, class Container=std::set<T, Compare>, class Compare=std::less<typename Container::value_type>>
class priority_queue {
public:
  priority_queue() = default;
  explicit priority_queue(Compare& cmp) : c(cmp), cmp(cmp) {}

  void push(const T& value) { c.insert(value); }

  void pop() {
    if (c.empty()) return;
    c.erase(top());
  }

  T& top() { return c.begin(); }

  bool remove(const T& value) {
    auto it = c.find(value);
    if (it == c.end()) return false;
    c.erase(it);
    return true;
  }

  void update_priority(const T& value) {
    remove(value);
    push(value);
  }

  bool empty() { return c.empty(); }
  size_t size() { return c.size(); }

  template <class ... Args>
  void emplace(Args&&... args) {
    c.emplace(args ...);
  }

protected:
  Container c;
  Compare cmp;
};

#endif //_PRIORITY_QUEUE_INCLUDED_HPP