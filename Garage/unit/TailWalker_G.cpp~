#include "./TailWalker.h"

namespace Garage{
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
       mIsInitialized(false),
       mAngle(90),
       mDirection(),
       mDoTrace(false),
       mStartMeasuringDistance(){
    }
    
    void TailWalker::run(){
      float direction = mLineMonitor->calcDirection();
      
      //mTailController->setAngle(mAngle);
      mTailController->run();

      if(!mDoTrace){
	direction = mDirection;
      }
      
      mLeftWheel.setPWM(mSpeed + (direction/100)*mSpeed*2);
      mRightWheel.setPWM(mSpeed - (direction/100)*mSpeed*2);
    }

    void TailWalker::setSpeed(int speed){
      mSpeed = speed;
    }

    void TailWalker::setAngle(int32_t angle){
      mAngle = angle;
    }

    void TailWalker::setDirection(float direction){
      mDoTrace = false;
      if(direction > 100){
	mDirection = 100;
      }else if(direction < -100){
	mDirection = -100;
      }else{
	mDirection = direction;
      }
    }

    void TailWalker::init(){
      if(!mIsInitialized){
	mTailController->init();
      }
      mTailController->setAngle(mAngle);
      mIsInitialized = true;
      mDoTrace = true;
      mStartMeasuringDistance = mLeftWheel.getCount();
    }

    int TailWalker::getDistance(){
      return mLeftWheel.getCount() - mStartMeasuringDistance;
    }

  }
}
