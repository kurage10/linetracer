#include "./TailController.h"

namespace Garage{
  namespace unit{

    TailController::TailController(ev3api::Motor& tailMotor)
      :mTailMotor(tailMotor),
       mAngle(3){}

    void TailController::run(){
      int speed = calcDirection();
      mTailMotor.setPWM(speed);
    }

    void TailController::init(){
      ev3api::Clock mClock = ev3api::Clock();
      
      mTailMotor.setPWM(-100);
      mClock.sleep(1000);
      mTailMotor.setPWM(0);
      mTailMotor.reset();

      mTailMotor.setBrake(true);
    }
    int TailController::calcDirection(){
      //int diff=(mTailMotor.getCount()-mAngle)*0.25;
      int diff=(mTailMotor.getCount()-mAngle)*0.90;
      if(diff > 100) return -100;
      else if(diff < -100)return 100;
      else return -diff;
    }
    void TailController::setAngle(int32_t angle){
      mAngle=angle;
    }

    int32_t TailController::getAngle(){
      return mTailMotor.getCount();
    }

    void TailController::getUp(){
      mTailMotor.setPWM(1);
    }
  }
}
