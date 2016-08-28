/******************************************************************************
 *  LineTracerWithStarter.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_LINETRACERWITHSTARTER_H_
#define EV3_APP_LINETRACERWITHSTARTER_H_

#include "Starter.h"
#include "LineTracer.h"
#include "TailController.h"
#include "StairWalker.h"

namespace Stair{
  namespace app{

class LineTracerWithStarter {
public:
  LineTracerWithStarter(Stair::app::LineTracer* lineTracer,
			Stair::unit::Starter* starter,
			Stair::unit::TailController* tailController);

    void run();

private:
    enum State {
        UNDEFINED,
        WAITING_FOR_START,
	PREPARE_STARTING,
	ROCKET_STARTING,
        WALKING
    };

    Stair::app::LineTracer* mLineTracer;
    Stair::unit::Starter* mStarter;
    Stair::unit::TailController* mTailController;
    State mState;

    void execUndefined();
    void execWaitingForStart();
    void execPrepare();
    void execStarting();
    void execWalking();

    bool mStarting();
    int timeFromStart;
};

  }
}
 
#endif  // EV3_APP_LINETRACERWITHSTARTER_H_
