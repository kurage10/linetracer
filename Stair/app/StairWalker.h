#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "StairTurner.h"
#include "LineTracer.h"
#include "GyroSensor.h"
#include "ObstacleDitector.h"
#include "TailWalker.h"
#include "BalancingWalker.h"
#include "TailController.h"

class StairWalker{
public:
  StairWalker(StairTurner* stairTurner,
    LineTracer* lineTracer,
    ObstacleDitector* obstacleDitector,
    TailWalker* tailWalker,
    BalancingWalker* balancingWalker,
    TailController* tailController);
  void run();
private:
  StairTurner* mStairTurner;
  LineTracer* mLineTracer;
  ObstacleDitector* mObstacleDitector;
  TailWalker* mTailWalker;
  BalancingWalker* mBalancingWalker;
  TailController* mTailController;
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
#endif
