//
// Created by jiacheng3 on 2018/3/26.
//

#ifndef JTHREAD_TASK_GROUP_H
#define JTHREAD_TASK_GROUP_H

#include "task.h"
#include <queue>

namespace jthread {

class TaskGroup {
 public:

  void AddTask();

 private:
  std::queue<std::shared_ptr<Task>> local_task_;
  std::queue<std::shared_ptr<Task>> remote_task_;
};

TaskGroup thread_local _group;

} // namespace jthread

#endif //JTHREAD_TASK_GROUP_H
