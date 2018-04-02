//
// Created by jiacheng3 on 2018/3/26.
//

#ifndef JTHREAD_TASK_CONTROL_H
#define JTHREAD_TASK_CONTROL_H

#include "task_group.h"

#include <map>
#include <memory>

#define MAX_PTHREAD_NUM 1024

namespace jthread {

class TaskControl {
 public:

  void Init();

 private:
  TaskGroup *group_ptr_[MAX_PTHREAD_NUM];
};

} //namespace jthread

#endif //JTHREAD_TASK_CONTROL_H
