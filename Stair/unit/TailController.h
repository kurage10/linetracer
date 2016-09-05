#ifndef EV3_APP_TAILCONTROLLER_H_
#define EV3_APP_TAILCONTROLLER_H_
#include "Motor.h"

namespace Stair{
  namespace unit{

class TailController{
private:
  ev3api::Motor& mTailMotor;
  int32_t mAngle; //expected value of Motor
public:
  TailController(ev3api::Motor& tailController);
  int calcDirection();
  void init();
  void run();
  void setAngle(int32_t angle);
  int32_t getAngle();
};

  }
}

#endif
