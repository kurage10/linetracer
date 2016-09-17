#ifndef EV3_GARAGE_APP_STOPPER_H_
#define EV3_GARAGE_APP_STOPPER_H_

#include "Motor.h"
#include "Task.h"

using app::Task;

namespace Garage{
  namespace app{

    class Stopper : public Task{      
    public:
      
      Stopper(ev3api::Motor& leftWheel,
	      ev3api::Motor& rightWheel,
	      ev3api::Motor& tailMotor
	      );

      ~Stopper();
      
      void run();
      bool isDone();
      void init();
      void reset();
      
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
    
  }
}

#endif  // EV3_UNIT_STOPPER_H_
