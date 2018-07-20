/*
 * File: test-AVL.cpp
 * ------------------
 * For testing the AVL tree
 */

#include "AVL-Tree.h"
#include <random>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  AVLTree<int> tree;
  tree.insert(5);

  for (int i = 0; i < 1000; i++) {
    tree.insert(i);
    if (!tree.verify())
        cout << "error" << endl;
  }

  for (int i = 0; i < 500; i++){
    tree.insert(i);
    if (!tree.verify())
        cout << "error" << endl;
  }
  
  tree.clear();


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
