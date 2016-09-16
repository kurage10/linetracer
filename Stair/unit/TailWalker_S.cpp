#include "TailWalker.h"

namespace Stair{
  namespace unit{

TailWalker::TailWalker(ev3api::Motor& leftWheel,
                       ev3api::Motor& rightWheel,
                       TailController* tailController)
     :mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mTailController(tailController){

}
void TailWalker::run(){

  mTailController->setAngle((int32_t)85);
  mTailController->run();
  mLeftWheel.setPWM(-10);
  mRightWheel.setPWM(-10);
}
void TailWalker::init(){
  mTailController->setAngle((int32_t)85);
  mLeftWheel.setPWM(0);
  mRightWheel.setPWM(0);
  mIsInitialized = true;
}

  }
}
