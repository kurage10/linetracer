
#ifndef EV3_UNIT_TAILWALKER_H_
#define EV3_UNIT_TAILWALKER_H_

#include "Motor.h"
#include "TailController.h"
#include <stdio.h>

class TailWalker {
public:
  TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController);

  void init();
  void run();

private:
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    TailController* mTailController;
    bool mIsInitialized;
    FILE* file;
};

#endif  // EV3_UNIT_BALANCINGWALKER_H_
