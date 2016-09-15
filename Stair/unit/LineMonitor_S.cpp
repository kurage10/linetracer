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

namespace Stair{
  namespace unit{


// 定数宣言
const int8_t LineMonitor::THRESHOLD_Tail = 8;  // 黒色の光センサ値
const float LineMonitor::KP_Tail = 9.22;
    //const float LineMonitor::KP_Tail = 2.22;
const float LineMonitor::KI_Tail = 0.0;
    //const float LineMonitor::KI_Tail = 7.92;
const float LineMonitor::KD_Tail = 0.0;
    //const float LineMonitor::KD_Tail = 0.16;

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold(THRESHOLD_Tail),
      diff(),
      integral(0),
      onLineFlag() {
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
float LineMonitor::calcDirection(State state){
    // 光センサからの取得値を見て
    // PID制御を行う
  float p,i,d,direction;
  float KP,KI,KD;
  
  switch(state){
  case TailWalking:
    //ev3_speaker_play_tone(NOTE_C6,500);
    KP = KP_Tail;
    KI = KI_Tail;
    KD = KD_Tail;
    mThreshold = THRESHOLD_Tail;
    break;
  case BalanceWalking:
    break;
  default:
    break;
  }
  
  diff[0]=diff[1];
  diff[1] = mColorSensor.getBrightness() - mThreshold;
  integral=integral+(diff[1]+diff[0])/2.0*0.004;
  p=KP*diff[1];
  i=KI*integral;
  d=KD*(diff[1]-diff[0])/0.004;

  direction=p+i+d;
    
  //右側走行化
  direction *= -1;
  
  if(direction > 100) return 100;
  else if(direction < -100)return -100;
  else return direction;

}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}

    bool LineMonitor::onLine(){
      if(mColorSensor.getBrightness() < THRESHOLD_Tail){
	onLineFlag = true;
      }
      return onLineFlag;
    }

    void LineMonitor::resetOnLine(){
      onLineFlag = false;
    }
  }
}
