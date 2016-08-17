#include "StairTurner.h"

StairTurner::StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController):
  mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  mTailController(tailController),
  mIsInitialized(false),
  timefromstart(0){

}

void StairTurner::run(){
  if(!mIsInitialized){
    mLeftWheel.setPWM(10);
    mRightWheel.setPWM(10);
    //mTailController->setAngle(80);
    mIsInitialized=true;
  }
  int tailangle=85+timefromstart/200;
  if(tailangle > 93) tailangle=93;
  mTailController->setAngle(tailangle);
  mTailController->run();
  //mTailController->setAngle(80);
  //mTailController->run();
  timefromstart=timefromstart+1;
  if(timefromstart > 200){
    int speed=(980-timefromstart)/20;
    if(speed<0)speed=0;
    mLeftWheel.setPWM(-speed);
    mRightWheel.setPWM(speed);
  }
  else if(timefromstart > 100){
    mLeftWheel.setPWM(0);
    mRightWheel.setPWM(0);
  }

}
void StairTurner::init(){
  mLeftWheel.setPWM(0);
  mRightWheel.setPWM(0);
  timefromstart=0;
  mIsInitialized=false;
}
