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
#include "./LineMonitor.h"

namespace Garage{
  namespace unit{

    
    // 定数宣言
    const int8_t LineMonitor::THRESHOLD_Tail = 8;  // 黒色の光センサ値
    const float LineMonitor::KP_Tail = 9.22;
    
    /**
     * コンストラクタ
     * @param colorSensor カラーセンサ
     */
    LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor)
      : mColorSensor(colorSensor),
	mThreshold(THRESHOLD_Tail){
    }
    
    /**
     * ライン上か否かを判定する
     * @retval true  ライン上
     * @retval false ライン外
     */
    float LineMonitor::calcDirection(){
      // 光センサからの取得値を見て
      // P制御を行う
      float direction = KP_Tail*(mColorSensor.getBrightness() - mThreshold);

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

  }
}
