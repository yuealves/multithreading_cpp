// A demo of producer/Consumer using C++ conditional variable
// By Ari Saif
// Run this using one of the following methods:
//  1. With bazel:
//      bazel run --cxxopt='-std=c++17' \
//      src/main/conditional_variable:{THIS_FILE_NAME_WITHOUT_EXTENSION}
//  2. With g++:
//      g++ -std=c++17 -lpthread \
//      src/main/conditional_variable/{THIS_FILE_NAME}.cc  -I ./
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>  // For std::unique_lock
#include <random>
#include <thread>
#include <vector>
#include <functional>

// Create a function to generate a random value between 0 and 10
auto GenRandomValue = std::bind(std::uniform_int_distribution<>(0, 10),
                                std::default_random_engine());

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;
int g_data = 0;
void ConsumeData(int& data) {}

void Consumer() {
  int data = 0;
  for (int i = 0; i < 100; i++) {
    std::unique_lock<std::mutex> ul(g_mutex);

    // g_cv.wait会阻塞当前线程，并调用ul.unlock()释放锁使得其它被阻塞在锁竞争上的线程得以继续执行
    // g_cv.wait阻塞当前线程会一直持续到其它线程notify_*唤醒该线程，唤醒时会自动调用ul.lock()，
    // 使得其他使用ul锁的线程的对应critical section阻塞

    // 由于线程有可能被各种操作系统意外的情况唤醒，故而在被唤醒时还需要检查flag是否ready，故而一个
    // 保险的写法是：
    // while(!g_ready){
    //   g_cv.wait(ul);
    // }
    // 下述一行与上面的while循环是等效的
    g_cv.wait(ul, []() { return g_ready; });

    // Sample data
    data = g_data;
    std::cout << "data: " << data << std::endl;
    g_ready = false;
    ul.unlock();
    g_cv.notify_one();
    ConsumeData(data);
    ul.lock();
  }
}

void Producer() {
  for (int i = 0; i < 100; i++) {
    std::unique_lock<std::mutex> ul(g_mutex);

    // Produce data
    g_data = GenRandomValue();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    g_ready = true;
    ul.unlock();
    g_cv.notify_one();
    ul.lock();
    g_cv.wait(ul, []() { return g_ready == false; });
  }
}

int main() {
  std::thread t1(Consumer);
  std::thread t2(Producer);
  t1.join();
  t2.join();
  return 0;
}