/*
 * File: stack-sort.cpp
 * --------------------
 * Sort a stack using another stack.
 */

#include <stdio>
#include <stack>
#include <random>
using namespace std;

/**
 * Function: insert_into_sorted
 * ----------------------------
 * Inserts an element in to the sorted stack B, by poping elements off of B until the
 * location of the element is exposed, pushing the element to B, and then replacing all
 * of the elements back to B that were displaced.
 * @tparam T: The tpe of elements in the stacks
 * @param el: The element to insert into the sorted stack B
 * @param A: Auxiliary stack to use for displaced elements
 * @param B: The sorted stack to insert the element into
 */
template <class T>
void insert_into_sorted(T el, stack <T> &A, stack <T> &B) {
    // Displace elements from B until the spot for next element is exposed
    int numDisplaced = 0; // Number of elements that are displaced
    while (!B.empty()) {
        T next = B.top();
        if (tmp < next) break;
        B.pop();
        A.push(next);
        numDisplaced++;
    }
    B.push(el); // Put the next element in it's place

    // Move the displaced sorted elements back onto stack B
    while (k > 0) {
        T next = A.top();
        A.pop();
        B.push(next);
        numDisplaced--;
    }
}

/**
 * Function: stack_sort
 * --------------------
 * Sorts a stack using O(n^2) time and O(n) auxiliary space. The approach here
 * is to pop an element off of stack A, and put it into the stack B, which grows and is always sorted.
 * This continues until each element of A has been popped off and B contains all the elements of A.
 * @tparam T: The type of element stored in the stack
 * @param A: The stack to sort
 */
template <class T>
void stack_sort(stack<T>& A) {

    stack<T> B; // Stack where the new sorted elements will go
    while (!A.empty()) {
        T next = A.top(); // Pop off the next element to be placed into stack B
        A.pop();
        insert_into_sorted(next, A, B);
    }
    A = B; // Copy the new stack to the variable A
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
