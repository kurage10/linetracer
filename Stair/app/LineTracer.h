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

class LineTracer {
public:
    LineTracer(LineMonitor* lineMonitor,
               BalancingWalker* balancingWalker);

    void run(bool starting);
    void init();
    void stop();

private:
    LineMonitor* mLineMonitor;
    BalancingWalker* mBalancingWalker;
    bool mIsInitialized;
    int mSpeed;
    float calcSpeed(float direction);
};

#endif  // EV3_APP_LINETRACER_H_
