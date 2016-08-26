#ifndef EV3_UNIT_STOPPER_H_
#define EV3_UNIT_STOPPER_H_

#include "Motor.h"

class Stopper	{

public:
	
	Stopper(	  ev3api::Motor& leftWheel,
				  ev3api::Motor& rightWheel,
				  ev3api::Motor& tailMotor
			);
	
	void run();
	void init();
	
private:
 	
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
	ev3api::Motor& mTailMotor;
	
	void stop();
	
	int currentPWM;
	
	void updatePWM();
	bool isEndReached();
	bool bIsInitialized;
	bool bIsTailDown;
};

#endif  // EV3_UNIT_STOPPER_H_