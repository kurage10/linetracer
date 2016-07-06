#include "TailController.h"
#define GAIN 2.5F


TailController::TailController(ev3api::Motor& tailMotor)
  :mTailMotor(tailMotor),
  mForward(0),
  mAngle(tailMotor.getCount()){}

void TailController::run(){
  int speed = calcDirection();
  //int speed=-1;
  mTailMotor.setPWM(speed);
}

void TailController::init(){
  mTailMotor.reset();
}
int TailController::calcDirection(){
  int tailEnc  = mTailMotor.getCount();        // 左モータ回転角度
  return (tailEnc-mAngle)*0.25;
}
void TailController::setAngle(int angle){
  mAngle=angle;
}
