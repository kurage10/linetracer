/******************************************************************************
 *  LineTracerWithStarter.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_LINETRACERWITHSTARTER_H_
#define EV3_APP_LINETRACERWITHSTARTER_H_

#include "Starter.h"
#include "LineTracer.h"
#include "TailController.h"
#include "ev3api.h"
#include "SonarSensor.h"
#include "Motor.h"
#include <stdio.h>
#include "BalancerCpp.h"
#include "LookUpGate.h"

class LineTracerWithStarter {
public:
    LineTracerWithStarter(LineTracer* lineTracer,
                          Starter* starter,
                          TailController* tailController,
                          ev3api::SonarSensor& sonar,
                          LookUpGate* lookUpGate,
                          // ev3api::Motor& leftWheel,
                          // ev3api::Motor& rightWheel,
                          Balancer* balancer);

    void run();

private:
    enum State {
        UNDEFINED,
        WAITING_FOR_START,
	PREPARE_STARTING,
	ROCKET_STARTING,
        WALKING,
        LOOKUPGATE
    };

    LineTracer* mLineTracer;
    Starter* mStarter;
    TailController* mTailController;
    State mState;
    ev3api::SonarSensor& mSonar;
    LookUpGate* mLookUpGate;
    // ev3api::Motor& mLeftWheel;
    // ev3api::Motor& mRightWheel;
    FILE * file2;
    Balancer* mBalancer;


    void execUndefined();
    void execWaitingForStart();
    void execPrepare();
    void execStarting();
    void execWalking();
    void execLookUpGate();

    bool mStarting();
    int timeFromStart;
};

#endif  // EV3_APP_LINETRACERWITHSTARTER_H_
