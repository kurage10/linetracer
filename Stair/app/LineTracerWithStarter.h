/******************************************************************************
 *  LineTracerWithStarter.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_LINETRACERWITHSTARTER_H_
#define EV3_APP_LINETRACERWITHSTARTER_H_

#include "../unit/Starter.h"
#include "./LineTracer.h"
#include "../unit/TailController.h"
#include "./StairWalker.h"

using app::Task;

namespace Stair{
  namespace app{

    class LineTracerWithStarter : public Task{
    public:
      LineTracerWithStarter(app::LineTracer* lineTracer,
			    unit::Starter* starter,
			    unit::TailController* tailController);

      void run();
      bool isDone();
      void reset();
      ~LineTracerWithStarter();
      
    private:
      enum State {
        UNDEFINED,
        WAITING_FOR_START,
	PREPARE_STARTING,
	ROCKET_STARTING,
        WALKING
      };
      
      app::LineTracer* mLineTracer;
      unit::Starter* mStarter;
      unit::TailController* mTailController;
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
