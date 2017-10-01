/*
 * File: MinHeap.h
 * ---------------
 * Presents the implementation of a MinHeap data structure
 *
 * Implementation details:
 *
 * Copies of all of the elements inserted into the heap are stored in a linear vector
 * that represents a binary tree. This binary tree is sorted such that the values of the child nodes
 * of any node are greater than or equal to the value of the node.
 * The minimum element (root) is stored at the zero'th index of this array.
 *
 * For any node at position i in the heap vector:
 *  - left child is at 2i
 *  - right child it at 2i + 1
 *  - parent is i/2 (if any)
 */

#include "MinHeap.h"
using namespace std;

MinHeap::MinHeap() : size(0) { }

MinHeap::MinHeap(T elements[]) : size(0) {
    for (T element : elements) insert(element);
}

void MinHeap::insert(T element) {
    heap.push_back(element);
    bubbleUp(heap.size() - 1);
    size++;
}

bool MinHeap::contains(const T& element) {
    return search(element, 0);
}

T MinHeap::pop() {
    if (size() == 0) throw out_of_range ("MinHeap is empty");

    T min = heap[0];

    heap[0] = heap.back();
    heap.pop_back();
    sinkDown(0);

    size--;
    return min;
}

T MinHeap::peek() {
    if (size() == 0) throw out_of_range ("MinHeap is empty");
    return heap[0];
}

void MinHeap::bubbleUp(size_t position) {
    if (position == 0) return; // no parent
    size_t parent = position / 2;
    if (heap[position] < heap[parent]) {
        swap(position, parent);
        bubbleUp(parent);
    }
}

void MinHeap::sinkDown(size_t position) {
    size_t left = 2 * position;
    size_t right = left + 1;
    if (heap[left] < heap[position]) {
        swap(left, position);
        sinkDown(left);
    } else if (heap[right] < heap[position]) {
        swap(right, position);
        sinkDown(right);
    }
}

void MinHeap::swap(size_t indexA, size_t indexB) {
    T temp = heap[indexA];
    heap[indexA] = heap[indexB];
    heap[indexB] = temp;
}

bool MinHeap::search(const T &query, size_t start) {
    if (query < heap[start]) return false;
    if (query == heap[start]) return true;
    return search(query, 2 * start) || search(query, 2 * start + 1);
}