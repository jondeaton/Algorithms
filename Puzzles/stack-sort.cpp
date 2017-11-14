/*
 * File: stack-sort.cpp
 * --------------------
 * Sort a stack using another stack.
 */

#include <stdio>
#include <stack>
#include <random>
using namespace std;

template <class T>
void stack_sort(stack<T>& A) {

    stack<T> B;
    int k = 0;
    int N = A.size();

    T highest;
    while (k < N) {

        // Flip them all over
        for (int i = 0; i < N - k; i++) {
            T next = A.pop();
            if (next > xf) { }
        }
        k++;
    }

}

/**
 * Function: print_stack
 * ---------------------
 * Prints the contents of a stack to stdout
 * @tparam T: The type of element stored in the stack
 * @param A: The queue of elements
 */
template <class T>
void print_stack(stack<T>& A) {

    stack<T> B;
    while (!A.empty()) {
        T next = A.top;
        A.pop();
        cout << next << " ";
        B.push(next);
    }
    cout << endl;

    while (!B.empty()) {
        T next = B.top();
        B.pop();
        A.push(next); // put it all back
    }
}

int main(int argc, char* argv[]) {

    stack<int> A;
    N = 10;
    for (int i = 0; i < N; i++) A.push(rand() % 100);

    print_stack(A);
    stack_sort(A);
    print_stack(A);
    return 0;
}
