/*
 * File: test-RedBlackTree.cpp
 * ------------------
 * For testing the Red Black tree
 */

#include "RedBlackTree.h"
#include <random>
#include <iostream>

using namespace std;

void ascendingInsertion() {
  RedBlackTree<int> tree;
  // Basic insertion check
  for (int i = 0; i < 14; i++) {
    tree.insert(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}

void descendingInsertion() {
  RedBlackTree<int> tree;
  for (int i = 13; i >= 0; i--) {
    tree.insert(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}

void randomizedInsertion() {
  RedBlackTree<int> tree;
  for (int i = 0; i < 1000; i++) {
    tree.insert((int) random() % 1000);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}

void largeInsertion() {
  RedBlackTree<int> tree;
  int numel = 100000;
  for (int i = 0; i < numel; i++) {
    tree.insert((int) random() % 100000);
  }
  if (!tree.verify())
    cout << "Error: large insertion." << endl;
  tree.clear();
}

void ascendingRemoval() {
  RedBlackTree<int> tree;
  for (int i = 0; i < 14; i++)
    tree.insert(i);

  for (int i = 0; i < 6; i++) {
    tree.remove(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}

void descendingRemoval() {
  RedBlackTree<int> tree;
  for (int i = 0; i < 14; i++)
    tree.insert(i);

  for (int i = 13; i >= 0; i--) {
    tree.remove(i);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}

void randomizedRemoval() {
  RedBlackTree<int> tree;
  for (int i = 0; i < 100; i++)
    tree.insert(i);

  for (int i = 0; i < 100; i++) {
    tree.remove((int) random() % 100);
    if (!tree.verify())
      cout << "Error: " << i << endl;
  }
  tree.clear();
}

void mixedInsertionRemoval() {
  RedBlackTree<int> tree;
  for (int i = 0; i < 1000; i++) {
    tree.insert((int) random());
    tree.insert((int) random());
    tree.remove((int) random());
    for (int j = 0; j < 100; j++){
        tree.insert((int) random());
        tree.insert((int) random());
        tree.remove((int) random());
        tree.remove((int) random());
    }

    if (!tree.verify())
        cout << "Error: " << i << endl;
  }
}

int main() {

  ascendingInsertion();
  cout << "Finished ascending insertion." << endl;

  descendingInsertion();
  cout << "Finished descending insertion." << endl;

  randomizedInsertion();
  cout << "Finished randomized insertion." << endl;

  largeInsertion();
  cout << "Finished large insertion." << endl;

  ascendingRemoval();
  cout << "Finished ascending removal." << endl;

  descendingRemoval();
  cout << "Finished descending removal." << endl;

  randomizedRemoval();
  cout << "Finished randomized removal." << endl;

  mixedInsertionRemoval();
  cout << "Finished randomixed insertion and removal" << endl;

  return 0;
}
