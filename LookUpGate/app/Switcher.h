#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "LineTracerWithStarter.h"
#include "UsecaseDetector.h"
#include "LookUpGate.h"

namespace app{
  
class Switcher{
public:
  Switcher(LineTrace::app::LineTracerWithStarter* linetracer,
	   unit::UsecaseDetector* usecasedetector,
     LookUpGate::app::LookUpGate* lookupgate);
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
  LookUpGate::app::LookUpGate* mLookUpGate;
  void execUndefined();
  void execLineTracer();
  void execLookupGate();
  void execGarage();
  void execStair();
};

}
#endif
