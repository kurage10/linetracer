#include "ObstacleDitector.h"
#include<stdio.h>

namespace Stair{
  namespace unit{

    const int ObstacleDitector::INITIAL_LIVENESS = 30;

    ObstacleDitector::ObstacleDitector(const ev3api::GyroSensor& gyroSensor,const ev3api::Motor& leftWheel,const ev3api::Motor& rightWheel,const ev3api::ColorSensor& colorSensor):
      mGyroSensor(gyroSensor),
      mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mColorSensor(colorSensor),
      onRight(false),
      straight(false),
      firstLand(false),
      mCliming(false),
      detectStair(false),
      max_left(0),
      max_left_liveness(INITIAL_LIVENESS),
      min_left(0),
      min_left_liveness(INITIAL_LIVENESS),
      max_right(0),
      max_right_liveness(INITIAL_LIVENESS),
      min_right(0),
      min_right_liveness(INITIAL_LIVENESS){
      file = fopen("/stairLog.csv","w");
      fprintf(file,"left,right,Climb\n");
    }
    bool ObstacleDitector::isObstacle(){
      //int16_t angle = mGyroSensor.getAnglerVelocity();  // ジャイロセンサ値
      int left = mLeftWheel.getCount();
      if(left > max_left){min_left=left;max_left=left;max_left_liveness=INITIAL_LIVENESS;}
      else {min_left=left;min_left_liveness=INITIAL_LIVENESS;}
      int diff_left=max_left-min_left;

      int right = mRightWheel.getCount();
      if(right > max_right){min_right=right;max_right=right;max_right_liveness=INITIAL_LIVENESS;}
      else {min_right=right;min_right_liveness=INITIAL_LIVENESS;}
      int diff_right=max_right-min_right;

      timefromstart=timefromstart+1;
      //fprintf(file,"%d,%d,%d,%d,%d,%d\n",left-left_offset,right-right_offset,vec_left,vec_right,200*(int)mCliming,200*(int)detectStair);
      fprintf(file,"%d,%d,%d\n",left,right,200*(int)mCliming);
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

      if(diff_left > 20 /*|| diff_right > 23*/){
        setOffset();
	      mCliming=true;
	      return true;
      }/*
	 if(mCliming && diff < 80 && 40 < diff){
	 mCliming=false;
	 detectStair=true;
	 return true;
	 }*/
      max_left_liveness=max_left_liveness-1;
      min_left_liveness=min_left_liveness-1;
      if(max_left_liveness <= 0)max_left=0;
      if(min_left_liveness <= 0)min_left=0;

      max_right_liveness=max_right_liveness-1;
      min_right_liveness=min_right_liveness-1;
      if(max_right_liveness <= 0)max_right=0;
      if(min_right_liveness <= 0)min_right=0;



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
    int ObstacleDitector::calcSpeed(int goal){
      return goal - (mLeftWheel.getCount() - left_offset);
    }
    void ObstacleDitector::init(){
      setOffset();
      mCliming=false;
      max_left=0;
      max_left_liveness=INITIAL_LIVENESS;
      min_left=0;
      min_left_liveness=INITIAL_LIVENESS;
      max_right=0;
      max_right_liveness=INITIAL_LIVENESS;
      min_right=0;
      min_right_liveness=INITIAL_LIVENESS;
    }
    void ObstacleDitector::setOffset(){
      left_offset = mLeftWheel.getCount();
      right_offset = mRightWheel.getCount();
      pre_left = left_offset;
      pre_right = right_offset;
      timefromstart=0;
    }
    void ObstacleDitector::setFirst(){
      if(!firstLand){
        firstLeft=mLeftWheel.getCount();
        firstRight=mRightWheel.getCount();
        firstLand=false;
      }
    }
    bool ObstacleDitector::isOnRight(){
      int left,right,color,diff;
      left = mLeftWheel.getCount();
      right = mRightWheel.getCount();
      color = mColorSensor.getBrightness();
      diff = (left > right) ? left-right : right-left;
      if(!onRight){
        if(right > left && color < 20){
          ev3_speaker_play_tone(NOTE_A5,300);
          onRight=true;
        }
      }else{
        if(diff < 20 || straight){
          straight = true;
          ev3_speaker_play_tone(NOTE_A5,300);
          return true;
        }
      }
      return false;
    }
    bool ObstacleDitector::onStraight(){
      int left,right,diff;
      left = mLeftWheel.getCount();
      right = mRightWheel.getCount();
      diff = (left > right) ? left-right : right-left;
      if(diff < 17 || straight){
        straight=true;
        return true;
      }else{
        return false;
      }
    }
  }
}
