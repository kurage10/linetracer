#include "Stopper.h"

const int stopAngle = 700;
const int tailAngle = 80;

Stopper::Stopper(	ev3api::Motor& leftWheel,
					ev3api::Motor& rightWheel,
					ev3api::Motor& tailMotor
				)
	: mLeftWheel(leftWheel),
	  mRightWheel(rightWheel),
	  mTailMotor(tailMotor){
		  bIsStopping = false;
		  bIsTailDown = false;
}

void Stopper::activate(){
	bIsStopping = true;
	mLeftWheel.setCount(0);
	mRightWheel.setCount(0);
	mTailMotor.setPWM(10);
}

void Stopper::update(){
	if(bIsStopping)
	{
		if(mTailMotor.getCount() >= tailAngle)
		{
			mTailMotor.setPWM(0);
			bIsTailDown = true;
		}
		
		if(bIsTailDown)
		{
			updatePWM();
		
			mLeftWheel.setPWM(currentPWM);
			mRightWheel.setPWM(currentPWM);
		}
	}
}

bool Stopper::isEndReached(){
	return mLeftWheel.getCount() >= stopAngle;
}

void Stopper::updatePWM(){
	currentPWM = 25 - (5 * (mLeftWheel.getCount()/140));
}