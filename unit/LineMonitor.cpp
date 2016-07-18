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

// 定数宣言
const int8_t LineMonitor::INITIAL_THRESHOLD = 23;  // 黒色の光センサ値
const float LineMonitor::KP = 1.11;
const float LineMonitor::KI = 3.96;
const float LineMonitor::KD = 0.08;

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold(INITIAL_THRESHOLD),
      diff(),
      integral(0){
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
float LineMonitor::calcVecSpeed(){
    // 光センサからの取得値を見て
    // PID制御を行う
  float p,i,d,speed;
  diff[0]=diff[1];
  diff[1] = mColorSensor.getBrightness() - mThreshold;
  integral=integral+(diff[1]+diff[0])/2.0*0.004;
  p=KP*diff[1];
  i=KI*integral;
  d=KD*(diff[1]-diff[0])/0.004;
  speed=p+i+d;

  //右側走行化
  speed *= -1;
  
  if(speed > 100) return 100;
  else if(speed < -100)return -100;
  else return speed;

}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}
