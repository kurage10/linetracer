/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_LINETRACER_H_
#define EV3_APP_LINETRACER_H_

#include "LineMonitor.h"
#include "BalancingWalker.h"
#include "Task.h"

using app::Task;

namespace LineTrace{
  namespace app{

class LineTracer : public Task{
public:
  LineTracer(unit::LineMonitor* lineMonitor,
	     unit::BalancingWalker* balancingWalker);

    void run();
    void init();
    bool isDone();
    void setStarting(bool starting);

private:
    unit::LineMonitor* mLineMonitor;
    unit::BalancingWalker* mBalancingWalker;
    bool mIsInitialized;
    bool mStarting;

};

  }
}

#endif  // EV3_APP_LINETRACER_H_
