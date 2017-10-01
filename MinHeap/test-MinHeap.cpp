/*
 * File: test-MinHeap.cpp
 * ----------------------
 * For testing the MinHeap data structure
 */

#include <MinHeap.h>
#include <stdio.h>
#include <random>

int main(int argc, char* argv[]) {
  MinHeap<int> minHeap;

  for (int i = 0; i < 10; i++) {
    minHeap.insert(random() % 100);
  }

}