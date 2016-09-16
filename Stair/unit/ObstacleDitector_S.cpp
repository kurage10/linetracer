#include "ObstacleDitector.h"
#include<stdio.h>

namespace Stair{
  namespace unit{

    const int ObstacleDitector::INITIAL_LIVENESS = 80;

    ObstacleDitector::ObstacleDitector(const ev3api::GyroSensor& gyroSensor,const ev3api::Motor& leftWheel,const ev3api::Motor& rightWheel):
      mGyroSensor(gyroSensor),
      mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mCliming(false),
      detectStair(false),
      max(0),
      max_liveness(INITIAL_LIVENESS),
      min(0),
      min_liveness(INITIAL_LIVENESS) {
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
        left_offset = mLeftWheel.getCount();
        right_offset = mRightWheel.getCount();
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
    bool ObstacleDitector::isDistance(int goal){
      int left,right;
      if(mCliming){
        left = mLeftWheel.getCount();
        right = mRightWheel.getCount();
        if(left-left_offset >= goal && right - right_offset >= goal){
          return true;
        }
      }
      return false;
    }
    void ObstacleDitector::init(){
      mCliming=false;
      max=0;min=0;
      max_liveness=INITIAL_LIVENESS;
      min_liveness=INITIAL_LIVENESS;
    }

  }
}
