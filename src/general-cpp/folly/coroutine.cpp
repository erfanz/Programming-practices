// #include <folly/Portability.h>

// #if FOLLY_HAS_COROUTINES

#include <folly/Optional.h>
#include <folly/ScopeGuard.h>
#include <folly/executors/ManualExecutor.h>
#include <folly/experimental/coro/Baton.h>
#include <folly/experimental/coro/BlockingWait.h>
#include <folly/experimental/coro/Invoke.h>
#include <folly/experimental/coro/Utils.h>
#include <folly/fibers/FiberManager.h>
#include <folly/fibers/FiberManagerMap.h>
// #include <folly/portability/GTest.h>

#include <memory>
#include <type_traits>

folly::coro::Task<int> task42() {
  co_return 42;
}

folly::coro::Task<int> taskSlow43() {
  co_await folly::futures::sleep(std::chrono::seconds{1});
  co_return co_await task42() + 1;
}

int main() {
  CHECK_EQ(43, folly::coro::blockingWait(taskSlow43().scheduleOn(folly::getCPUExecutor().get())));
  return 0;
}
