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
	  if(mCount > 500){
	    mCount = 0;
	    mTailWalker->setSpeed(15);//スピードを下げる？
	    mTailWalker->setDoTrace(true);
	    mState=WALKING_WITH_TAIL;
	  }else{
	    mTailWalker->run();
	    mCount++;
	  }
	}
      }
    }
    void StairWalker::execTailwalking(){
      mTailWalker->run();//距離で段への衝突を検知->一旦停止
      if(mObstacleDitector->isObstacle()){
	mTailWalker->setSpeed(-5);
	mTailWalker->setDoTrace(false);
	mCount++;
	if(mCount > 500){
	  mTailWalker->setSpeed(0);
	}
	if(mCount > 1000){
	  mCount = 0;
	  mTailWalker->setSpeed(30);
	  mGyroSensor.reset();
	  mState = CLIMBING;
	}
      }
    }
    void StairWalker::execClimbing(){
      mTailWalker->run();
      if(mGyroSensor.getAngle() < -3){
	mGyroSensor.reset();
	mTailWalker->setSpeed(0);
	mTailWalker->setDoTrace(true);
	mState = MOVE_TO_CENTER;
      }
      //速度を上げて昇段->走行体の角度で昇段完了を検知->execMoving()
    }
    void StairWalker::execMoving(){
      mTailWalker->run();
      //倒立走行に移って段中央へ移動->尻尾走行へ->execTurning()
    }
    void StairWalker::execTurning(){
      //スピン->一定角回転後にラインエッジを検知したら終了->(1段目)execClimbing()
      //(2段目)execWalking()
    }
    void StairWalker::execWalking(){
      //倒立走行に移る->ラインが黒から白になったタイミングでexecGetOff()
    }
    void StairWalker::execGetOff(){
      //ライントレースせずに直進->降段完了を検知->ラインを検出後isDone()をtrue
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
