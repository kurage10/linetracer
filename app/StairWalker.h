#ifndef EV3_APP_STAIRWALKER_H_
#define EV3_APP_STAIRWALKER_H_

#include "TailWalker.h"

class StairTurner{
public:
  StairTurner(TailWalker* tailWalker);
  void run();
private:
  TailWalker* mtailWalker;
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
}
#endif
