#ifndef EV3_APP_OBSTACLEDITECTOR_H_
#define EV3_APP_OBSTACLEDITECTOR_H_

#include "GyroSensor.h"
#include "ColorSensor.h"
#include "Motor.h"
#include<stdio.h>

namespace Stair{
  namespace unit{

class ObstacleDitector{
public:
  ObstacleDitector(const ev3api::GyroSensor& gyroSensor,const ev3api::Motor& leftWheel,const ev3api::Motor& rightWheel,const ev3api::ColorSensor& colorSensor);
  bool isObstacle();
  void init();
  bool isDistance(int goal);
  bool isDistanceFromFirst(int goal);
  void setOffset();
  void setFirst();
  int calcSpeed(int goal);
  bool isOnRight();
  bool onStraight();

private:
  const ev3api::GyroSensor& mGyroSensor;
  const ev3api::Motor& mLeftWheel;
  const ev3api::Motor& mRightWheel;
  const ev3api::ColorSensor& mColorSensor;

  static const int INITIAL_LIVENESS;
  float mColorLog[3];
  bool mCliming;
  bool onRight;
  bool straight;
  bool detectStair;
  bool firstLand;
  int firstLeft;
  int firstRight;
  int left_offset;
  int right_offset;
  int pre_left;
  int pre_right;
  int vec_left;
  int vec_right;
  int timefromstart;
  int max_left;
  int max_left_liveness;
  int min_left;
  int min_left_liveness;
  int max_right;
  int max_right_liveness;
  int min_right;
  int min_right_liveness;
  FILE* file;
};

  }
}
#endif
