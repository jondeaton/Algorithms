/*
 * File: test-AVL.cpp
 * ------------------
 * For testing the AVL tree
 */

#include "AVL-Tree.h"
#include <random>

int main() {
  AVLTree<int> tree;
  tree.insert(5);

  for (int i = 0; i < 1000; i++)
    tree.insert(i);

  for (int i = 0; i < 500; i++)
    tree.insert(i);

//  tree.clear();

}