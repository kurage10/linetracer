#include "TailController.h"
#include <math.h>
#define GAIN 2.5F


TailController::TailController(ev3api::Motor& tailMotor)
  :mTailMotor(tailMotor),
  mAngle(3){}

void TailController::run(){
  float speed = calcDirection();
  //int speed=-1;
  mTailMotor.setPWM(speed);
}

void TailController::init(){
  mTailMotor.reset();
}
int TailController::calcDirection(){
  int diff=mTailMotor.getCount()-mAngle;
  if(diff==0)return 0;
  else if(diff<0) return -1;
  else return 1;
}
void TailController::setAngle(int angle){
  mAngle=angle;
}
