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
#include <map>

template <bool, class T, class... Ts>
struct default_container
{};

template <class T, class... Ts>
struct default_container<false, T, Ts...> {
  typedef std::set<T, Ts...> type;
};

template <class T, class... Ts>
struct default_container<true, T, Ts...> {
  typedef std::vector<T> type;
};

template <class T, class Compare>
struct TrueCmp {
  TrueCmp(const T& t, Compare comp) : t(t), comp(comp) {};
  bool operator() (const T& a, const T& b) {
    if (a == t) return true;
    if (b == t) return false;
    return comp(a, b);
  }

private:
  const T& t;
  const Compare& comp;
};

/**
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
  bool fast_top=false,
  class Compare=typename std::less<T>,
  class Container=typename default_container<fast_top, T, Compare>::type>
class priority_queue {
public:
  typedef typename Container::value_type value_type;

  priority_queue() = default;
  explicit priority_queue(const Compare& cmp) : c(cmp), comp(cmp) {}

  inline bool empty() { return c.empty(); }
  inline size_t size() { return c.size(); }
  T& top() { return c.begin(); }

  template <bool is_enabled = fast_top>
  typename std::enable_if<fast_top>::type
  push(const T& value) {
    c.push_back(value);
    bubble_up((int) size() - 1);
  }

  template <bool is_enabled = fast_top>
  typename std::enable_if<is_enabled>::type
  pop() {
    c[0] = c.back();
    c.pop_back();
    sink_down(0);
  }

  template <bool is_enabled = fast_top>
  typename std::enable_if<is_enabled, bool>::type
  inline contains(const T& value) {
    return indices.find(value) != indices.end();
  }

  template <bool is_enabled = fast_top>
  typename std::enable_if<is_enabled, bool>::type
  remove(const T& value) {
    if (indices.find(value) == indices.end()) return false;

    Compare comp_temp = comp;
    comp = new TrueCmp<T, Compare>(value, comp);

    int index = indices[value];
    bubble_up(index);

    pop();
    return true;
  }

  template <bool is_enabled = fast_top>
  typename std::enable_if<is_enabled>::type
  update_priority(const T& value) {
    int index = indices[value];
    bubble_up(sink_down(index));
  }

  // Set implementation
  template <bool is_enabled=fast_top>
  typename std::enable_if<!is_enabled>::type
  push(const T& value) {
    c.insert(value);
  }

  template <bool is_enabled=fast_top>
  typename std::enable_if<!is_enabled>::type
  pop() {
    if (c.empty()) return;
    c.erase(top());
  }

  template <bool is_enabled=fast_top>
  typename std::enable_if<!is_enabled, bool>::type
  remove(const T& value) {
    auto it = c.find(value);
    if (it == c.end()) return false;
    c.erase(it);
    return true;
  }

  template <bool is_enabled=fast_top>
  typename std::enable_if<!is_enabled>::type
  update_priority(const T& value) {
    remove(value);
    push(value);
  }

protected:
  Container c;
  Compare comp;

private:
  // Maps values to index within the min heap
  typename std::enable_if<fast_top, std::map<T, int>>::type indices;

  typename std::enable_if<fast_top, int>::type
  bubble_up(int index) {
    if (index == 0) return 0;         // at root
    int parent = parent_of(index);
    if (comp(c[index], c[parent])) {
      std::swap(c[index], c[parent]);
      return bubble_up(parent);
    } else return index;
  }

  typename std::enable_if<fast_top, int>::type
  sink_down(int index) {
    int left = left_of(index);     // Index of left child
    int right = right_of(index);   // Index of right child
    if (left >= size()) return index;    // No children

    if (comp(c[left], c[index]) && comp(c[left], c[right])) {
      std::swap(c[left], c[index]);
      return sink_down(left);
    } else if (comp(c[index], c[right]) && comp(c[right], c[left])) {
      std::swap(c[right], c[index]);
      return sink_down(right);
    } else return index;
  }

  typename std::enable_if<fast_top, int>::type
  inline left_of(int index) { return 2 * (index + 1) - 1; }

  typename std::enable_if<fast_top, int>::type
  inline right_of(int index) { return 1 + left_of(index); }

  typename std::enable_if<fast_top, int>::type
  inline parent_of(int index) { return (index + 1) / 2 - 1; }
};

#endif //_PRIORITY_QUEUE_INCLUDED_HPP