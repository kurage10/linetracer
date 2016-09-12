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
       mSpeed(20),
       mDoTrace(true) {

    }
    void TailWalker::run(){
      float direction;
      
      mTailController->setAngle(mAngle);
      mTailController->run();

      if(mDoTrace){
	direction = mLineMonitor->calcDirection(Stair::unit::LineMonitor::TailWalking);
      }else{
	direction = 0;
      }
      
      mLeftWheel.setPWM(mSpeed + (direction/100)*mSpeed);
      mRightWheel.setPWM(mSpeed - (direction/100)*mSpeed);
    }

    void TailWalker::setSpeed(int speed){
      mSpeed = speed;
    }

    void TailWalker::setAngle(int32_t angle){
      mAngle = angle;
    }

    void TailWalker::setDoTrace(bool doTrace){
      mDoTrace = doTrace;
    }
    
    void TailWalker::init(){
      mTailController->setAngle((int32_t)80);
      mIsInitialized = true;
    }

  }
}
