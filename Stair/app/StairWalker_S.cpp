
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
       isFinished(false),
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
        case STAND:
          execStand();
        break;
        case WALKING:
	        execWalking();
	      break;
        case CLIMBING:
	        execClimbing();
	      break;
        case PREPARE_TURNING:
          execPrepareTurning();
        break;
        case TURNING:
	        execTurning();
	      break;
        case FINISH:
          execFinish();
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

      /*
      timefromstart=timefromstart+1;
      if(timefromstart > 1000){
        mTailController->run();
      }
      if(mTailController->getAngle() > 94){
        mTailController->setAngle(0);
        timefromstart=0;
        if(mCount==2){
          mState=FINISH;
        }else{
          mState=STAY;
        }
      }*/
      mTailController->run();
      if(!mObstacleDitector->isObstacle()){
        mLineTracer->setStarting(false);
        mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
        mLineTracer->run();
      }else{
        mState=STAND;
      }
    }
    void StairWalker::execStand(){
      mTailController->run();
      if(!mObstacleDitector->isDistance(-60)){
        mBalancingWalker->setCommand(-20,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);
      }else{
        timefromstart = 0;
        mStairTurner->init();
        mTailController->setAngle(100);
        if(mTailController->getAngle() > 94){
          mTailController->setAngle(0);
          timefromstart=0;
          if(mCount==2){
            mState=FINISH;
          }else{
            mState=CLIMBING;
          }
        }
      }
    }
    void StairWalker::execWalking(){

      mLineTracer->setStarting(false);
      mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
      mLineTracer->run();
      //mTailWalker->run();
      mTailController->setAngle(0);
      mTailController->run();
      //mBalancingWalker->setCommand(BalancingWalker::NORMAL,0);
      //mBalancingWalker->run();
      if(mObstacleDitector->isObstacle() && mCount < 2){
	      //timefromstart = 1300;
        timefromstart = 0;
	      mState = CLIMBING;
      }
    }
    void StairWalker::execStay(){

      mTailController->run();
      /*
      if(timefromstart <= 600){
        mLineTracer->setStarting(true);
        mLineTracer->setSpeed(10);
        mLineTracer->run();
      }else if(timefromstart <= 1000){
        mBalancingWalker->setCommand(0,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);

      }else if(timefromstart <= 1150){
        mBalancingWalker->setCommand(-20,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);
      }else{
        mStairTurner->init();
        mBalancingWalker->init();
        timefromstart = 0;
        mState = PREPARE_TURNING;
      }*/
      if(!mObstacleDitector->isDistance(210)){
        mLineTracer->setStarting(true);
        mLineTracer->setSpeed(10);
        mLineTracer->run();
      }else{
        timefromstart=timefromstart+1;
        if(timefromstart <= 400){
          mBalancingWalker->setCommand(0,0);
          mBalancingWalker->run();
          mTailController->setAngle(85);
        }
        else if(timefromstart <= 550){
          mBalancingWalker->setCommand(-20,0);
          mBalancingWalker->run();
          mTailController->setAngle(85);
        }
        else{
          mStairTurner->init();
          mBalancingWalker->init();
          timefromstart = 0;
          mState = PREPARE_TURNING;
        }
      }
    }

    void StairWalker::execClimbing(){
      //timefromstart=timefromstart+1;
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

      if(!mObstacleDitector->isDistance(210)){
        mBalancingWalker->setCommand(Stair::unit::BalancingWalker::LOW,0);
        mBalancingWalker->run();
        mTailController->setAngle(0);
      }else{
        mState=PREPARE_TURNING;
      }
      mTailController->run();
      /*最強
     if(timefromstart <= 1600){
	      mBalancingWalker->setCommand(Stair::unit::BalancingWalker::LOW,0);
        mBalancingWalker->run();
	      mTailController->setAngle(0);

      }else if(timefromstart < 2000){
        mBalancingWalker->setCommand(0,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);

      }else if(timefromstart < 2150){
        mBalancingWalker->setCommand(-20,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);
      }
      else{
	      timefromstart=0;
	      mStairTurner->init();
        mBalancingWalker->init();
        mTailWalker->init();
	      //mBalancingWalker->setCommand(-BalancingWalker::LOW,-100);

	      mState=PREPARE_TURNING;

      }
      */


    }
    void StairWalker::execPrepareTurning(){
      mTailController->run();

      timefromstart=timefromstart+1;
      if(timefromstart < 400){
        mBalancingWalker->setCommand(0,0);
        mBalancingWalker->run();
        mTailController->setAngle(0);

      }else if(timefromstart < 700){
        mBalancingWalker->setCommand(-20,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);
      }
      else if(timefromstart < 1000){
  	    //timefromstart=0;
  	    mStairTurner->init();
        //mBalancingWalker->init();
        //mTailWalker->init();
          	      //mBalancingWalker->setCommand(-BalancingWalker::LOW,-100);

      }else{
        mState=TURNING;
      }
      /*
      timefromstart=timefromstart+1;
      if(timefromstart > 500){
        mState=TURNING;
      }*/

    }
    void StairWalker::execTurning(){

      //  int speed = mStairTurner->getSpinSpeed();
      mStairTurner->run();
      if(mStairTurner->isDone()){
        mObstacleDitector->init();
        //mLineTracer->init();
        mBalancingWalker->init();
        mTailController->setAngle(85);
        mCount=mCount+1;
        timefromstart = 0;
        mState=PREPARE;

      }

    }
    void StairWalker::execFinish(){
      timefromstart=timefromstart+1;
      mTailController->run();
      mLineTracer->setStarting(true);
      mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
      mLineTracer->run();
      if(timefromstart > 1000){
        isFinished=true;
      }
    }
    bool StairWalker::isDone(){

      return isFinished;
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
