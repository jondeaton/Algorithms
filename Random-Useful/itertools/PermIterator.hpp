#include <algorithm>
#include <iterator>

template <typename Integer>
Integer factorial(const Integer k) {
  Integer f(1);
  for (Integer i = Integer(2); i < k; ++i)
    f *= i;
  return f;
}

/*
 * Rearranges the elements of [begin, end) to be the n'th permutation
 * of them lexicographically, as given by the comparator
 */
template <typename RandomIterator, typename Integer, typename Comparator>
void nthPermutation(RandomIterator begin, RandomIterator end, Integer n, Comparator cmp) {
  std::sort(begin, end, cmp);  // sort the elements lexicographically

  const Integer k(end - begin);
  const Integer radix = factorial(k);

  for (Integer i = 0; i < k; i++) {
    Integer digit = n / radix;
    std::rotate(begin, begin + digit, begin + digit + 1);
    ++begin;
    n %= radix;
    if (i + 1 != k)
      radix /= (k - i - 1);
  }
}



