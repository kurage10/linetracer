#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "StairTurner.h"
#include "LineTracer.h"
#include "GyroSensor.h"
#include "ObstacleDitector.h"
#include "TailWalker.h"
#include "BalancingWalker.h"
#include "TailController.h"
#include "Task.h"
#include "Waker.h"

using app::Task;
using LineTrace::unit::Waker;

namespace Stair{
  namespace app{

    class StairWalker : public Task{
    public:
      StairWalker(Stair::unit::StairTurner* stairTurner,
		  Stair::app::LineTracer* lineTracer,
		  Stair::unit::ObstacleDitector* obstacleDitector,
		  Stair::unit::TailWalker* tailWalker,
		  Stair::unit::BalancingWalker* balancingWalker,
		  Stair::unit::TailController* tailController,
      Waker* waker);
      void run();
      bool isDone();
      ~StairWalker();

    private:
      Stair::unit::StairTurner* mStairTurner;
      Stair::app::LineTracer* mLineTracer;
      Stair::unit::ObstacleDitector* mObstacleDitector;
      Stair::unit::TailWalker* mTailWalker;
      Stair::unit::BalancingWalker* mBalancingWalker;
      Stair::unit::TailController* mTailController;
      Waker* mWaker;
      enum State {
	      UNDEFINED,
	      PREPARE,
        STAY,
        STAND,
	      WALKING,
        PREPARE_CLIMB,
	      CLIMBING,
        PREPARE_TURNING,
	      TURNING,
        FINISH
      };
      State mState;
      int timefromstart;
      int mCount;
      bool isFinished;
      bool endLine;
      void execUndefined();
      void execPrepare();
      void execStand();
      void execStay();
      void execWalking();
      void execPrepareClimb();
      void execClimbing();
      void execPrepareTurning();
      void execTurning();
      void execFinish();
    };

  }
}
#endif
