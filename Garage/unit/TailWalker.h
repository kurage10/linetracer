#ifndef EV3_GARAGE_UNIT_TAILWALKER_H_
#define EV3_GARAGE_UNIT_TAILWALKER_H_

#include "Motor.h"
#include "./TailController.h"
#include "./LineMonitor.h"

namespace Garage{
  namespace unit{

    class TailWalker {
    public:
      TailWalker(ev3api::Motor& leftWheel,
		 ev3api::Motor& rightWheel,
		 TailController* tailController,
		 LineMonitor* lineMonitor);

      void init();
      void run();
      void setSpeed(int speed);
      void setAngle(int32_t angle);
      void setDirection(float direction);
      int  getDistance();
      
    private:
      ev3api::Motor& mLeftWheel;
      ev3api::Motor& mRightWheel;
      TailController* mTailController;
      LineMonitor* mLineMonitor;
      int mSpeed;
      bool mIsInitialized;
      int32_t mAngle;
      float mDirection;
      bool mDoTrace;
      int mStartMeasuringDistance;
    };

  }
}
 
#endif  // EV3_UNIT_BALANCINGWALKER_H_
