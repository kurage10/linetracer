#ifndef EV3_APP_STAIRTURNER_H_
#define EV3_APP_STAIRTURNER_H_

#include "Motor.h"
#include "TailController.h"
class StairTurner{
public:
  StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController);
  void run();
  void init();
private:
  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
  TailController* mTailController;
  bool mIsInitialized;
  int timefromstart;
};



#endif
