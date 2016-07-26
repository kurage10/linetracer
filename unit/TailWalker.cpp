#include "TailWalker.h"

TailWalker::TailWalker(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController)
  :mTailController(tailController),
  mLeftWheel(leftWheel),
  mRightWheel(rightWheel){

}
void TailWalker::run(){
  mTailController->setAngle(70);
  mLeftWheel.setPWM(80);
  mRightWheel.setPWM(80);
}
void TailWalker::init(){
  mLeftWheel.reset();
  mRightWheel.reset();
}
