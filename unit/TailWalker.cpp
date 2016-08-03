#include "TailWalker.h"

TailWalker::TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController)
  :mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  mTailController(tailController),
  mIsInitialized(false){

}
void TailWalker::run(){
  //mTailController->setAngle(75);
  if(!mIsInitialized){
    init();
    mIsInitialized=true;
  }
  //mTailController->run();
  mLeftWheel.setPWM((int32_t)60);
  mRightWheel.setPWM((int32_t)60);
}
void TailWalker::init(){
  mTailController->init();
  mTailController->setAngle((int32_t)75);
  //mLeftWheel.reset();
  //mRightWheel.reset();
  mIsInitialized = true;
}
