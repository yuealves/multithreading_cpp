#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include "utility.h"

// A demo for creating a vector containing 100 threads
// Run this using one of the following methods:
//  1. With cmake: mkdir build && cd build; cmake ..; make
//  2. With plain g++: g++ -std=c++17 -pthread src/main/1.vector_of_threads_main.cc  -I ./src/lib
int main() {
  const int number_of_threads = 100;
  uint64_t number_of_elements = 1000* 1000;
  uint64_t step = number_of_elements / number_of_threads;
  std::vector<std::thread> threads;
  std::vector<uint64_t> partial_sums(number_of_threads);

  for (uint64_t i = 0; i < number_of_threads; i++) {
    threads.push_back(std::thread(AccumulateRange, std::ref(partial_sums[i]),
                                  i * step, (i + 1) * step));
  }

  for (std::thread &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }

  uint64_t total =
      std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));

  PrintVector(partial_sums);
  std::cout << "total: " << total << std::endl;

  return 0;
}