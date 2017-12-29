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

template <class T, class Compare>
struct CmpException {
  CmpException(const T& t, Compare comp) : t(t), comp(comp) {};
  bool operator() (const T& a, const T& b) {
    if (a == t) return true;
    if (b == t) return false;
    return comp(a, b);
  }

private:
  const T& t;
  const Compare& comp;
};

template <class T>
class priority_queue_base {
protected:
  std::map<T, int> indices;
};

/**
 * @class priority_queue
 * @brief  A priority queue that supports removal and priority-updating
 * @tparam T  Type of element stored in the priority queue.
 * @tparam Container  The container to use to store the elements. Must support insert, find, end/begin, and erase
 * @tparam Compare  Comparison function object type, defaults to
 *                  less<_Sequence::value_type>.
 * @tparam fast_top  If set to true, then "top" will run in constant time, at the expense of keeping a hash map of
 *                   size O(n), doubling the memory footprint of the priority queue
 */
template<
  class T,
  bool fast_top=true,
  class Compare=typename std::less<T>,
  class Container=typename default_container<fast_top, T, Compare>::type>
class priority_queue : public if_<!fast_top, Empty, priority_queue_base<T>>::value {
public:
  typedef Container                                 container_type;
  typedef typename Container::value_type            value_type;
  typedef typename Container::size_type             size_type;
  typedef typename Container::reference             reference;
  typedef typename Container::const_reference       const_reference;
  typedef typename Container::iterator              iterator;
  typedef typename Container::const_iterator        const_iterator;

  static constexpr bool ft = fast_top;

  priority_queue() = default;

  template <bool enable=fast_top>
  explicit priority_queue(typename std::enable_if<enable, const Compare&>::type cmp)
    : comp(cmp) {}

  template <bool enable=fast_top>
  explicit priority_queue(const typename std::enable_if<!enable, Compare&>::type compare)
    : priority_queue_base<T>(), c(compare), comp(compare) {}

  /**
   * @fn priority_queue::top
   * @return The element at the top (front) of the queue
   */
  iterator top() {
    return c.begin();
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
  void erase(iterator it) {
    if constexpr (ft) {
      T value = *it;

      Compare comp_temp = comp; // Store the
      comp = new CmpException<T, Compare>(value, comp);

      int index = this->indices[value];
      bubble_up(index);
      pop();

      comp = comp_temp;
    } else {
      if (it != c.end()) c.erase(it);
    }
  }

  /**
   * @fn priority_queue::find
   * @param value The value to find in the container
   * @return An iterator to the element in the queue
   */
  iterator find(const T& value) {
    if constexpr (fast_top) {
      if (contains(value)) return c.begin() + this->indices[value];
      return end();
    } else return c.find(value);
  }

  /**
   * @fn priority_queue::update_priority
   * @details Simply removed and adds the
   * @param it
   */
  void update_priority(iterator it) {
    if constexpr (fast_top) {
      int index = this->indices[*it];
      bubble_up(sink_down(index));
    } else {
      erase(it);
      push(*it);
    }
  }

  /**
   * @fn priority_queue::end
   * @return An iterator to the end of the container
   */
  iterator end() {
    return c.end();
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

  inline bool contains(const T& value) {
    if constexpr (fast_top) return this->indices.find(value) != this->indices.end();
    else return c.find(value) != c.end();
  }

  typename std::enable_if<fast_top, int>::type
  bubble_up(int index) {
    if (index == 0) return 0;         // at root
    int parent = parent_of(index);
    if (comp(c[index], c[parent])) {
      std::swap(c[index], c[parent]);
      this->indices[c[index]] = index;
      return bubble_up(parent);
    } else return index;
  }

  typename std::enable_if<fast_top, int>::type
  sink_down(int index) {
    int left = left_of(index);     // Index of left child
    int right = right_of(index);   // Index of right child
    if (left >= (int) size()) return index;    // No children

    if (comp(c[left], c[index]) && comp(c[left], c[right])) {
      std::swap(c[left], c[index]);
      this->indices[c[index]] = index;
      return sink_down(left);
    } else if (comp(c[index], c[right]) && comp(c[right], c[left])) {
      std::swap(c[right], c[index]);
      this->indices[c[index]] = index;
      return sink_down(right);
    } else return index; // all done!
  }

  typename std::enable_if<fast_top, int>::type
  inline left_of(int index) { return 2 * (index + 1) - 1; }

  typename std::enable_if<fast_top, int>::type
  inline right_of(int index) { return 1 + left_of(index); }

  typename std::enable_if<fast_top, int>::type
  inline parent_of(int index) { return (index + 1) / 2 - 1; }
};

#endif //_PRIORITY_QUEUE_INCLUDED_HPP