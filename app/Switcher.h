#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "../LineTrace/app/LineTracerWithStarter.h"
#include "../Stair/app/LineTracerWithStarter.h"
#include "../Garage/app/Stopper.h"
#include "../LookUpGate/app/LookUpGate.h"
#include "Task.h"

namespace app{

class Switcher{
public:
  Switcher(Task* linetrace,
	   Task* garage,
	   Task* stair,
	   Task* gate);
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
  Task* mLineTrace;
  Task* mGarage;
  Task* mStair;
  Task* mGate;
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
