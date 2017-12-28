/*
 * File: smallest-k.cpp
 * --------------------
 * Problem: Design an algorithm to find the smallest k numbers in an array
 * Algorithm approach: Selection rank
 */

#include <stdlib.h>
#include <vector>
using namespace std;

/**
 * Function: smallestK
 * -------------------
 * Modifies the array to put the smallest k numbers at the beginning
 * @param elements: List of elements to find the k smallest in
 * @param smallest: Vector of elements to which to add the k'th smallest
 * @param k: The number of elements to add to the "smallest" vector
 */
void smallestK(vector<int>& elements, vector<int>& smallest, size_t k) {
    size_t kth_largest = rank(elements, 0, elements.size(), k);
    for (int n : elements)
        if (n <= kth_largest) smallest.push_back(n);
}

/**
 * Function: rank
 * --------------
 * Gets the element in the array between left and right indices of a certain rank
 * @param array: An array of integers to search through, will be modified
 * @param left: Left index (inclusive)
 * @param right: Right index (exclusive)
 * @param rank: The number of elements that the returned element is bigger than between left and right
 * @return: The rank'th largest element it the array
 */
int rank(vector<int>& array, size_t left, size_t right, size_t rank) {
    size_t pivot = left + rand() % (right - left);

    size_t leftEnd = partition(array, left, right, pivot);
}

/**
 * Function: partition
 * -------------------
 * Puts all of the elements less than the element at the pivot index
 * @param array
 * @param left
 * @param right
 * @return
 */
int partition(vector<int>& array, size_t left, size_t right, size_t pivot) {

}