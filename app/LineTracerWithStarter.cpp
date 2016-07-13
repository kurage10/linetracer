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
LineTracerWithStarter::LineTracerWithStarter(LineTracer* lineTracer,Starter* starter,TailController* tailController)
    : mLineTracer(lineTracer),
      mStarter(starter),
      mTailController(tailController),
      mState(UNDEFINED) {
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
    mTailController->setAngle(90);
    mState = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void LineTracerWithStarter::execWaitingForStart() {
    mTailController -> run();
    if (mStarter->isPushed()) {
      mTailController->setAngle(3);
      mState = WALKING;
    }
}

/**
 * 走行中状態の処理
 */
void LineTracerWithStarter::execWalking() {
    mTailController -> run();
    mLineTracer->run();
}
