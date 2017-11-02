#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "useful/mutex.hpp"

useful::spin_lock lock;

useful::barrier b;

void thread_fn() {
  using namespace std::chrono_literals;
  
  auto id = std::this_thread::get_id();

  b.at();

  for (int n = 0; n < 10; n += 1) {
    {
      std::lock_guard<useful::spin_lock> guard{lock};
      std::cout << "Thread " << id << ", n = " << n << '\n';
    }
    std::this_thread::sleep_for(1ms);
  }
}

int main(void) {
  std::vector<std::thread> threads;

  b.waitfor(5);
  
  for (int n = 0; n < 5; n += 1)
    threads.emplace_back(thread_fn);

  for (auto &t : threads)
    t.join();

  return 0;
}
