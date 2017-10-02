/*
 * File: test-MinHeap.cpp
 * ----------------------
 * For testing the MinHeap data structure
 */

#include "MinHeap.h"
#include <iostream>
#include <stdio.h>
#include <random>

void printHeap(MinHeap<int>& heap) {
  cout << "Contents: ";

  while (heap.size() > 1) {
    cout << heap.pop() << ", ";
  }
  cout << heap.pop();
  cout << endl;
}

int main() {

  MinHeap<int> heap;

  for (int i = 0; i < 10; i++)
    heap.insert(random() % 100);

  printHeap(heap);

  // Mixed insert and pop
  for (int i = 0; i < 100; i++) {
    heap.insert(random() % 5);
    heap.insert(random() % 7);
    heap.pop();
  }
  printHeap(heap);

  // Search test
  heap.clear();
  heap.insert(100);
  heap.insert(4);
  heap.insert(70);
  cout << "Heap contains 4? " << heap.contains(4) << endl;
  cout << "Heap contains 70? " << heap.contains(70) << endl;
  cout << "Heap contains 100? " << heap.contains(100) << endl;
  cout << "Heap contains 5? " << heap.contains(5) << endl;
  cout << "Heap contains 0? " << heap.contains(0) << endl;
}

