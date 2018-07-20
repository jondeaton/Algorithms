/**
 * @file MinHeap.tpp
 * @breif Presents the implementation of a MinHeap data structure
 *
 * @detail Copies of all of the elements inserted into the heap are stored in a linear vector
 * that represents a binary tree. This binary tree is sorted such that the values of the child nodes
 * of any node are greater than or equal to the value of the node.
 * The minimum element (root) is stored at the zero'th index of this array.
 *
 * For any node at position i in the heap vector:
 *  - left child is at 2i
 *  - right child it at 2i + 1
 *  - parent is i/2 (if any)
 */

#include <stdexcept>

template <class T>
MinHeap<T>::MinHeap() { }

template <class T>
MinHeap<T>::MinHeap(T elements[]) {
  for (T element : elements) insert(element);
}

template <class T>
void MinHeap<T>::insert(const T& element) {
  heap.push_back(element);
  bubbleUp(heap.size() - 1);
}

template <class T>
bool MinHeap<T>::contains(const T& element) {
  return search(element, 0);
}

template <class T>
T MinHeap<T>::pop() {
  T min = peek();

  heap[0] = heap.back();
  heap.pop_back();
  sinkDown(0);

  return min;
}

template <class T>
T MinHeap<T>::peek() {
  if (size() == 0) throw std::out_of_range ("MinHeap is empty");
  return heap[0];
}

template <class T>
void MinHeap<T>::bubbleUp(size_t index) {
  if (index == 0) return; // at root

  int parent = parentOf(index);
  if (heap[index] < heap[parent]) {
    swap(index, parent);
    bubbleUp(parent);
  }
}

template <class T>
void MinHeap<T>::sinkDown(size_t index) {
  size_t left = leftOf(index); // Index of left child
  size_t right = rightOf(index); // Index of right child

  if (left >= size()) return; // No children

  if (heap[index] > heap[left] && heap[left] <= heap[right]) {
    swap(left, index);
    sinkDown(left);
  } else if (heap[index] > heap[right] && heap[right] <= heap[left]) {
    swap(right, index);
    sinkDown(right);
  }
}

template <class T>
void MinHeap<T>::swap(size_t indexA, size_t indexB) {
  T temp = heap[indexA];
  heap[indexA] = heap[indexB];
  heap[indexB] = temp;
}

template <class T>
bool MinHeap<T>::search(const T& query, size_t start) {
  if (query < heap[start]) return false;
  if (query == heap[start]) return true;
  return search(query, leftOf(start)) || search(query, rightOf(start));
}

template <class T>
inline size_t MinHeap<T>::leftOf(size_t index) {
  return 2 * (index + 1) - 1;
}

template <class T>
inline size_t MinHeap<T>::rightOf(size_t index) {
  return 1 + leftOf(index);
}

template <class T>
inline int MinHeap<T>::parentOf(size_t index) {
  return (index + 1) / 2 - 1;
}