#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "TailWalker.h"
#include "StairTurner.h"

class StairWalker{
public:
  StairWalker(TailWalker* tailWalker,StairTurner* stairTurner);
  void run();
private:
  TailWalker* mtailWalker;
  StairTurner* mstairTurner;
  int distance=0;
  enum State {
      UNDEFINED,
      WALKING,
      TURNING
  };
  State mState;
  int mCount;
  void execUndefined();
  void execWalking();
  void execTurning();
};
#endif
