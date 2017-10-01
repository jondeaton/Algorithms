/*
 * File: partition.cpp
 * -------------------
 * Partition and swap algorithms
 */

#include <vector>

template <class T>
void partition(std::vector<T>& array, size_t left, size_t right, T pivot);

template <class T>
void swap(std::vector<T>& array, size_t indexA, size_t indexB);

/**
 * Function: partition
 * -------------------
 * Modifies the array so that all elements less than the pivot come before all element
 * greater than the pivot between indexes left and right.
 * @tparam T: The type of the elements
 * @param array: The array to partition
 * @param left: The left index
 * @param right: The right index
 * @param pivot: The element to compare to
 */
template <class T>
void partition(std::vector<T>& array, size_t left, size_t right, T pivot) {
    while (left <= right) {
        if (array[left] > pivot) {
            swap<T>(array, left, right);
            right--;
        } else {

        }
    }
}

template <class T>
void swap(std::vector<T>& array, size_t indexA, size_t indexB) {

}