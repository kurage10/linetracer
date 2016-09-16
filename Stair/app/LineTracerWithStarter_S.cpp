/******************************************************************************
 *  LineTracerWithStarter.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracerWithStarter.h"

namespace Stair{
  namespace app{

    /**
     * コンストラクタ
     * @param lineTracer ライントレーサ
     * @param starter    スタータ
     */
    LineTracerWithStarter::LineTracerWithStarter(app::LineTracer* lineTracer,
						 unit::Starter* starter,
						 unit::TailController* tailController)
      : mLineTracer(lineTracer),
	mStarter(starter),
	mTailController(tailController),
	mState(UNDEFINED),
	timeFromStart(0) {
    }

    LineTracerWithStarter::~LineTracerWithStarter(){
      delete mLineTracer;
      delete mStarter;
      delete mTailController;
      delete &mState;
      delete &timeFromStart;
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


    bool LineTracerWithStarter::isDone(){
      return timeFromStart > 4000;
    }
    /**
     * 未定義状態の処理
     */
    void LineTracerWithStarter::execUndefined() {
      mTailController->setAngle(96);

      mState = WAITING_FOR_START;
    }

    /**
     * 開始待ち状態の処理
     */
    void LineTracerWithStarter::execWaitingForStart() {
      mTailController -> run();

      if (mStarter->isPushed()) {
	      mLineTracer->init();
	      mTailController->setAngle(99);
	      mState = PREPARE_STARTING;
      }
    }

    void LineTracerWithStarter::execPrepare() {
      mTailController -> run();

      if(mTailController -> getAngle() >= 96){
	      mTailController -> setAngle(10);
	      mState = ROCKET_STARTING;
      }
    }

    void LineTracerWithStarter::execStarting() {
      mLineTracer->setStarting(true);
      mLineTracer->run();
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
      timeFromStart += 4;
      mLineTracer->setStarting(false);
      mLineTracer->run();
      //mTailController -> run();
    }

  }
}
