#include "TailController.h"

namespace LineTrace{
  namespace unit{

TailController::TailController(ev3api::Motor& tailMotor)
  :mTailMotor(tailMotor),
   mAngle(3){}

void TailController::run(){
  float speed = calcDirection();
  mTailMotor.setPWM(speed);
}

void TailController::init(){
  ev3api::Clock mClock = ev3api::Clock();
  
  mTailMotor.setPWM(-100);
  mClock.sleep(1000);
  mTailMotor.setPWM(0);
  mTailMotor.reset();
}
int TailController::calcDirection(){
  int diff=mTailMotor.getCount()-mAngle;
  if(diff==0)return 0;
  else return -diff*0.20;
}
void TailController::setAngle(int32_t angle){
  mAngle=angle;
}

int32_t TailController::getAngle(){
  return mTailMotor.getCount();
}

  }
}
