//
// Created by jdeaton on 9/27/2017.
//

#ifndef ALGORITHMS_PRIVATE_SORTER_CPP_H
#define ALGORITHMS_PRIVATE_SORTER_CPP_H

#include <vector>


template <class T>
int partition(std::vector<T> A, int p, int r) {
  // todo
  return 0;
}

template <class T>
int selection(std::vector<T> A, int i) {
  // todo
  return 0;
}


template <class T>
int median_partition(std::vector<T> A, int p, int r) {
  int i = selection(A, (r - p) / 2);
  std::swap(A[i], A[p]);
  return partition(A, p, r);
}


template <class T>
class Sorter {
public:

  void quick_sort(std::vector<T> A, int p, int r) {
    while (p < r) {
      int q = partition(A, p , r);
      quick_sort(A, p, q - 1);
      p = q + 1;
    }
  }

  void merge_sort(std::vector<T> array) {
    // todo

  }

  void heap_sort(std::vector<T> array) {
    // todo

  }

  void smooth_sort(std::vector<T> array) {
    // todo
  }
};




#endif //ALGORITHMS_PRIVATE_SORTER_CPP_H
