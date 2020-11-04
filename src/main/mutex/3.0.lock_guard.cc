// A demo for mutex and lock_guard
// By Ari Saif
// Run this using one of the following methods:
//  1. With bazel:
//      bazel run --cxxopt='-std=c++17' \
//      src/main/mutex:{THIS_FILE_NAME_WITHOUT_EXTENSION}
//  2. With g++:
//      g++ -std=c++17 -lpthread \
//      src/main/mutex/{THIS_FILE_NAME}.cc  -I ./
#include <cassert>
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

std::mutex g_mutex;
unsigned long g_counter;

void Incrementer() {
  for (size_t i = 0; i < 100; i++) {
    // Using lock_guard wrapper is better than directly using mutex, as
    // lock_guard will automatically unlock the mutex when it is out of the
    // scope. If an exception occurs, directly using mutex may not release the
    // lock (the line of "mtx.unlock()" will not be executed).
    std::lock_guard<std::mutex> guard(g_mutex);
    g_counter++;
  }
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < 100; i++) {
    threads.push_back(std::thread(Incrementer));
  }

  for (std::thread &t : threads) {
    t.join();
  }
  std::cout << "g_counter: " << g_counter << std::endl;

  assert(g_counter == 100 * 100);
}
