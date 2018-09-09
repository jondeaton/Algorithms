#include <benchmark/benchmark.h>
#include "sive.hpp"
#include <vector>

namespace {

  static void bench_eratosthenes(benchmark::State &state) {
    int n = state.range(0);
    std::vector<bool> prime(n + 1);
    for (auto _ : state) {
      eratosthenes<int>(n, prime);
    }
  }
  BENCHMARK(bench_eratosthenes)->Range(8, 8 << 12);

  static void bench_sundaram(benchmark::State &state) {
    int n = state.range(0);
    std::vector<bool> prime(n + 1);
    for (auto _ : state) {
      sundaram<int>(n, prime);
    }
  }
  BENCHMARK(bench_sundaram)->Range(8, 8 << 10);

}

BENCHMARK_MAIN();

