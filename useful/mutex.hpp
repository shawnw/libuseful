/*
The MIT License (MIT)

Copyright (c) 2016 shawnw

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef USEFUL_MUTEX_HPP
#define USEFUL_MUTEX_HPP

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

namespace useful {

  /* Basic thread barrier. Initialize with a number N, and threads that wait on the barrier
   * will block until N threads are waiting. Useful for environments without the concurrency TS. */
  class barrier {
  private:
    int count;
    std::mutex m;
    std::condition_variable cond;

  public:
    explicit barrier(int c = -1) : count(c), m(), cond() {}
    barrier(const barrier &) = delete;
    barrier(const barrier &&) = delete;
    barrier& operator=(const barrier &) = delete;
    barrier& operator=(const barrier &&) = delete;
    
    // Returns false if the barrier has already been passed by other threads.
    bool at() {
      std::unique_lock<std::mutex> guard(m);

      if (count > 0) {
        count -= 1;
        if (count == 0) {
          cond.notify_all();
        } else {
          cond.wait(guard, [this]{ return count <= 0; });
          count = -1;
        }
        return true;
      } else {
        return false;
      }
    }

    // Set the number of threads the barrier should wait for. Can't be used on a barrier
    // currently being waited for.
    void waitfor(int c) {
      std::lock_guard<std::mutex> guard(m);
      if (count > 0)
        throw std::logic_error("Attempt to reset a currently active barrier.");
      count = c;
    }
  };

  /* Spin lock using std::atomic_flag, usable with std::lock_guard
     etc. Satisfies Mutex concept */
  class spin_lock {
  private:
    std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
  public:
    spin_lock(const spin_lock &) = delete;
    spin_lock(const spin_lock &&) = delete;
    spin_lock& operator=(const spin_lock &) = delete;
    spin_lock& operator=(const spin_lock &&) = delete;
    
    void lock() {
      while (lock_.test_and_set(std::memory_order_acquire))
        ;
    }
    bool try_lock() {
      return !lock_.test_and_set(std::memory_order_acquire);
    }    
    void unlock() {
      lock_.clear(std::memory_order_release);
    }
  };

  /* Ticket lock, see https://en.wikipedia.org/wiki/Ticket_lock
     Satisfies BasicLockable concept. */
  class ticket_lock {
  private:
    using itype = unsigned int;
    std::atomic<itype> current_ticket{0};
    std::atomic<itype> next_ticket{0};
  public:
    ticket_lock(const ticket_lock &) = delete;
    ticket_lock(const ticket_lock &&) = delete;
    ticket_lock& operator=(const ticket_lock &) = delete;
    ticket_lock& operator=(const ticket_lock &&) = delete;
    
    void lock() {
      itype this_ticket = next_ticket.fetch_add(1, std::memory_order_relaxed);
      while (current_ticket.load(std::memory_order_acquire) != this_ticket)
        ;
    }
    void unlock() {
      current_ticket.fetch_add(1, std::memory_order_release);
    }
  };  
};


#endif
