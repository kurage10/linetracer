#ifndef EV3_APP_TAILCONTROLLER_H_
#define EV3_APP_TAILCONTROLLER_H_
#include "Motor.h"


class TailController{
private:
  ev3api::Motor& mTailMotor;
  int mAngle; //expected value of Motor
  int mForward; //the speed of Motor
public:
  TailController(ev3api::Motor& tailController);
  int calcDirection();
  void init();
  void run();
  void setAngle(int angle);
};



#endif
