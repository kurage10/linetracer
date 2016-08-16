#include "ObstacleDitector.h"
#include<stdio.h>

const int ObstacleDitector::INITIAL_LIVENESS = 80;

ObstacleDitector::ObstacleDitector(const ev3api::GyroSensor& gyroSensor):
  mGyroSensor(gyroSensor),
  max(0),
  max_liveness(INITIAL_LIVENESS),
  min(0),
  min_liveness(INITIAL_LIVENESS),
  mCliming(false),
  detectStair(false)
  {
    file = fopen("/stairLog.csv","w");
    fprintf(file,"angle,diff,max,min,max_liveness,min_liveness,mCliming,detectStair\n");
}
bool ObstacleDitector::isObstacle(){
  int16_t angle = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値
  if(angle > max){max=angle;max_liveness=INITIAL_LIVENESS;}
  else if(angle < min){min=angle;min_liveness=INITIAL_LIVENESS;}
  int diff=max-min;
  fprintf(file,"%d,%d,%d,%d,%d,%d,%d,%d\n",angle,diff,max,min,max_liveness,min_liveness, 200*(int)mCliming,200*(int)detectStair);

  if(diff > 130 || mCliming){
    mCliming=true;
    return true;
  }/*
  if(mCliming && diff < 80 && 40 < diff){
    mCliming=false;
    detectStair=true;
    return true;
  }*/
  max_liveness=max_liveness-1;
  min_liveness=min_liveness-1;
  if(max_liveness <= 0)max=0;
  if(min_liveness <= 0)min=0;

  return false;
}
void ObstacleDitector::init(){
  mCliming=false;
}
