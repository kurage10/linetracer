
#include "StairWalker.h"

namespace Stair{
  namespace app{

    StairWalker::StairWalker(Stair::unit::StairTurner* stairTurner,
			     Stair::app::LineTracer* LineTracer,
			     Stair::unit::ObstacleDitector* obstacleDitector,
			     Stair::unit::TailWalker* tailWalker,
			     Stair::unit::BalancingWalker* balancingWalker,
			     Stair::unit::TailController* tailController)
      :mStairTurner(stairTurner),
       mLineTracer(LineTracer),
       mObstacleDitector(obstacleDitector),
       mTailWalker(tailWalker),
       mBalancingWalker(balancingWalker),
       mTailController(tailController),
       mState(UNDEFINED),
       timefromstart(0),
       mCount(0),
       endLine(false){
    }
    void StairWalker::run(){
      switch (mState) {
        case UNDEFINED:
          execUndefined();
	      break;
        case PREPARE:
	        execPrepare();
	      break;
        case STAY:
          execStay();
        break;
        case WALKING:
	        execWalking();
	      break;
        case CLIMBING:
	        execClimbing();
	      break;
        case TURNING:
	        execTurning();
	      break;
        default:
	      break;
      }
    }
    void StairWalker::execUndefined(){
      mLineTracer->init();
      mState=WALKING;
    }
    void StairWalker::execPrepare(){


      //mLineTracer->run(false);
      timefromstart=timefromstart+1;
      if(timefromstart > 1000){
        mTailController->run();
      }
      if(mTailController->getAngle() > 94){
        mTailController->setAngle(0);
        timefromstart=0;
        mState=WALKING;
      }
    }
    void StairWalker::execStay(){
      timefromstart=timefromstart+1;
      mTailController->run();
      mLineTracer->setStarting(true);
      mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
      mLineTracer->run();
      if(timefromstart > 250){
        mState=WALKING;
      }
    }
    void StairWalker::execWalking(){

      mLineTracer->setStarting(true);
      mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
      mLineTracer->run();
      //mTailWalker->run();
      mTailController->setAngle(0);
      mTailController->run();
      //mBalancingWalker->setCommand(BalancingWalker::NORMAL,0);
      //mBalancingWalker->run();
      if(mObstacleDitector->isObstacle() && mCount < 2){
	      timefromstart = -100;
	      mState = CLIMBING;
      }
    }
    void StairWalker::execClimbing(){
      timefromstart=timefromstart+1;
      /*if(timefromstart <= 600){
        mBalancingWalker->setCommand(-Stair::unit::BalancingWalker::LOW,0);
      }else{
        mBalancingWalker->setCommand(Stair::unit::BalancingWalker::LOW,0);
	      mTailController->setAngle(85);
	      mTailController->run();
        if(mObstacleDitector->isLanding()){
          timefromstart=0;
          mState=PREPARE_TURNING;
        }
      }
      mBalancingWalker->run();*/


      if(timefromstart <= 600){
        mBalancingWalker->setCommand(-Stair::unit::BalancingWalker::LOW,0);
	    }
      else if(timefromstart <= 1600){
	      mBalancingWalker->setCommand(Stair::unit::BalancingWalker::LOW,0);
	      mTailController->setAngle(85);
	      mTailController->run();
      }
      else if(timefromstart < 1800){

	      mBalancingWalker->setCommand(0,0);
	      mTailController->setAngle(85);
	      mTailController->run();
      }
      else if(timefromstart < 2050){
	      mBalancingWalker->setCommand(-Stair::unit::BalancingWalker::LOW,0);
      }
      else{
	      timefromstart=0;
	      mStairTurner->init();
	      //mBalancingWalker->setCommand(-BalancingWalker::LOW,-100);

	      mState=TURNING;

      }
      mBalancingWalker->run();

    }
    void StairWalker::execPrepareTurning(){
      timefromstart=timefromstart+1;
      if(timefromstart <= 200){
        //mBalancingWalker->setCommand(0,0);
        mLineTracer->setStarting(true);
        mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
        mLineTracer->run();
	      mTailController->setAngle(85);
	      mTailController->run();
	    }
      else if(timefromstart <= 400){
	      mBalancingWalker->setCommand(-Stair::unit::BalancingWalker::LOW,0);
	      mTailController->setAngle(85);
	      mTailController->run();
      }
    }
    void StairWalker::execTurning(){

      //  int speed = mStairTurner->getSpinSpeed();
      mStairTurner->run();
      if(mStairTurner->isDone()){
        mObstacleDitector->init();
        //mLineTracer->init();
        mBalancingWalker->init();
        mTailController->setAngle(100);

        timefromstart = 0;
        mCount = mCount + 1;
        mState=PREPARE;

      }

    }

    bool StairWalker::isDone(){
      if(mCount==2){
        return true;
      }else{
        return false;
      }
    }

    StairWalker::~StairWalker(){
      delete mStairTurner;
      delete mLineTracer;
      delete mObstacleDitector;
      delete mTailWalker;
      delete mBalancingWalker;
      delete mTailController;
      delete &mState;
      delete &timefromstart;
      delete &mCount;
    }
  }
}
