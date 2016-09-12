#include "GateTracer.h"

namespace LookUpGate{
  namespace unit{

    GateTracer::GateTracer(ev3api::Motor& leftWheel,
                ev3api::Motor& rightWheel,
                ev3api::ColorSensor& colorSensor)
            : mLeftWheel(leftWheel),
              mRightWheel(rightWheel),
              mColorSensor(colorSensor){

              }

    void GateTracer::init() {
      // init_f("Tracer");
    }

    void GateTracer::terminate() {
      // msg_f("Stopped.", 1);
      mLeftWheel.stop();
      mRightWheel.stop();
    }

    void GateTracer::run() {
      const float Kp = 3;        // 比例係数
      const int target = 5;        // 白・黒の中間値
      const int bias = 0;
      // msg_f("running...", 1);
      int diff = mColorSensor.getBrightness() - target;
      float turn = Kp * diff + bias;
      mLeftWheel.setPWM(pwm - turn);
      mRightWheel.setPWM(pwm + turn);
    }

    void GateTracer::back() {
      const float Kp = 1;        // 比例係数
      const int target = 5;        // 白・黒の中間値
      const int bias = 0;
      // msg_f("running...", 1);
      int diff = mColorSensor.getBrightness() - target;
      float turn = Kp * diff + bias;
      mLeftWheel.setPWM(-(pwm - turn));
      mRightWheel.setPWM(-(pwm + turn));
    }
  }
}