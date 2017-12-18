

#include <custom-priority-queue.hpp>
#include <algorithm>
using namespace std;

template<class T, class Container, class Compare>
bool mutable_priority_queue<T, Container, Compare>::remove(const T &value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it == this->c.end()) return false;
    std::push_heap(c.begin(), it + 1, cmp);
    std::pop_heap(c.begin(), c.end());
    return true;
}

template<class T, class Container, class Compare>
bool mutable_priority_queue<T, Container, Compare>::change_priority(const T &value) {
    remove(value);

}

template <class T>
bool cmp(const T& a, const T& b) { return false; }
