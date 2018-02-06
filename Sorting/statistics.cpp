//
// Created by Jonathan Deaton on 2/4/18.
//

#include <algorithm>
#include <iostream>

using namespace std;

template <class T>
int partition(T A[], int start, int end) {
  
}


template <class T>
int select(T A[], int n, int i) {
  if (n == 0) return A[0];

  int medians[n / 5];
  for (int g = 0; g < n / 5; g++) {
    std::sort(A[g], A[g + 5]);
    A[g] = A[g + 2];
  }

  int mm = select(medians, n / 5, n / 10);
  partition();

}

int main() {

  int A[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  int i = select(A, 10, 3);
  cout << "i: " << A[i] << endl;

  return 0;
}