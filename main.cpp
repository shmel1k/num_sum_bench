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

constexpr uint64_t VEC_SIZE = 10000000;
constexpr uint64_t TARGET = VEC_SIZE + 1;

std::vector<uint64_t> initializeTest() {
  std::vector<uint64_t> vec;
  vec.reserve(VEC_SIZE + 1);
  for (int i = 0; i < VEC_SIZE; ++i) {
    vec.push_back(i);
  }
  return vec;
}

bool barrierSearch(const std::vector<uint64_t>& vec, uint64_t target) {
  size_t i = 0;
  for (; vec[i] != target; ++i) {
  }
  return i < vec.size();
}

static void BM_barrierSearch(benchmark::State& state) {
  auto vec = initializeTest();
  vec.push_back(TARGET);
  for (auto _ : state) {
    barrierSearch(vec, TARGET);
  }
}

BENCHMARK(BM_barrierSearch);

bool linearSearch(const std::vector<uint64_t>& vec, uint64_t target) {
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i] == target) {
      return true;
    }
  }
  return false;
}

static void BM_linearSearch(benchmark::State& state) {
    auto vec = initializeTest();
    for (auto _ : state) {
        linearSearch(vec, TARGET);
    }
}

BENCHMARK(BM_linearSearch);

BENCHMARK_MAIN();

// int main(int argc, char** argv) {
//   assert(sumWithConversion(422) == 8);
//   assert(sumWithoutConversion(422) == 8);
//   return 0;
// }
