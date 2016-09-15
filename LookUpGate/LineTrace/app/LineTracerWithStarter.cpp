/******************************************************************************
 *  LineTracerWithStarter.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracerWithStarter.h"

namespace LineTrace{
  namespace app{
  
/**
 * コンストラクタ
 * @param lineTracer ライントレーサ
 * @param starter    スタータ
 */
    LineTracerWithStarter::LineTracerWithStarter(app::LineTracer* lineTracer,
						 unit::Starter* starter,
						 unit::TailController* tailController,
             ev3api::SonarSensor& sonar)
    : mLineTracer(lineTracer),
      mStarter(starter),
      mSonar(sonar),
      mTailController(tailController),
      mState(UNDEFINED),
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
  
  if(timeFromStart > 3000){
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
  if (dis < 60) {      
    mTailController -> setAngle(85); 
  }

  mLineTracer->run(false, timeFromStart);
  mTailController -> run();
}

  }
}