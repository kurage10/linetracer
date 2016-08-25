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

namespace LineTrace{
  namespace app{

class LineTracer {
public:
  LineTracer(unit::LineMonitor* lineMonitor,
	     unit::BalancingWalker* balancingWalker);

    void run(bool starting, int timeFromStart);
    void init();

private:
    unit::LineMonitor* mLineMonitor;
    unit::BalancingWalker* mBalancingWalker;
    bool mIsInitialized;

    float calcSpeed(float direction);
};

  }
}

#endif  // EV3_APP_LINETRACER_H_
