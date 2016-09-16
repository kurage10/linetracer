#include "ObstacleDitector.h"
#include<stdio.h>

namespace Stair{
  namespace unit{

    const int ObstacleDitector::INITIAL_LIVENESS = 30;

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
      fprintf(file,"angle,max,min,mCliming,detectStair\n");
    }
    bool ObstacleDitector::isObstacle(){
      //int16_t angle = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値
      int angle = mLeftWheel.getCount();
      if(angle > max){min=angle;max=angle;max_liveness=INITIAL_LIVENESS;}
      else {min=angle;min_liveness=INITIAL_LIVENESS;}
      int diff=max-min;
      int left,right;

      timefromstart=timefromstart+1;
      //fprintf(file,"%d,%d,%d,%d,%d,%d\n",left-left_offset,right-right_offset,vec_left,vec_right,200*(int)mCliming,200*(int)detectStair);
      fprintf(file,"%d,%d,%d,%d,%d\n",angle,max,min,200*(int)mCliming,200*(int)detectStair);
      /*
      if(timefromstart % 100==0){
        left = mLeftWheel.getCount();
        right = mRightWheel.getCount();

        vec_left=left-pre_left;
        vec_right=right-pre_left;

        if(left-left_offset > 20 && right-right_offset >20 && vec_left < 0 && vec_right < 0){
          mCliming=true;
          return true;
        }
        pre_left=left;
        pre_right=right;
      }*/

      if(diff > 20){
        setOffset();
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
      left = mLeftWheel.getCount();
      right = mRightWheel.getCount();
      if(left-left_offset >= goal && right - right_offset >= goal){
        return true;
      }
      return false;
    }
    void ObstacleDitector::init(){
      mCliming=false;
      max=0;min=0;
      max_liveness=INITIAL_LIVENESS;
      min_liveness=INITIAL_LIVENESS;
    }
    void ObstacleDitector::setOffset(){
      left_offset = mLeftWheel.getCount();
      right_offset = mRightWheel.getCount();
      pre_left = left_offset;
      pre_right = right_offset;
      timefromstart=0;
    }

  }
}
