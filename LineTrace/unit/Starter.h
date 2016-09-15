/******************************************************************************
 *  Starter.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Starter
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_LINETRACE_UNIT_STARTER_H_
#define EV3_LINETRACE_UNIT_STARTER_H_

#include "TouchSensor.h"
#include <stdio.h>
#include "ev3api.h"

namespace LineTrace{
  namespace unit{

class Starter {
public:
    explicit Starter(const ev3api::TouchSensor& touchSensor);

    bool isPushed();
    void setRemote(bool flag);

protected:
    const ev3api::TouchSensor& mTouchSensor;
    bool bt_cmd;     /* Bluetoothコマンド 1:リモートスタート */
    bool wasPushed;
};

  }
}

#endif  // EV3_UNIT_STARTER_H_
