#include "TailController.h"

TailController::TailController(ev3api::Motor& tailMotor)
  :mTailMotor(tailMotor),
  mAngle(3){}

void TailController::run(){
  float speed = calcDirection();
  mTailMotor.setPWM(speed);
}

void TailController::init(){
  mTailMotor.reset();
}
int TailController::calcDirection(){
  int diff=mTailMotor.getCount()-mAngle;
  if(diff==0)return 0;
  else if(diff<0) return 1;
  else return -1;
}
void TailController::setAngle(int angle){
  mAngle=angle;
}