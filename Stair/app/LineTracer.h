/******************************************************************************
 *  LineTracer.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineTracer
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_STAIR_APP_LINETRACER_H_
#define EV3_STAIR_APP_LINETRACER_H_

#include "../unit/LineMonitor.h"
#include "../unit/BalancingWalker.h"
#include "Task.h"

using app::Task;

namespace Stair{
  namespace app{

    class LineTracer : public Task {
    public:
      LineTracer(Stair::unit::LineMonitor* lineMonitor,
		 Stair::unit::BalancingWalker* balancingWalker);

      ~LineTracer();

      void run();
      bool isDone();
      void init();
      void reset();
      void stop();
      void setSpeed(int speed);
      void setStarting(bool starting);

    private:
      Stair::unit::LineMonitor* mLineMonitor;
      Stair::unit::BalancingWalker* mBalancingWalker;
      bool mIsInitialized;
      int mSpeed;
      bool mStarting;
      int timeFromStart;

      float calcSpeed(float direction);
    };

  }
}
#endif  // EV3_APP_LINETRACER_H_
