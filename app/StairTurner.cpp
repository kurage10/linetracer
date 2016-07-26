#include "StairTurner.h"

StairTurner::StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel):
  mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  initialized(false){

}

void StairTurner::run(){
  if(!initialized){
    mLeftWheel.setPWM(0);
    mRightWheel.setPWM(0);
    initialized=true;
  }
  mLeftWheel.setPWM(-20);
  mRightWheel.setPWM(20);
}
