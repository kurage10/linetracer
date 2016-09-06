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
    : mTouchSensor(touchSensor) {
      mBt = ev3_serial_open_file(EV3_SERIAL_BT);
}

/**
 * 押下中か否か
 * @retval true  押下している
 * @retval false 押下していない
 */
bool Starter::isPushed(){
    uint8_t c = fgetc(mBt); /* 受信 */
    if(c=='1'){
      bt_cmd=true;
    }else{
      bt_cmd=false;
    }
    fputc(c, mBt); /* エコーバック */
    return (bt_cmd || mTouchSensor.isPressed());

}

  }
}
