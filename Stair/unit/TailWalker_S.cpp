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
       mDoTrace(true),
       mDirection() {

    }
    void TailWalker::run(){
      float direction = mDirection;
      
      mTailController->setAngle(mAngle);
      mTailController->run();

      if(mDoTrace){
	direction = mLineMonitor->calcDirection(Stair::unit::LineMonitor::TailWalking);
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

    void TailWalker::setDirection(int direction){
      mDirection = direction;
    }
    
    void TailWalker::init(){
      mTailController->setAngle((int32_t)80);
      mIsInitialized = true;
    }

    bool TailWalker::onLine(){
      return mLineMonitor->onLine();
    }

    void TailWalker::resetOnLine(){
      mLineMonitor->resetOnLine();
    }

  }
}
