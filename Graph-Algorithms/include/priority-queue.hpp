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


#include "type-traits.hpp"
#include <set>
#include <vector>
#include <map>

template <bool, class T, class... Ts>
struct default_container {};

template <class T, class... Ts>
struct default_container<false, T, Ts...> {
  typedef std::set<T, Ts...> type;
};

template <class T, class... Ts>
struct default_container<true, T, Ts...> {
  typedef std::vector<T> type;
};

template <class T>
class priority_queue_base {
public:
  priority_queue_base() = default;
protected:
  std::map<T, int> indices;
};

/**
 * @class priority_queue
 * @brief  A priority queue that supports removal of elements for updating priorities
 * @tparam T  Type of element stored in the priority queue.
 * @tparam Container  The container to use to store the elements. Must support insert, find, end/begin, and erase
 * @tparam Compare  Comparison function object type, defaults to
 *                  less<_Sequence::value_type>.
 * @tparam fast_top  If set to true, then "top" will run in constant time, at the expense of keeping a hash map of
 *                   size O(n), doubling the memory footprint of the priority queue
 */
template<
  class T,
  bool fast_top=false,
  class Compare=typename std::less<T>,
  class Container=typename default_container<fast_top, T, Compare>::type>
class priority_queue : public if_<fast_top, priority_queue_base<T>, Empty>::value {
public:
  typedef Container                                 container_type;
  typedef typename Container::value_type            value_type;
  typedef typename Container::size_type             size_type;
  typedef typename Container::reference             reference;
  typedef typename Container::const_reference       const_reference;
  typedef typename Container::iterator              iterator;
  typedef typename Container::const_iterator        const_iterator;

  priority_queue() = default;

  template <bool enable=fast_top>
  explicit priority_queue(typename std::enable_if<enable, const Compare&>::type cmp)
    : comp(cmp) {}

  template <bool enable=fast_top>
  explicit priority_queue(const typename std::enable_if<!enable, Compare&>::type cmp)
    : c(cmp), comp(cmp) {}

  /**
   * @fn priority_queue::top
   * @return The element at the top (front) of the queue
   */
  const_reference top() {
    return *c.begin();
  }

  /**
   * @fn priority_queue::push
   * @brief Add an element to the priority queue
   * @param value The value to add to the priority queue.
   */
  void push(const T& value) {
    if constexpr (fast_top) {
      c.push_back(value);
      bubble_up((int) size() - 1);

    } else c.insert(value);
  }

  /**
   * @fn priority_queue::pop
   * @brief remove the top element from the priority queue
   */
  void pop() {
    if constexpr (fast_top) {
      c[0] = c.back();
      c.pop_back();
      sink_down(0);

    } else {
      if (c.empty()) return;
      c.erase(top());
    }
  }

  /**
   * @fn priority_queue
   * @param value
   * @return
   */
  void erase(const T& value) {
    if constexpr (fast_top) {
      int index = this->indices[value];
      swap(index, c.size() - 1);
      c.pop_back();
      this->indices.erase(value);
      sink_down(index);
    } else c.erase(value);
  }

  /**
   * @fn priority_queue::contains
   * @param value The value to check for being contained in the queue
   * @return True if the queue contains this element, false otherwise
   */
  inline bool contains(const T& value) {
    if constexpr (fast_top) return this->indices.find(value) != this->indices.end();
    else return c.find(value) != c.end();
  }

  /**
   * @fn priority_queue::empty
   * @return True if the queue is empty, false otherwise
   */
  inline bool empty() {
    return c.empty();
  }

  /**
   * @fn priority_queue::size
   * @return The number of elements in the priority queue
   */
  inline size_t size() {
    return c.size();
  }

protected:
  Container c;
  Compare comp;

private:

  template <bool enable=fast_top>
  typename std::enable_if<enable, int>::type
  bubble_up(int index) {
    if (index == 0) return 0;         // at root
    int parent = parent_of(index);
    if (comp(c[index], c[parent])) {
      swap(index, parent);
      return bubble_up(parent);
    } else return index;
  }

  template <bool enable=fast_top>
  typename std::enable_if<enable, int>::type
  sink_down(int index) {
    int left = left_of(index);     // Index of left child
    int right = right_of(index);   // Index of right child
    if (left >= (int) size()) return index;    // No children

    if (comp(c[left], c[index]) && comp(c[left], c[right])) {
      swap(left, index);
      return sink_down(left);
    } else if (comp(c[index], c[right]) && comp(c[right], c[left])) {
      swap(right, index);
      return sink_down(right);
    } else return index; // all done!
  }

  template <bool enable=fast_top>
  typename std::enable_if<enable>::type
  inline swap(int index_a, int index_b) {
    std::swap(c[index_a], c[index_b]);
    this->indices[c[index_a]] = index_a;
    this->indices[c[index_b]] = index_b;
  }

  template <bool enable=fast_top>
  typename std::enable_if<enable, int>::type
  inline left_of(int index) { return 2 * (index + 1) - 1; }

  template <bool enable=fast_top>
  typename std::enable_if<enable, int>::type
  inline right_of(int index) { return 1 + left_of(index); }

  template <bool enable=fast_top>
  typename std::enable_if<enable, int>::type
  inline parent_of(int index) { return (index + 1) / 2 - 1; }
};

#endif //_PRIORITY_QUEUE_INCLUDED_HPP