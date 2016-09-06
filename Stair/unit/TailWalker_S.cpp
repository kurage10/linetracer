#include "TailWalker.h"

namespace Stair{
  namespace unit{

    TailWalker::TailWalker(ev3api::Motor& leftWheel,
			   ev3api::Motor& rightWheel,
			   TailController* tailController,
			   LineMonitor* lineMonitor)
      :mLeftWheel(leftWheel),
       mRightWheel(rightWheel),
       mTailController(tailController),
       mLineMonitor(lineMonitor), 
       mSpeed(100) {

    }
    void TailWalker::run(){
      float direction;
      
      mTailController->setAngle(mAngle);
      mTailController->run();

      direction = mLineMonitor->calcDirection();
      
      mLeftWheel.setPWM(mSpeed + (direction/100)*mSpeed);
      mRightWheel.setPWM(mSpeed - (direction/100)*mSpeed);
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
