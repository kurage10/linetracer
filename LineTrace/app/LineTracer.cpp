/******************************************************************************
 *  LineTracer.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracer.h"
#include <math.h>

namespace LineTrace{
  namespace app{
    /**
     * コンストラクタ
     * @param lineMonitor     ライン判定
     * @param balancingWalker 倒立走行
     */
    LineTracer::LineTracer(unit::LineMonitor* lineMonitor,
			   unit::BalancingWalker* balancingWalker)
      : mLineMonitor(lineMonitor),
	mBalancingWalker(balancingWalker),
	mIsInitialized(false){
    }

    /**
     * ライントレースする
     */
    void LineTracer::run() {
      int mSpeed;

      if (mIsInitialized == false) {
        mBalancingWalker->init();
        mIsInitialized = true;
      }

      float direction = mLineMonitor->calcDirection(mStarting);

      mSpeed = mLineMonitor->calcSpeed();

      mBalancingWalker->setCommand(mSpeed, direction);
      // 倒立走行を行う
      mBalancingWalker->run();
    }

    void LineTracer::init(){
      mBalancingWalker->init();
      mIsInitialized = true;
    }

    bool LineTracer::isDone(){
      int distance = mLineMonitor->measureDistance();
      if(distance > 9000){
	return true;
      }
      else{
	return false;
      }
    }
    void LineTracer::setStarting(bool starting){
      mStarting = starting;
    }

    LineTracer::~LineTracer(){
      delete mLineMonitor;
      delete mBalancingWalker;
      delete &mIsInitialized;
    }
  }
}
