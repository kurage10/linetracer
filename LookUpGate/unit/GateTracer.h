#ifndef EV3_LOOKUPGATE_UNIT_GATETRACER_H_
#define EV3_LOOKUPGATE_UNIT_GATETRACER_H_

#include "Motor.h"
#include "ColorSensor.h"

namespace LookUpGate{
  namespace unit{

class GateTracer {
public:
  GateTracer(ev3api::Motor& leftWheel,
              ev3api::Motor& rightWheel,
              ev3api::ColorSensor& colorSensor);


  void run();
  void init();
  void terminate();
  void back();

private:
  ev3api::Motor mLeftWheel;
  ev3api::Motor mRightWheel;
  ev3api::ColorSensor mColorSensor;
  const int8_t mThreshold = 20;
  const int8_t pwm = (ev3api::Motor::PWM_MAX) / 5;
};
  }
}
#endif //
