#include "TailWalker.h"


TailWalker::TailWalker(ev3api::Motor& leftWheel,
                       ev3api::Motor& rightWheel,
                       TailController* tailController)
     :mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mTailController(tailController){

}
void TailWalker::run(){

  mTailController->setAngle((int32_t)80);
  mTailController->run();
  mLeftWheel.setPWM(100);
  mRightWheel.setPWM(100);
}
void TailWalker::init(){
  mTailController->setAngle((int32_t)80);
  mIsInitialized = true;
}
