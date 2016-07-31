#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "LineTracerWithStarter.h"

class Switcher{
public:
  Switcher(LineTracerWithStarter* linetracer);
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
  Usecase mUsecase;
  void execUndefined();
  void execLineTracer();
  void execLookupGate();
  void execGarage();
  void execStair();
};

#endif