#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "LineTracerWithStarter.h"
#include "Stopper.h"
#include "UsecaseDetector.h"

namespace app{
  
class Switcher{
public:
  Switcher(LineTrace::app::LineTracerWithStarter* linetracer,
	   unit::UsecaseDetector* usecasedetector, Stopper* stopper);
  void run();
private:
  /*  enum Usecase{
    UNDEFINED,
    LINETRACER,
    LOOKUPGATE,
    GARAGE,
    STAIR
    };*/
  
  LineTrace::app::LineTracerWithStarter* mLineTracerWithStarter;
  unit::UsecaseDetector* mUsecaseDetector;
  unit::UsecaseDetector::Usecase mUsecase;
  
  Stopper* mStopper;
  
  void execUndefined();
  void execLineTracer();
  void execLookupGate();
  void execGarage();
  void execStair();
};

}
#endif
