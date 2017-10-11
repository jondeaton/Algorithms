/*
 * File: test-RedBlackTree.cpp
 * ------------------
 * For testing the Red Black tree
 */

#include "RedBlackTree.h"
#include <random>
#include <iostream>

using namespace std;

void basicInsertion() {
  RedBlackTree<int> tree;
  // Basic insertion check
  for (int i = 0; i < 14; i++) {
    tree.insert(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}


int main() {

  basicInsertion();
  cout << "Finished ascending insertion." << endl;

  RedBlackTree<int> tree;
  for (int i = 13; i >= 0; i--) {
    tree.insert(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }

  cout << "Finished descending insertion." << endl;

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

  cout << "Finishes basic removal." << endl;


  for (int i = 0; i < 100000; i++) {
    tree.insert((int) random());
    tree.insert((int) random());
    tree.remove((int) random());
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  cout << "Finished randomixed insertion and removal" << endl;


  for (int i = 1000; i > 0; i--) {
    tree.remove(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }

  cout << "Finished descending removal." << endl;

  tree.clear();

  return 0;
}
