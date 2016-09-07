/******************************************************************************
 *  LineTracerWithStarter.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracerWithStarter.h"


/**
 * コンストラクタ
 * @param lineTracer ライントレーサ
 * @param starter    スタータ
 */
LineTracerWithStarter::LineTracerWithStarter(LineTracer* lineTracer,
                                              Starter* starter,
                                              TailController* tailController,
                                              ev3api::SonarSensor& sonar,
                                              LookUpGate* lookUpGate,
                                              // ev3api::Motor& leftWheel,
                                              // ev3api::Motor& rightWheel,
                                              Balancer* balancer)
    : mLineTracer(lineTracer),
      mStarter(starter),
      mTailController(tailController),
      mState(UNDEFINED),
      mSonar(sonar),
      mLookUpGate(lookUpGate),
      // mLeftWheel(leftWheel),
      // mRightWheel(rightWheel),
      mBalancer(balancer),
      timeFromStart(0) {
}

/**
 * ライントレースする
 */
void LineTracerWithStarter::run() {
    switch (mState) {
    case UNDEFINED:
        execUndefined();
        break;
    case WAITING_FOR_START:
        execWaitingForStart();
        break;
    case PREPARE_STARTING:
        execPrepare();
        break;
    case ROCKET_STARTING:
        execStarting();
      	break;
    case WALKING:
        execWalking();
        break;
    case LOOKUPGATE:
        execLookUpGate();
        break;
    default:
        break;
    }
}

/**
 * 未定義状態の処理
 */
void LineTracerWithStarter::execUndefined() {
  mTailController->init();
    mTailController->setAngle(102);
    
    mState = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void LineTracerWithStarter::execWaitingForStart() {
    mTailController -> run();
  
    if (mStarter->isPushed()) {
      mLineTracer->init();
      mTailController->setAngle(112);
      mState = PREPARE_STARTING;
      file2 = fopen("/gateDistance.txt","w");
    }
}

void LineTracerWithStarter::execPrepare() {
  mTailController -> run();

  if(mTailController -> getAngle() >= 108){
    mTailController -> setAngle(0);
    mState = ROCKET_STARTING;
  }
}

void LineTracerWithStarter::execStarting() {
  mLineTracer->run(true, timeFromStart);
  mTailController -> run();
  
  if(timeFromStart > 4000){
    mState = WALKING;
  }else{
    timeFromStart += 4;
  }
}

/**
 * 走行中状態の処理
 */
void LineTracerWithStarter::execWalking() {
  int dis = mSonar.getDistance();
  if (60 < dis && dis < 65) {      
    mTailController -> setAngle(85); 
  } else if (15 < dis && dis <= 20) {   
    mState = LOOKUPGATE;
  }
  mLineTracer->run(false, timeFromStart);
  mTailController -> run();
}

void LineTracerWithStarter::execLookUpGate() {
    // fprintf(file2,"LOOKUPGATE\n");
    mLookUpGate->run();
  //   mLeftWheel.setPWM(base_speed);
  //   mRightWheel.setPWM(base_speed);
  //   int dis = mSonar.getDistance();
  //   if (dis <= 20) {
  //     mTailController -> setAngle(80); 
  //   }

  // mTailController -> run();



}
