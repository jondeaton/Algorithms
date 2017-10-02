/*
 * File: MinHeap.h
 * ---------------
 * Presents the interface of a MinHeap data structure.
 * Space Complexity: O(n)
 */

#ifndef _MinHeap_H
#define _MinHeap_H

#include <vector>

template <class T>
class MinHeap {

public:

  explicit MinHeap();
  explicit MinHeap(T elements[]);

  /**
   * Public method: insert
   * ---------------------
   * Inserts an element in to the min heap
   * Complexity: O(log(n))
   * @param element: The element to insert into the MinHeap
   */
  void insert(const T& element);

  /**
   * Public method: pop
   * ------------------
   * Removes the minimum element from the top of the heap and returns it
   * Complexity: O(log(n))
   * @return: Copy of the minimum element form the heap
   */
  T pop();

  /**
   * Public method: peek
   * -------------------
   * Returns a copy of the minimum element without modifying the heap
   * Complexity: O(1)
   * @return: Copy of the minimum element from the heap
   */
  T peek();

  /**
   * Public method: contains
   * -----------------------
   * Determines if the heap contains a certain element
   * Complexity: O(n)
   * @param element: Reference to an element to search for
   * @return: True if an element equal to the query is contained in the heap
   */
  bool contains(const T& element);

  /**
   * Public method: size
   * -------------------
   * Returns the number of elements in the heap
   * Complexity: O(1)
   * @return: Number of elements in the array
   */
  size_t size() { return heap.size(); }

  /**
   * Public method: clear
   * --------------------
   * Empties the heap of all contents
   */
  void clear() { heap.clear(); }

private:
  std::vector<T> heap;

  void bubbleUp(size_t index);
  void sinkDown(size_t index);
  void swap(size_t indexA, size_t indexB);
  bool search(const T& query, size_t start);

  size_t leftOf(size_t index);
  size_t rightOf(size_t index);
  int parentOf(size_t index);
};

#include "MinHeap.tpp"

#endif