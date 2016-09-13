#ifndef EV3_APP_OBSTACLEDITECTOR_H_
#define EV3_APP_OBSTACLEDITECTOR_H_

#include "GyroSensor.h"
#include<stdio.h>

namespace Stair{
  namespace unit{

class ObstacleDitector{
public:
  ObstacleDitector(const ev3api::GyroSensor& gyroSensor);
  bool isObstacle();
  void init();
  void setThreshold(int threshold);
private:
  const ev3api::GyroSensor& mGyroSensor;
  static const int INITIAL_LIVENESS;
  float mColorLog[3];
  bool mCliming;
  bool detectStair;
  int max;
  int max_liveness;
  int min;
  int min_liveness;
  int mThreshold;
  FILE* file;
};

  }
}
#endif
