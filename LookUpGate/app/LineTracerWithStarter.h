/******************************************************************************
 *  LineTracerWithStarter.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_LINETRACE_APP_LINETRACERWITHSTARTER_H_
#define EV3_LINETRACE_APP_LINETRACERWITHSTARTER_H_

#include "GyroSensor.h"
#include "../unit/Starter.h"
#include "./LineTracer.h"
#include "../unit/TailController.h"
#include "Task.h"

using app::Task;
namespace LineTrace{
  namespace app{

    class LineTracerWithStarter : public Task{
    public:
      LineTracerWithStarter(app::LineTracer* lineTracer,
			    unit::Starter* starter,
			    unit::TailController* tailController,
			    ev3api::GyroSensor& gyroSensor);

      ~LineTracerWithStarter();

      void run();
      bool isDone();

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
      ev3api::GyroSensor& mGyroSensor;
      State mState;
      FILE* fp;

      void execUndefined();
      void execWaitingForStart();
      void execPrepare();
      void execStarting();
      void execWalking();
      bool isFinished();
      bool mStarting();
      int timeFromStart;
    };

  }
}

#endif  // EV3_APP_LINETRACERWITHSTARTER_H_
