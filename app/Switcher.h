#ifndef EV3_APP_SWITCHER_H_
#define EV3_APP_SWITCHER_H_
#include "LineTracerWithStarter.h"
<<<<<<< HEAD
#include "Stopper.h"
#include "UsecaseDetector.h"
=======
#include "Task.h"
>>>>>>> refs/remotes/origin/master

namespace app{

class Switcher{
public:
<<<<<<< HEAD
  Switcher(LineTrace::app::LineTracerWithStarter* linetracer,
	   unit::UsecaseDetector* usecasedetector, Stopper* stopper);
=======
  Switcher(Task* linetracer);
>>>>>>> refs/remotes/origin/master
  void run();
private:
  enum Usecase{
    UNDEFINED,
    LINETRACER,
    LOOKUPGATE,
    GARAGE,
    STAIR
<<<<<<< HEAD
    };*/
  
  LineTrace::app::LineTracerWithStarter* mLineTracerWithStarter;
  unit::UsecaseDetector* mUsecaseDetector;
  unit::UsecaseDetector::Usecase mUsecase;
  
  Stopper* mStopper;
  
=======
  };

  //LineTrace::app::LineTracerWithStarter* mLineTracerWithStarter;
  Task* mLineTracerWithStarter;
//  unit::UsecaseDetector* mUsecaseDetector;
  Usecase mUsecase;
>>>>>>> refs/remotes/origin/master
  void execUndefined();
  void execLineTracer();
  void execLookupGate();
  void execGarage();
  void execStair();
};

}
#endif
