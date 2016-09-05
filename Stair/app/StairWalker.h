#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "GyroSensor.h"
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
		  Stair::unit::TailController* tailController,
		  ev3api::GyroSensor& gyroSensor);
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
      ev3api::GyroSensor& mGyroSensor;
      enum State {
	UNDEFINED,
	CHANGE_INTO_TAILWALK,
	WALKING_WITH_TAIL,
	CLIMBING,
	MOVE_TO_CENTER, 
	TURNING,
	WALKING_WITHOUT_TAIL, 
	GET_OFF
      };
      State mState;
      int mCount;
      void execUndefined();
      void execChangeIntoTailwalk();
      void execTailwalking();
      void execClimbing();
      void execMoving();
      void execTurning();
      void execWalking();
      void execGetOff();

      FILE* fp;
    };
  }
}
#endif
