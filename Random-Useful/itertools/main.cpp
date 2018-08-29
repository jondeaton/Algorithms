
#include "PermIterator.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {

  const string x = "abcde";
  for (const string p : Permutations(x))
    cout << p << endl;

  return 0;
}
