#include "./GarageStopper.h"

namespace Garage{
  namespace app{

    GarageStopper::GarageStopper(Garage::unit::TailWalker* tailWalker,
				 Garage::unit::Starter* starter,
				 GrayDetector* grayDetector)
      : mTailWalker(tailWalker),
	mStarter(starter),
	mGrayDetector(grayDetector),
	mState(UNDEFINED) {
    }

    GarageStopper::~GarageStopper(){
      delete mTailWalker;
      delete mStarter;
      delete mGrayDetector;
    }

    void GarageStopper::run(){

    }

    bool GarageStopper::isDone(){

    }

    void GarageStopper::execUndefined(){

    }
    
  }
}
