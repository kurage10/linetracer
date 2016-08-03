#include "StairTurner.h"

StairTurner::StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController):
  mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  mTailController(tailController),
  initialized(false){

}

void StairTurner::run(){
  if(!initialized){
    mLeftWheel.reset();
    mRightWheel.reset();
    mTailController->setAngle(80);
    initialized=true;
  }
  mTailController->run();
  mLeftWheel.setPWM(-40);
  mRightWheel.setPWM(40);
}
