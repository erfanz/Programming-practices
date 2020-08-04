/*
Tips for Compiling:
gcc-10 

On Clang (Mine is 11.0.3):
clang++ -std=c++2a -stdlib=libc++ simple_coroutine.cpp

On GCC (Mine is 10.2.0):
gcc-10 -std=c++20 -lstdc++ -fcoroutine simple_coroutine.cpp
*/


#ifdef __clang__
#include <experimental/coroutine>
using std::experimental::suspend_never;
#else
#include <coroutine>
using std::suspend_never;
#endif

#include <iostream>

struct simple {
  static inline int x = 0;
  int id = 0;
  simple() : id{ x++ } { std::cout << id << " constructed\n"; }
  simple(simple&&) : id{ x++ } { std::cout << id << " move constructed\n"; }
  ~simple() { std::cout << id << " destructed\n"; }
  
  struct promise_type {
    simple get_return_object() { return {}; }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
    auto initial_suspend() noexcept { return suspend_never{}; }
    auto final_suspend() noexcept { return suspend_never{}; }
  };
};

simple f() { co_return; }

int main() {
  f();
}
