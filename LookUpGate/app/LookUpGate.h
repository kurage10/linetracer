#ifndef LOOKUPGATE_H_
#define LOOKUPGATE_H_

#include "../../LineTrace/unit/TailController.h"
#include "../../LineTrace/unit/BalancingWalker.h"
#include "../../LineTrace/app/LineTracer.h"
#include "ev3api.h"
#include "SonarSensor.h"
#include "Motor.h"
#include "GateTracer.h"
#include "Task.h"

using app::Task;

namespace LookUpGate{
  namespace app{

    class LookUpGate : public Task {
    public:
        enum State {
            UNDEFINED,
            SEEK,
            INIT,
            FIRST,
            BACK,
            SECOND
        };
        LookUpGate(LineTrace::unit::TailController* tailController,
                    ev3api::SonarSensor& sonar,
                    ev3api::Motor& leftWheel,
                    ev3api::Motor& rightWheel,
                    unit::GateTracer* gateTracer,
                    LineTrace::app::LineTracer* lineTracer,
                    LineTrace::unit::BalancingWalker* balancingWalker);
        ~LookUpGate();
        void run();
        bool isDone();
	void reset();
      
    private:
        LineTrace::unit::TailController* mTailController;
        ev3api::SonarSensor& mSonar;
        ev3api::Motor& mLeftWheel;
        ev3api::Motor& mRightWheel;
        unit::GateTracer* mGateTracer;
        LineTrace::app::LineTracer* mLineTracer;
        LineTrace::unit::BalancingWalker* mBalancingWalker;
        State state;
	int time;
	int LeftCount;
	int RightCount;

        void seek();
        void init();
        void firstPass();
        void backWard();
        void secondPass();
        int setSpeed(int speed, int time);
        void delay(int time);
	void getCount();

    };
  }
}
#endif  // EV3_APP_LOOKUPGATE_H_
