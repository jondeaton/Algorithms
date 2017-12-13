/**
 * @file custom-priority-queue.hpp
 * @brief Presents the interface of a custom priority queue that supports removal
 *
 * @author Jon Deaton
 * @date December 13, 2017
 * @version 1.0
 *
 * @details  This priority queue implementation allows for
 *
 */

#include <set>

/**
 * @brief  A priority queue that supports removal and priority-
 * @tparam T  Type of element.
 * @tparam Container  Type of underlying sequence, defaults to vector<_Tp>.
 * @tparam Compare  Comparison function object type, defaults to
 *                  less<_Sequence::value_type>.
 */
template<typename T, class Compare=std::less<typename std::set<T>::value_type>>
class mutable_priority_queue : public std::set<T, std::set<T>, Compare> {
public:
    bool remove(const T& value);
    bool change_priority(const T& value);
};