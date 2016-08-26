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
      mIsInitialized(false) {
}

/**
 * ライントレースする
 */
void LineTracer::run(bool starting, int timeFromStart) {
  int mSpeed;
  
  if (mIsInitialized == false) {
        mBalancingWalker->init();
        mIsInitialized = true;
  }

    float direction = mLineMonitor->calcDirection(starting);

    mSpeed = mLineMonitor->distanceMonitor();
    
    // 走行体の向きを計算する
    //float speed = calcSpeed(direction);

    //mBalancingWalker->setCommand(BalancingWalker::LOW, direction);
    mBalancingWalker->setCommand(mSpeed, direction);
    //    if(starting){
    //      mBalancingWalker->setCommand(mSpeed, 10);
    //    }else{
    //      mBalancingWalker->setCommand(mSpeed, 25);
    //    }
      
    // 倒立走行を行う
    mBalancingWalker->run();
}

/**
 * 走行体の向きを計算する
 * @param isOnLine true:ライン上/false:ライン外
 * @retval 30  ライン上にある場合(右旋回指示)
 * @retval -30 ライン外にある場合(左旋回指示)
 */
float LineTracer::calcSpeed(float direction) {
    if (direction > 0) {
        // ライン上にある場合
        return direction;
    } else {
        // ライン外にある場合
        return -direction;
    }
}

void LineTracer::init(){
  mBalancingWalker->init();
  mIsInitialized = true;
}

  }
}