#include <assert.h>
#include <iostream>
#include "benchmark/include/benchmark/benchmark.h"

int sumWithConversion(uint64_t n) {
  std::string sumStr = std::to_string(n);
  int sum = 0;
  for (int i = sumStr.length() - 1; i >= 0; --i) {
    sum += (sumStr.at(i) - '0');
  }
  return sum;
}

static void BM_sumWithConversion(benchmark::State& state) {
  for (auto _ : state) {
    sumWithConversion(1844674407370955161);
  }
}

BENCHMARK(BM_sumWithConversion);

int sumWithoutConversion(uint64_t n) {
  int sum = 0;
  for (; n > 0;) {
    sum += n % 10;
    n = n / 10;
  }
  return sum;
}

static void BM_sumWithoutConversion(benchmark::State& state) {
  for (auto _ : state) {
    sumWithoutConversion(1844674407370955161);
  }
}

BENCHMARK(BM_sumWithoutConversion);

BENCHMARK_MAIN();

// int main(int argc, char** argv) {
//   assert(sumWithConversion(422) == 8);
//   assert(sumWithoutConversion(422) == 8);
//   return 0;
// }
