#include "Stopper.h"

const int stopAngle = 700;
const int tailAngle = 80;

Stopper::Stopper(	ev3api::Motor& leftWheel,
					ev3api::Motor& rightWheel,
					ev3api::Motor& tailMotor
				)
	: mLeftWheel(leftWheel),
	  mRightWheel(rightWheel),
	  mTailMotor(tailMotor)
{
		  bIsInitialized = false;
		  bIsTailDown = false;
}

void Stopper::init(){
	leftAngle = mLeftWheel.getCount();
	rightAngle = mRightWheel.getCount();
	currentPWM = 25;
}

void Stopper::run(){
	
	if(!bIsInitialized)
		init();
	
	if(mTailMotor.getCount() >= tailAngle)
	{
		mTailMotor.setPWM(0);
		bIsTailDown = true;
		ev3_led_set_color(LED_ORANGE);
	}
	else
	{	
		mTailMotor.setPWM(20);
		ev3_led_set_color(LED_GREEN);
		mLeftWheel.setPWM(50);
		mRightWheel.setPWM(50);
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