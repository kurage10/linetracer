/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_LINETRACE_APP_LINETRACER_H_
#define EV3_LINETRACE_APP_LINETRACER_H_

#include "../unit/LineMonitor.h"
#include "../unit/BalancingWalker.h"
#include "Task.h"

using app::Task;

namespace LineTrace{
  namespace app{

    class LineTracer : public Task{
    public:
      LineTracer(unit::LineMonitor* lineMonitor,
		 unit::BalancingWalker* balancingWalker);

      ~LineTracer();

      void run();
      void init();
      bool isDone();
      void setStarting(bool starting);
      void setSpeed(int speed);

    private:
      unit::LineMonitor* mLineMonitor;
      unit::BalancingWalker* mBalancingWalker;
      bool mIsInitialized;
      bool mStarting;
      int mSpeed;

    };

  }
}

#endif  // EV3_APP_LINETRACER_H_
