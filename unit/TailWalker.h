#ifndef EV3_APP_TAILWALKER_H_
#define EV3_APP_TAILWALKER_H_

#include "TailController.h"
#include "Motor.h"

class TailWalker{
public:
  TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController);
  void run();
  void init();
private:
  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
  TailController* mTailController;
  bool mIsInitialized;
};
#endif
