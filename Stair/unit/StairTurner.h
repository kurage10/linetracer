#ifndef EV3_APP_STAIRTURNER_H_
#define EV3_APP_STAIRTURNER_H_

#include "Motor.h"
#include "TailController.h"
#include "ColorSensor.h"
#include<stdio.h>
namespace Stair{
  namespace unit{

class StairTurner{
public:
  StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController,const ev3api::ColorSensor& colorSensor);
  void run();
  void init();
  bool isDone();
  bool detectCrossLine();
private:
  ev3api::Motor& mLeftWheel;
  ev3api::Motor& mRightWheel;
  TailController* mTailController;
  static const int INITIAL_LIVENESS;
  const ev3api::ColorSensor& mColorSensor;
  bool mIsInitialized;
  bool mOnline;
  int mSpeed;
  int mCount;
  int max;
  int max_liveness;
  int min;
  int min_liveness;
  int timefromstart;
  FILE* file;
};

  }
}

#endif
