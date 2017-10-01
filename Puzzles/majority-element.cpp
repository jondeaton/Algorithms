/*
 * File: majority-element.cpp
 * --------------------------
 * Problem: A majority element is an element that makes up more than half of
 * the items in an array. Given a positive integers array, find the majority element.
 * If there is no majority element return -1.
 */

#include <vector>
using namespace std;

static int getCandidate(vector<int> array);
static bool validate(vector<int> array, int candidate)

int findMajorityElement(vector<int> array) {
  int candidate = getCandidate(array);
  return validate(array, candidate) ? candidate : -1;
}

/**
 * Function: getCandidate
 * ----------------------
 * Finds a candidate majority element
 * @param array: An array to search for a majority element candidate in
 * @return:==
 */
static int getCandidate(vector<int> array) {
  int candidate = 0;
  int count = 0;
  for (int n : array) {
    if (n == candidate) count++;
    else count--;
    if (count == 0) candidate = n;
  }
  return candidate;
}

static bool validate(vector<int> array, int candidate) {
  int count = 0;
  for (int n : array)
    if (n == candidate) count++;
  return count > array.size() / 2;
}