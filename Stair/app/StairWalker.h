#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "../unit/StairTurner.h"
#include "./LineTracer.h"
#include "GyroSensor.h"
#include "../unit/ObstacleDitector.h"
#include "../unit/TailWalker.h"
#include "../unit/BalancingWalker.h"
#include "../unit/TailController.h"
#include "Task.h"
#include "../unit/Waker.h"

using app::Task;

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
		  Stair::unit::Waker* waker);
      void run();
      bool isDone();
      void reset();
      ~StairWalker();

    private:
      Stair::unit::StairTurner* mStairTurner;
      Stair::app::LineTracer* mLineTracer;
      Stair::unit::ObstacleDitector* mObstacleDitector;
      Stair::unit::TailWalker* mTailWalker;
      Stair::unit::BalancingWalker* mBalancingWalker;
      Stair::unit::TailController* mTailController;
      Stair::unit::Waker* mWaker;
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
        FINISH,
        STOP
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
      void execStop();
      void shortCutSpin();
    };

  }
}
#endif
