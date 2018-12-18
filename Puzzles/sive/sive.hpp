
#include <vector>

template <typename T>
void eratosthenes(T n, std::vector<bool> &prime) {

  /* In C++ vector<bool> is optimized to be a dynamically
   * sized bitset. Thus we are only using one bit per number. */
  for (T i = 0; i <= n; i++) prime[i] = true;
  prime[0] = false;
  prime[1] = false; 
  /* Only need to go up to the square root of n. */
  for (int i = 2; i * i < n; ++i) {
    if (prime[i]) {
      // can start at square of i for similar reason
      for (int j = i * i; j <= n; j += i)
        prime[j] = false;
    }
  }
}

#include <iostream>

// any odd number which is not of the form (2i + 1)(2j + 1) = 4ij + 2i + 2j + 1
// is a prime number. This is because any odd number that is not the product
// of two other odd numbers is prime.
template <typename T>
void sundaram(T n, std::vector<bool> &prime) {
  int N = n / 2;

  std::vector<bool> sive(N + 1);
  for (T i = 0; i <= N; ++i)
    sive[i] = true;

  // for all i + j + 2ij <= N
  for (T i = 1; i <= N / 4; ++i) {
    for (T j = i; j <= (N - 1) / (2 * i + 1); ++j)
      sive[i + j + 2 * i * j] = false;
  }

  for (T i = 0; i <= n; i++) prime[i] = false;
  for (T i = 0; i <= N; i++)
    if (sive[i]) prime[2 * i + 1] = true;

  prime[1] = false;
  prime[2] = true; // don't forget about all those even primes
}





