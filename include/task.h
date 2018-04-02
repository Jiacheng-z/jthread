//
// Created by jiacheng3 on 2018/3/26.
//

#ifndef JTHREAD_TASK_H
#define JTHREAD_TASK_H

#include <boost/context/all.hpp>
#include <functional>
#include <memory>
#include <type_traits>

namespace ctx = boost::context;

namespace jthread {

//template<typename Stack = ctx::fixedsize_stack>
template<typename Stack = ctx::protected_fixedsize_stack>
class Task : public std::enable_shared_from_this<Task<Stack>> {
 public:
  Task() = default;

  template<typename _F, typename... _ARGS>
  auto SetTask(_F &&fn, _ARGS &&... args) -> std::future<typename std::result_of<_F(_ARGS...)>::type> {

      using return_type = typename std::result_of<_F(_ARGS...)>::type;

      auto task = std::make_shared<std::packaged_task<return_type()>>(
          std::bind(std::forward<_F>(fn), std::forward<_ARGS>(args)...)
      );

      fn_ = [this, task] { (*task)(); };

      return task->get_future();
  };

  void Execute() {
      c_ = ctx::callcc(std::allocator_arg, stack_, [&](ctx::continuation &&sink) {
        c_ = std::move(sink);
        fn_();
        return std::move(c_);
      });
  }

 private:
  Stack stack_;
  ctx::continuation c_;
  std::function<void()> fn_;
};

} // namespace jthread

#endif //JTHREAD_TASK_H
