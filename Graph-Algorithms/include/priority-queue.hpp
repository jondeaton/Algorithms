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

#include <queue>
std::priority_queue<int> e;

template <bool, class T, class... Ts>
static struct default_container<false> {
  typedef std::set<T, Ts...> type;
};

template <bool, class T, class... Ts>
static struct default_container<true> {
  typedef std::vector<T> type;
};

template <class T, class Compare>
static struct TrueCmp {
  TrueCmp(Compare comp, const T& t) : comp(comp), t(t) = default;
  bool operator() (const T& a, const T& b) {
    if (a == t) return true;
    if (b == t) return false;
    return comp(a, b);
  }

private:
  const T& t;
  Compare comp;
};

/**
 * @brief  A priority queue that supports removal and priority-
 * @tparam T  Type of element stored in the priority queue.
 * @tparam Container  The container to use to store the elements. Must support insert, find, end/begin, and erase
 * @tparam Compare  Comparison function object type, defaults to
 *                  less<_Sequence::value_type>.
 * @tparam fast_top  If set to true, then "top" will run in constant time, at the expense of keeping a hash map of
 *                   size O(n), doubling the memory footprint of the priority queue
 */
template<
  class T,
  class Container=default_container<fast_top, T, Compare>::type,
  class Compare=std::less<typename Container::value_type>,
  bool fast_top=false>
class priority_queue {
public:
  priority_queue() = default;
  explicit priority_queue(Compare& cmp) : c(cmp), comp(cmp) {}

  inline bool empty() { return c.empty(); }
  inline size_t size() { return c.size(); }
  T& top() { return c.begin(); }

  typename std::enable_if<fast_top>::type
  void push(const T& value) {
    c.push_back(value);
    return bubble_up(size() - 1);
  }

  typename std::enable_if<fast_top>::type
  void pop() {
    T min = top();

    c[0] = c.back();
    c.pop_back();
    sink_down(0);
  }

  typename std::enable_if<fast_top>::type
  bool remove(const T& value) {
    if (indices.find(value) == indices.end()) return false;

    Compare comp_temp = comp;
    comp = new TrueCmp(comp, value);

    size_t index = indices[value];
    bubble_up(index);

    pop();
    return true;
  }

  typename std::enable_if<fast_top>::type
  void update_priority(const T& value) {
    size_t index = indices[value];
  }

  // Set implementation

  typename std::enable_if<!fast_top>::type
  void push(std::enable_if<!fast_top, const T&>::type value) { c.insert(value); }

  typename std::enable_if<!fast_top>::type
  void pop() {
    if (c.empty()) return;
    c.erase(top());
  }

  typename std::enable_if<!fast_top>::type
  bool remove(const T& value) {
    auto it = c.find(value);
    if (it == c.end()) return false;
    c.erase(it);
    return true;
  }

  typename std::enable_if<!fast_top>::type
  void update_priority(const T& value) {
    remove(value);
    push(value);
  }

  template <class ... Args>
  typename std::enable_if<!fast_top>::type
  void emplace(Args&&... args) {
    c.emplace(args ...);
  }

protected:
  Container c;
  Compare comp;

private:
  typename <std::enable_if<fast_top>>::type
  std::map<T, size_t> indices;

  void bubble_up(size_t index) {
    if (index == 0) return; // at root

    int parent = parent_of(index);
    if (comp(c[index], c[parent])) {
      swap(index, parent);
      bubble_up(parent);
    }
  }

  void sink_down(size_t index) {
    size_t left = left_of(index);     // Index of left child
    size_t right = right_of(index);   // Index of right child
    if (left >= size()) return;       // No children

    if (c[index] > c[left] && c[left] <= c[right]) {
      swap(left, index);
      sink_down(left);
    } else if (c[index] > c[right] && c[right] <= c[left]) {
      swap(right, index);
      sink_down(right);
    }
  }

  void swap(size_t indexA, size_t indexB) {
    T temp = c[indexA];
    c[indexA] = c[indexB];
    c[indexB] = temp;
  }

  inline size_t left_of(size_t index) { return 2 * (index + 1) - 1; }
  inline size_t right_of(size_t index) { return 1 + left_of(index); }
  inline int parent_of(size_t index) { return (int) (index + 1) / 2 - 1; }
};

#endif //_PRIORITY_QUEUE_INCLUDED_HPP