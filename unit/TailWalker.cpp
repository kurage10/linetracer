#include "TailWalker.h"


TailWalker::TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,ev3api::Motor& tailMotor,TailController* tailController,BalancingWalker* balancingWalker)
  :mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  mTailMotor(tailMotor),
  mTailController(tailController),
  mBalancingWalker(balancingWalker),
  mIsInitialized(false){

}
void TailWalker::run(){
  mTailController->setAngle((int32_t)75);
  mTailController->run();
  mLeftWheel.setPWM((int32_t)100);
  mRightWheel.setPWM((int32_t)100);
}
void TailWalker::init(){
  mTailController->setAngle((int32_t)75);
  mIsInitialized = true;
}
