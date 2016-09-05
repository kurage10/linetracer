
#include "StairWalker.h"
#include <stdio.h>

namespace Stair{
  namespace app{

    StairWalker::StairWalker(Stair::unit::StairTurner* stairTurner,
			     Stair::app::LineTracer* LineTracer,
			     Stair::unit::ObstacleDitector* obstacleDitector,
			     Stair::unit::TailWalker* tailWalker,
			     Stair::unit::BalancingWalker* balancingWalker,
			     Stair::unit::TailController* tailController,
			     ev3api::GyroSensor& gyroSensor)
      :mStairTurner(stairTurner),
       mLineTracer(LineTracer),
       mObstacleDitector(obstacleDitector),
       mTailWalker(tailWalker),
       mBalancingWalker(balancingWalker),
       mTailController(tailController),
       mGyroSensor(gyroSensor), 
       mState(UNDEFINED),
       mCount(0){
      fp = fopen("AnglerVelocityLog.txt","w");
    }
    void StairWalker::run(){
      switch (mState) {
      case UNDEFINED:
	execUndefined();
	break;
      case CHANGE_INTO_TAILWALK:
	execChangeIntoTailwalk();
	break;
      case WALKING_WITH_TAIL:
	execTailwalking();
	break;
      case CLIMBING:
	execClimbing();
	break;
      case MOVE_TO_CENTER:
	execMoving();
	break;
      case TURNING:
	execTurning();
	break;
      case WALKING_WITHOUT_TAIL:
	execWalking();
	break;
      case GET_OFF:
	execGetOff();
	break;
      default:
	break;
      }
    }
    
    void StairWalker::execUndefined(){
      //mGyroSensor.reset();
      mBalancingWalker->setCommand(0,0);
      mBalancingWalker->run();

      mCount++;
      if(mCount > 250){
	mCount = 0;
	mState=CHANGE_INTO_TAILWALK;
      }
    }
    void StairWalker::execChangeIntoTailwalk(){
      if(mTailController->getAngle() <= 75){
	mTailController->setAngle(90);
	mTailController->run();
	
	mBalancingWalker->setCommand(0,0);
	mBalancingWalker->run();
      }else{
	if(mCount < 400){
	  mBalancingWalker->setCommand(-35,0);
	  mBalancingWalker->run();
	  mTailController->run();
	  mCount++;
	}else{
	  mTailWalker->setSpeed(0);
	  mTailWalker->setAngle(90);
	  mTailController->run();
	  mCount = 0;
	  mState=WALKING_WITH_TAIL;
	}
      }
    }
    void StairWalker::execTailwalking(){
      mTailWalker->run();
    }
    void StairWalker::execClimbing(){

    }
    void StairWalker::execMoving(){

    }
    void StairWalker::execTurning(){

    }
    void StairWalker::execWalking(){

    }
    void StairWalker::execGetOff(){

    }

    bool StairWalker::isDone(){
      //code
      return false;
    }

    StairWalker::~StairWalker(){
      delete mStairTurner;
      delete mLineTracer;
      delete mObstacleDitector;
      delete mTailWalker;
      delete mBalancingWalker;
      delete mTailController;
      delete &mState;
      delete &mCount;
    }
  }
} 
