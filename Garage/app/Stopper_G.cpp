#include "Stopper.h"

namespace Garage{
  namespace app{
    
    const int stopAngle = 700;
    const int tailAngle = 80;
    
    Stopper::Stopper(ev3api::Motor& leftWheel,
		     ev3api::Motor& rightWheel, 
		     ev3api::Motor& tailMotor
		     )
      : mLeftWheel(leftWheel),
	mRightWheel(rightWheel),
	mTailMotor(tailMotor){
      bIsInitialized = false;
      bIsTailDown = false;
    }
    
    void Stopper::init(){
      mLeftWheel.setCount(0);
      mRightWheel.setCount(0);
    }
    
    void Stopper::run(){
      
      if(!bIsInitialized)
	init();
      
      if(mTailMotor.getCount() >= tailAngle)
	{
	  mTailMotor.setPWM(0);
	  bIsTailDown = true;
	}
      else
	{
	  mTailMotor.setPWM(10);
	}
      
      if(bIsTailDown)
	{
	  updatePWM();
	  
	  mLeftWheel.setPWM(currentPWM);
	  mRightWheel.setPWM(currentPWM);
	}
    }
    
    bool Stopper::isEndReached(){
      return mLeftWheel.getCount() >= stopAngle;
    }
    
    void Stopper::updatePWM(){
      currentPWM = 25 - (5 * (mLeftWheel.getCount()/140));
    }

    bool Stopper::isDone(){
      return false;
    }

    Stopper::~Stopper(){
      delete &bIsInitialized;
      delete &bIsTailDown;
    }
  }
}
