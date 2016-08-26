#include "DistanceMonitor.h"

namespace unit{
  
  const int DistanceMonitor::ENC_THRESHOLD = 180;

  DistanceMonitor::DistanceMonitor(ev3api::Motor& leftMotor, ev3api::Motor& rightMotor)
    : mleftMotor(leftMotor),
      mrightMotor(rightMotor),
      leftWheelEnc(),
      rightWheelEnc(),
      startMeasuringEnc() {
  }

  int DistanceMonitor::measure(){
    leftWheelEnc = mleftMotor.getCount();
    rightWheelEnc = mrightMotor.getCount();

    if(rightWheelEnc - leftWheelEnc > ENC_THRESHOLD && startMeasuringEnc == 0){
      startMeasuringEnc = leftWheelEnc;
    }

    if(startMeasuringEnc == 0){
      return 0;
    }
    return leftWheelEnc - startMeasuringEnc;
  }

  void DistanceMonitor::init(){
    mleftMotor.reset();
    mrightMotor.reset();
  }
}
