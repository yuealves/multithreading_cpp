#include <atomic>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

#define THREAD_NUM 4

// std::atomic<int> in_stage_one(THREAD_NUM);
int in_stage_one = THREAD_NUM;
std::mutex mtx;
std::condition_variable end_stage_1;
std::condition_variable start_stage_2;

void job() {
  // stage 1

  // non-critical sections, all threads can run simultaneously
  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::unique_lock<std::mutex> lck(mtx); // call mtx.lock() when constructing lck
  // critical sections begin
  std::cout << "stage 1" << std::endl;
  in_stage_one--;
  end_stage_1.notify_one();
  // critical sections end

  // if blocked, lck.unlock() is automatically called.
  // if unblocked, lck.lock() is automatically called.
  start_stage_2.wait(lck, [](){return in_stage_one==0;});

  // stage 2
  // critical sections begin
  std::cout << "stage 2" << std::endl;
  // critical sections end
  lck.unlock();
}

int main() {
  std::thread thds[THREAD_NUM];
  for (int i = 0; i < THREAD_NUM; i++) {
    thds[i] = std::thread(job);
  }

  std::unique_lock <std::mutex> lck(mtx);
  end_stage_1.wait(lck, [](){return in_stage_one==0;});
  lck.unlock();
  start_stage_2.notify_all();
  for (int i = 0; i < THREAD_NUM; i++) {
    thds[i].join();
  }
}
