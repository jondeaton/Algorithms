#include <gtest/gtest.h>
#include "sive.hpp"
#include <vector>

TEST(Eratosthenes, Simple) {
  int n = 10;
  std::vector<bool> prime(n + 1);
  eratosthenes(n, prime);

  for (int i = 0; i <= 10; i++) {
    if (i == 2 || i == 3 || i == 5 || i == 7)
      EXPECT_TRUE(prime[i]) << i << " is prime";
    else
      EXPECT_FALSE(prime[i]) << i << " is not prime";
  }
}

TEST(Sundaram, Simple) {
  int n = 10;
  std::vector<bool> prime(n + 1);
  sundaram(n, prime);

  for (int i = 0; i <= 10; i++) {
    if (i == 2 || i == 3 || i == 5 || i == 7)
      EXPECT_TRUE(prime[i]) << i << " is prime";
    else
      EXPECT_FALSE(prime[i]) << i << " is not prime";
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


