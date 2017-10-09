/*
 * File: test-RedBlackTree.cpp
 * ------------------
 * For testing the Red Black tree
 */

#include "RedBlackTree.h"
#include <random>
#include <iostream>

using namespace std;

int main() {
  RedBlackTree<int> tree;

  // Basic insertion check
  for (int i = 0; i < 14; i++) {
    tree.insert(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
  cout << "Finished basic insertion" << endl;

  // Mixed insertion test
  for (int i = 0; i < 100; i++) {
    tree.insert((int) random() % 100);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
  cout << "Finished mixed insertion." << endl;

  for (int i = 0; i < 14; i++) {
    tree.insert(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }

  for (int i = 0; i < 6; i++) {
    tree.remove(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }

  tree.clear();
  return 0;
}
