#ifndef EV3_GARAGE_APP_GARAGE_STOPPER_H_
#define EV3_GARAGE_APP_GARAGE_STOPPER_H_

#include "../unit/TailWalker.h"
#include "../unit/TailController.h"
#include "../unit/LineMonitor.h"
#include "../unit/Starter.h"
#include "GrayDetector.h"
#include "Task.h"

using app::Task;
using unit::GrayDetector;

namespace Garage{
  namespace app{

    class GarageStopper : public Task{
    public:
      GarageStopper(Garage::unit::TailWalker* tailWalker,
		    Garage::unit::Starter* starter,
		    GrayDetector* grayDetector);
      ~GarageStopper();
      
      void run();
      bool isDone();
      
    private:
      enum State{
	UNDEFINED,
	TEST_START,//For testing
	GRAY,
	STOP
      };

      void execUndefined();
      void execTestStart();
      void execGray();
      void execStop();

      Garage::unit::TailWalker* mTailWalker;
      Garage::unit::Starter* mStarter;
      GrayDetector* mGrayDetector;

      State mState;
    };
    
  }
}

#endif
