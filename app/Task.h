
#ifndef EV3_APP_TASK_H_
#define EV3_APP_TASK_H_

namespace app{
  class Task{
  public:
      virtual bool isDone() = 0;
      virtual void run() = 0;
      virtual ~Task(){};
  };
}

#endif
