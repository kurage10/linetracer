#include "TailWalker.h"

namespace Stair{
  namespace unit{

    TailWalker::TailWalker(ev3api::Motor& leftWheel,
			   ev3api::Motor& rightWheel,
			   TailController* tailController)
      :mLeftWheel(leftWheel),
       mRightWheel(rightWheel),
       mTailController(tailController),
       mSpeed(100) {

    }
    void TailWalker::run(){
      mTailController->setAngle(mAngle);
      mTailController->run();
      mLeftWheel.setPWM(mSpeed);
      mRightWheel.setPWM(mSpeed);
    }

    void TailWalker::setSpeed(int speed){
      mSpeed = speed;
    }

    void TailWalker::setAngle(int32_t angle){
      mAngle = angle;
    }
    
    void TailWalker::init(){
      mTailController->setAngle((int32_t)80);
      mIsInitialized = true;
    }

  }
}
