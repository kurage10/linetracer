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
		  Stair::unit::TailController* tailController);
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
      enum State {
	UNDEFINED,
	PREPARE,
	WALKING,
	CLIMBING,
	TURNING
      };
      State mState;
      int timefromstart;
      int mCount;
      void execUndefined();
      void execPrepare();
      void execWalking();
      void execClimbing();
      void execTurning();
    };

  }
}
#endif
