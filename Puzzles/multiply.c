#include "stdio.h"
#include "stdlib.h"

/*
 * This is a solution to the puzzle:
 * Write a function that multiplies two numbers without
 * using the multiplication primitive.
 */

// naive implementation, takes O(m) time.
int mule(int k, int m) {
  int p = 0;
  while (m--) p += k;
  return p;
}

#define abs(x) (x < 0 ? -x : x)

// Better version, takes O(log min(m, k)) time and O(log min(m, k)) space.
int mul(int k, int m) {
  if (m == -1) return -k;
  if (m == 0) return 0;
  if (m == 1) return k;
  if (abs(k) < abs(m)) {
    int tmp = m;
    m = k;
    k = tmp;
  }
  int p = mul(k, m / 2);
  if (m % 2)
    return p + p + (m < 0 ? -k : k);
  else 
    return p + p;
}

int main(int argc, char *argv[]) {
  int k = atoi(argv[1]);
  int m = atoi(argv[2]);
  int p = mul(k, m);

  printf("%d x %d = %d (answer: %d)\n", k, m, p, k * m);
  printf("%s\n", p == m * k ? "correct." : "wrong.");
  return 0;
}
