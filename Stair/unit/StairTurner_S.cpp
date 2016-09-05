#include "StairTurner.h"

namespace Stair{
  namespace unit{

StairTurner::StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController):
  mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  mTailController(tailController),
  mIsInitialized(false), 
  mSpeed(30) {

}

void StairTurner::run(){
  mTailController->run();
  mLeftWheel.setPWM(mSpeed);
  mRightWheel.setPWM(-mSpeed);
}
void StairTurner::init(){
  mLeftWheel.setPWM(0);
  mRightWheel.setPWM(0);
  mTailController->setAngle(85);
  mIsInitialized=false;
}
void StairTurner::setSpinSpeed(int speed){
  mSpeed=speed;
}
int StairTurner::getSpinSpeed(){
  return mSpeed;
}

  }
}
