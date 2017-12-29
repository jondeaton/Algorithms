/**
 * @file pq-test.cpp
 * @brief tests the performance difference between the two implementations of the priority queue
 */

#include "priority-queue.hpp"
#include <iostream>

using namespace std;

#define N 1000000

template <class T, bool heap>
void test(priority_queue<T, heap>& queue){
  int x = 0;
  for (int i = 0; i < N; ++i) queue.push(i);
  for (int i = 0; i < N; i += 2) queue.erase(i);
  for (int i = 0; i < N; i += 2) x += queue.top();
  while (!queue.empty()) queue.pop();
}

template <class T, bool heap>
void time_test(const string& name, priority_queue<T, heap>& queue){
  clock_t begin = clock();
  test(queue);
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << name << ":\t" << elapsed_secs << " [seconds] elapsed" << endl;
}

int main() {
  priority_queue<int, false> queue_set;
  time_test("Set", queue_set);

  priority_queue<int, true> queue_heap;
  time_test("Heap", queue_heap);
}