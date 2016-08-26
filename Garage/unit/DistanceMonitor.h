#ifndef EV3_UNIT_DISTANCE_MONITOR_H_
#define EV3_UNIT_DISTANCE_MONITOR_H_
#include "Motor.h"

namespace unit{

  class DistanceMonitor{
  public:
    DistanceMonitor(ev3api::Motor& leftMotor, ev3api::Motor& rightMotor);
    int measure();
    void init();

  private:
    static const int ENC_THRESHOLD;

    ev3api::Motor& mleftMotor;
    ev3api::Motor& mrightMotor;
    int leftWheelEnc;
    int rightWheelEnc;
    int startMeasuringEnc;
  };
}
#endif
