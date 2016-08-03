#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "TailWalker.h"
#include "StairTurner.h"
#include "BalancingWalker.h"

class StairWalker{
public:
  StairWalker(TailWalker* tailWalker,StairTurner* stairTurner,BalancingWalker* balancingWalker);
  void run();
private:
  TailWalker* mTailWalker;
  StairTurner* mStairTurner;
  BalancingWalker* mBalancingWalker;
  enum StairState {
      UNDEFINED,
      WALKING,
      TURNING
  };
  StairState mStairState;
  int timefromstart;
  int mCount;
  void execUndefined();
  void execWalking();
  void execTurning();
};
#endif
