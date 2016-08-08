#ifndef EV3_APP_TAILWALKER_H_
#define EV3_APP_TAILWALKER_H_

#include "TailController.h"
#include "Motor.h"
#include "BalancingWalker.h"

class TailWalker{
public:
  TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,ev3api::Motor& tailMotor,TailController* tailController,BalancingWalker* balancingWalker);
  void run();
  void init();
private:
  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
  ev3api::Motor& mTailMotor;
  TailController* mTailController;
  BalancingWalker* mBalancingWalker;
  bool mIsInitialized;
};
#endif
