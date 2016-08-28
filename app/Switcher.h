#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "LineTracerWithStarter.h"
#include "Stopper.h"
#include "Task.h"

namespace app{

class Switcher{
public:
  Switcher(Task* linetracer,
	   Task* stopper,
	   Task* stairwalker);
  void run();
private:
  enum Usecase{
    UNDEFINED,
    LINETRACER,
    LOOKUPGATE,
    GARAGE,
    STAIR
  };

  //LineTrace::app::LineTracerWithStarter* mLineTracerWithStarter;
  Task* mLineTracerWithStarter;
  Task* mStopper;
  Task* mStairWalker;
//  unit::UsecaseDetector* mUsecaseDetector;
  Usecase mUsecase;
  void execUndefined();
  void execLineTracer();
  void execLookupGate();
  void execGarage();
  void execStair();
};

}
#endif
