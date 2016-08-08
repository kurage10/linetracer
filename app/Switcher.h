#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "LineTracerWithStarter.h"
#include "StairWalker.h"
class Switcher{
public:
  Switcher(LineTracerWithStarter* linetracer,StairWalker* stairWalker,TailWalker* tailWalker);
  void run();
private:
  enum Usecase{
    UNDEFINED,
    LINETRACER,
    LOOKUPGATE,
    GARAGE,
    STAIR
  };
  LineTracerWithStarter* mLineTracerWithStarter;
  StairWalker* mStairWalker;
  TailWalker* mTailWalker;
  Usecase mUsecase;
  int timeFromStart=0;
  void execUndefined();
  void execLineTracer();
  void execLookupGate();
  void execGarage();
  void execStair();
};

#endif
