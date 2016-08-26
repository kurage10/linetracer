/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

/*
This is reference of this source code.
We have to fix the parameter KP,KI,KD
* http://monoist.atmarkit.co.jp/mn/articles/1007/26/news083.html
*/
#include "LineMonitor.h"

namespace LineTrace{
  namespace unit{

// 定数宣言
    const int8_t LineMonitor::INITIAL_THRESHOLD = 28;  // 黒色の光センサ値

const float LineMonitor::KP_80 = 0.90;
const float LineMonitor::KI_80 = 1.2;
const float LineMonitor::KD_80 = 0.048;

const float LineMonitor::KP_30 = 1.11;
const float LineMonitor::KI_30 = 3.96;
const float LineMonitor::KD_30 = 0.08;

const float LineMonitor::KP_Start = 0.35;
const float LineMonitor::DIRECTION_MAX = 100;
const int LineMonitor::ENC_THRESHOLD = 180; //内輪差判定値

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor,
			 ev3api::Motor& leftWheel,
			 ev3api::Motor& rightWheel)
    : mColorSensor(colorSensor),
      mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mThreshold(INITIAL_THRESHOLD),
      diff(),
      integral(0),
      mSpeed(80),
      leftWheelEnc(0),
      rightWheelEnc(0),
      startMeasuringEnc(0),
      time(0) {
  //  fp = fopen("directionLog.csv","w");
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
float LineMonitor::calcDirection(bool starting){
    // 光センサからの取得値を見て
    // PID制御を行う
  float p,i,d,speed;
  float KP,KI,KD;
  diff[0]=diff[1];
  diff[1] = mColorSensor.getBrightness() - mThreshold;
  integral=integral+(diff[1]+diff[0])/2.0*0.004;

  switch(mSpeed){
  case 80:
    KP = KP_80;
    KI = KI_80;
    KD = KD_80;
    break;
  case 30:
    KP = KP_30;
    KI = KI_30;
    KD = KD_30;
    break;
  default:
    KP = 1.0;
    KI = 0.0;
    KD = 0.0;
    break;
  }

  p=KP*diff[1];
  i=KI*integral;
  d=KD*(diff[1]-diff[0])/0.004;

  if(starting){
    speed=p/KP*KP_Start;
  }else{
    speed=p+i+d;
  }

  //右側走行化
  speed *= -1;

  if(mSpeed == 0){
    speed = 0;
  }

  if(speed > DIRECTION_MAX) return DIRECTION_MAX;
  else if(speed < -DIRECTION_MAX)return -DIRECTION_MAX;
  else return speed;

}

/**
 *距離を監視し条件に応じて速度を変更する
 */
int LineMonitor::calcSpeed(){
  int distance=measureDistance();
  if(distance > 2500 && startMeasuringEnc != 0){
    mSpeed = 30;
  }

  if(distance > 2770 && startMeasuringEnc != 0){
    mSpeed = 80;
  }

  if(distance > 3110 && startMeasuringEnc != 0){
    mSpeed = 30;
  }

  if(distance > 3380 && startMeasuringEnc != 0){
    mSpeed = 80;
  }

  return mSpeed;
}
int LineMonitor::measureDistance(){
  leftWheelEnc = mLeftWheel.getCount();
  rightWheelEnc = mRightWheel.getCount();

  if(rightWheelEnc - leftWheelEnc > ENC_THRESHOLD && startMeasuringEnc == 0){
    startMeasuringEnc = leftWheelEnc;
  }

  if(startMeasuringEnc == 0){
    return 0;
  }
  return leftWheelEnc - startMeasuringEnc;
}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}

  }
}
