/*
 * File: test-RedBlackTree.cpp
 * ------------------
 * For testing the Red Black tree
 */

#include "RedBlackTree.h"
#include <random>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  RedBlackTree<int> tree;

  for (int i = 0; i < 6; i++) {
    tree.insert(i);
    if (!tree.verify())
        cout << "Error: " << i << endl;
  }

  tree.clear();
  return 1;

  for (int i = 0; i < 500; i++){
    tree.insert(i);
    if (!tree.verify())
        cout << "error" << endl;
  }

  for (int i = 1; i < 1000; i++) {
       tree.insert(random() % i);
       tree.insert(random() % i);
       tree.remove(random() % i);
       if (!tree.verify())
          cout << "error" << endl;
  }

  
  for (int i = 1; i < 500; i++) {
      tree.remove(random() % i);
      if (!tree.verify())
        cout << "error" << endl;
  }

  tree.clear();

  int numel = 1000000;
  for (int i = 1; i <= numel; i++)
      tree.insert(i);
 
  cout << "Height after adding " << numel << " elements: " << tree.height() << endl;

  if (!tree.verify()) cout << "Corrupted." << endl;

  for (int i = 1; i <= numel; i++)
      if (i % 2) tree.remove(i);

  for (int i = 1; i <= numel; i++) {
      if (i % 2 && tree.contains(i)) cout << "Error: " << i << endl;
      if (!i % 2 && !tree.contains(i)) cout << "Error: " << i << endl;
  }

}
