
#ifndef EV3_UNIT_TAILWALKER_H_
#define EV3_UNIT_TAILWALKER_H_

#include "Motor.h"
#include "TailController.h"
#include <stdio.h>

namespace Stair{
  namespace unit{

class TailWalker {
public:
  TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController);

  void init();
  void run();
  void setSpeed(int speed);
  void setAngle(int32_t angle);
  
private:
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    TailController* mTailController;
    int mSpeed;
    bool mIsInitialized;
    int32_t mAngle;
    FILE* file;
};

  }
}
 
#endif  // EV3_UNIT_BALANCINGWALKER_H_
