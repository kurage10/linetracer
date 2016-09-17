/******************************************************************************
 *  BalancingWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class BalancingWalker
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_STAIR_UNIT_BALANCINGWALKER_H_
#define EV3_STAIR_UNIT_BALANCINGWALKER_H_

#include "InitValues.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "BalancerCpp.h"

#include <stdio.h>

using unit::InitValues;

namespace Stair{
  namespace unit{

class BalancingWalker {
public:
  static const int LOWEST;
    static const int LOW;
    static const int NORMAL;
    static const int HIGH;

    BalancingWalker(const ev3api::GyroSensor& gyroSensor,
                    ev3api::Motor& leftWheel,
                    ev3api::Motor& rightWheel,
                    Stair::unit::Balancer* balancer,
		    InitValues* initValues);

    void init();
    void run();
    void setCommand(int forward, int turn);
    void changeMode(bool Balance);
    void prepareStand();
    
private:
    const ev3api::GyroSensor& mGyroSensor;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    Stair::unit::Balancer* mBalancer;
    InitValues* mInitValues;
    int mForward;
    int mTurn;

    //FILE* file;
};

  }
}
 
#endif  // EV3_UNIT_BALANCINGWALKER_H_
