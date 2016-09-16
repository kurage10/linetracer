#include "StairTurner.h"

namespace Stair{
  namespace unit{

const int StairTurner::INITIAL_LIVENESS = 20;

StairTurner::StairTurner(ev3api::Motor& leftWheel,ev3api::Motor& rightWheel,TailController* tailController,const ev3api::ColorSensor& colorSensor):
  mLeftWheel(leftWheel),
  mRightWheel(rightWheel),
  mTailController(tailController),
  mColorSensor(colorSensor),
  mIsInitialized(false),
  mOnline(false),
  mSpeed(30),
  timefromstart(0) {
    max=0;
    min=100;
    max_liveness=INITIAL_LIVENESS;
    min_liveness=INITIAL_LIVENESS;

    file = fopen("/turnLog.csv","w");
    fprintf(file,"diff,max,min,max_liveness,min_liveness,Count\n");

}

void StairTurner::run(){
  mTailController->run();
  mLeftWheel.setPWM(mSpeed);
  mRightWheel.setPWM(-mSpeed);

}
void StairTurner::init(){
  mLeftWheel.setPWM(0);
  mRightWheel.setPWM(0);
  mTailController->setAngle(85);
  mIsInitialized=false;
  mCount=0;
  timefromstart=0;
  max=0;min=100;
  max_liveness=INITIAL_LIVENESS;
  min_liveness=INITIAL_LIVENESS;
}
bool StairTurner::isDone(){

  return detectCrossLine();
}
bool StairTurner::detectCrossLine(){
  timefromstart=timefromstart+1;
  int bright=mColorSensor.getBrightness();
  if(bright > max){max=bright;max_liveness=INITIAL_LIVENESS;}
  else if(bright < min){min=bright;min_liveness=INITIAL_LIVENESS;}
  int diff = max-min;
  fprintf(file,"%d,%d,%d,%d,%d,%d\n",diff,max,min,max_liveness,min_liveness,200*(int)mCount);
  if( diff >= 0 && diff <= 5 && max < 7 && !mOnline && timefromstart > 80){
    mOnline=true;
    mCount=mCount+1;
    max=0;
    min=100;
  }
  if(min > 6 && min < 50){
      if(mCount == 2)return true;
      mOnline = false;
  }
  max_liveness=max_liveness-1;
  min_liveness=min_liveness-1;
  if(max_liveness <= 0)max=0;
  if(min_liveness <= 0)min=100;
  return false;
}


  }
}
