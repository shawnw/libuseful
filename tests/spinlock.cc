#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "useful/mutex.hpp"

useful::spin_lock slock;
useful::ticket_lock tlock;
useful::barrier b;

using namespace std::chrono_literals;

template<class Mutex>
void thread_fn(Mutex *lock) {
  auto id = std::this_thread::get_id();

  b.at();

  for (int n = 0; n < 10; n += 1) {
    {
      std::lock_guard<Mutex> guard{*lock};
      std::cout << "Thread " << id << ", n = " << n << '\n';
    }
    std::this_thread::sleep_for(2ms);
  }
}

template<class Mutex>
void runtest(Mutex *lock) {
  std::vector<std::thread> threads;

  b.waitfor(5);
  for (int n = 0; n < 5; n += 1)
    threads.emplace_back(thread_fn<Mutex>, lock);
  for (auto &t : threads)
    t.join();
}

int main(void) {
  std::cout << "Testing ticket lock...\n";
  runtest(&tlock);

  std::cout << "Testing spin lock...\n";
  runtest(&slock);

  return 0;
}
