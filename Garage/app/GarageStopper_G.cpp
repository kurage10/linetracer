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
      switch(mState){
      case UNDEFINED:
	execUndefined();
	break;
      case TEST_START:
	execTestStart();
	break;
      case GRAY:
	execGray();
	break;
      case STOP:
	execStop();
	break;
      default:
	break;
      }
    }

    bool GarageStopper::isDone(){
      return false;
    }

    void GarageStopper::execUndefined(){
      mTailWalker->init();
      mGrayDetector->init();
      mGrayDetector->setTraceThreshold(8);

      mState = TEST_START;//For testing
      mTailWalker->setSpeed(0);
      
      //mState = GRAY;//For on going
    }

    void GarageStopper::execTestStart(){
      mTailWalker->run();
      
      if(mStarter->isPushed()){
	mTailWalker->setSpeed(20);
	ev3_speaker_play_tone(NOTE_A5,300);
	mState = GRAY;
      }
    }

    void GarageStopper::execGray(){
      if(mGrayDetector->isGray()){
	mTailWalker->init();
	mState = STOP;
      }
    }

    void GarageStopper::execStop(){
      mTailWalker->run();
    }
    
  }
}
