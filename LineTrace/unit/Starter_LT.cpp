/******************************************************************************
 *  Starter.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Starter
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Starter.h"

namespace LineTrace{
  namespace unit{

    /**
     * コンストラクタ
     * @param touchSensor タッチセンサ
     */
    Starter::Starter(const ev3api::TouchSensor& touchSensor)
      : mTouchSensor(touchSensor),
	bt_cmd(false),
	wasPushed(false) {

    }

    void Starter::reset(){
      bt_cmd = false;
      wasPushed = false;
    }
    
    void Starter::setRemote(bool flag){
      bt_cmd=flag;

    }

    /**
     * 押下中か否か
     * @retval true  押下している
     * @retval false 押下していない
     */
    bool Starter::isPushed(){
      if(mTouchSensor.isPressed()){
	wasPushed = true;
      }

      return (bt_cmd || (wasPushed && !mTouchSensor.isPressed()));

    }

  }
}
