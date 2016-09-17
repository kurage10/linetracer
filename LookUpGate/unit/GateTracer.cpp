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
      const float Kp = 3;//9        // 比例係数
      // target = 5, 8
      const int target = 7;//8        // 白・黒の中間値
      const int bias = 2;
      // msg_f("running...", 1);
      int diff = mColorSensor.getBrightness() - target;
      float turn = Kp * diff + bias;
      mLeftWheel.setPWM(pwm - turn);
      mRightWheel.setPWM(pwm + turn);
    }

    // void GateTracer::run2() {
    //   const float Kp = 15;//9        // 比例係数
    //   // target = 5, 8
    //   const int target = 8;//8        // 白・黒の中間値
    //   const int bias = 0;
    //   // msg_f("running...", 1);
    //   int diff = mColorSensor.getBrightness() - target;
    //   float turn = Kp * diff + bias;
    //   mLeftWheel.setPWM(pwm - (turn/100)*pwm);
    //   mRightWheel.setPWM(pwm + (turn/100)*pwm);
    // }

    bool GateTracer::back(int LeftCount, int RightCount) {
      /* const float Kp = 7;//3        // 比例係数
      const int target = 8;//7        // 白・黒の中間値
      const int bias = 0;
      // msg_f("running...", 1);
      int diff = mColorSensor.getBrightness() - target;
      float turn = Kp * diff + bias;
      mLeftWheel.setPWM(-(8 - (turn/100)*8));
      mRightWheel.setPWM(-(8 + (turn/100)*8));*/
      // mLeftWheel.setPWM(-5);
      // mRightWheel.setPWM(-5);
      float bias = 1.0;

      int mLeftCount = mLeftWheel.getCount();
      int mRightCount = mRightWheel.getCount();

      int Lspeed = (LeftCount - mLeftCount)*bias;
      int Rspeed = (RightCount - mRightCount)*bias;

      ev3_speaker_play_tone(NOTE_A5,300);

      if(Lspeed > 10){
	mLeftWheel.setPWM(10);
      }else if(Lspeed < -10){
	mLeftWheel.setPWM(-10);
      }else{
	mLeftWheel.setPWM(Lspeed);
      }

      if(Rspeed > 10){
	mRightWheel.setPWM(10);
      }else if(Rspeed < -10){
	mRightWheel.setPWM(-10);
      }else{
	mRightWheel.setPWM(Rspeed);
      }

      return -3 < Lspeed && Lspeed < 3 && -3 < Rspeed && Rspeed < 3;
    }

  }
}
