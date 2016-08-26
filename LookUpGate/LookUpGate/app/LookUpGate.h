#ifndef LOOKUPGATE_H_
#define LOOKUPGATE_H_

#include "TailController.h"
#include "ev3api.h"
#include "SonarSensor.h"
#include "Motor.h"
namespace LookUpGate{
  namespace app{

class LookUpGate {
public:
    enum State {
        UNDEFINED,
        INIT,
        FIRST,
        BACK,
        SECOND
    };
    LookUpGate(LineTrace::unit::TailController* tailController,
                ev3api::SonarSensor& sonar,
                ev3api::Motor& leftWheel,
                ev3api::Motor& rightWheel);
    void run();
    
private:
    LineTrace::unit::TailController* mTailController;
    ev3api::SonarSensor& mSonar;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    State state;

    void init();
    void firstPass();
    void backWard();
    void secondPass();
    int setSpeed(int speed, int time);
    void delay(int time);

};
  }
}
#endif  // EV3_APP_LOOKUPGATE_H_