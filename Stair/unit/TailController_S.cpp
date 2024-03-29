#include "TailController.h"

namespace Stair{
  namespace unit{

TailController::TailController(ev3api::Motor& tailMotor)
  :mTailMotor(tailMotor),
  mAngle(3){}

void TailController::run(){
  int speed = calcDirection();
  mTailMotor.setPWM(speed);
}

void TailController::init(){
  mTailMotor.reset();
  mTailMotor.setBrake(true);
}
int TailController::calcDirection(){
  int diff=(mTailMotor.getCount()-mAngle)*0.25;
  if(diff > 100) return -100;
  else if(diff < -100)return 100;
  else return -diff;
}
void TailController::setAngle(int32_t angle){
  mAngle=angle;
}

int32_t TailController::getAngle(){
  return mTailMotor.getCount();
}

  }
}
