/*
 * File: test-MinHeap.cpp
 * ----------------------
 * For testing the MinHeap data structure
 */

#include "MinHeap.h"
#include <iostream>
#include <stdio.h>
#include <random>

int main(int argc, char* argv[]) {
  (void) argc;
  (void) argv;

  MinHeap<int> heap;

  for (int i = 0; i < 10; i++)
    heap.insert(random() % 100);

  cout << "Contents:" << endl;

  while (heap.size() > 0) {
    cout << heap.pop() << ", ";
  }
  cout << endl;
}