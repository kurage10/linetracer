
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
       mCount(0),
       currentStep(0) {
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
      mBalancingWalker->setCommand(0,0);
      mBalancingWalker->run();

      mCount++;
      if(mCount > 500){
	mCount = 0;
	mState=CHANGE_INTO_TAILWALK;
	ev3_speaker_play_tone(NOTE_A5,300);
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
	  if(mCount > 700){
	    mCount = 0;
	    mTailWalker->setSpeed(15);//スピードを下げる？
	    mTailWalker->setDoTrace(true);
	    mState=WALKING_WITH_TAIL;
	    ev3_speaker_play_tone(NOTE_A5,300);
	  }else{
	    mTailWalker->run();
	    mCount++;
	  }
	}
      }
    }
    void StairWalker::execTailwalking(){
      mTailWalker->run();//段への衝突を検知->一旦停止
      if(mObstacleDitector->isObstacle()){
	mTailWalker->setSpeed(-1);
	mTailWalker->setDoTrace(false);
	mCount++;
	if(mCount > 400){
	  mTailWalker->setSpeed(0);
	  mTailWalker->setAngle(100);
	}
	if(mCount > 700){
	  mCount = 0;
	  mObstacleDitector->init();
	  mTailWalker->setDoTrace(true);//added
	  mTailWalker->setSpeed(40);
	  mTailWalker->setDirection(0);
	  mTailWalker->setAngle(108);
	  //mGyroSensor.reset();
	  mState = CLIMBING;
	  ev3_speaker_play_tone(NOTE_A5,300);
	}
      }
    }
    void StairWalker::execClimbing(){
      //速度を上げて昇段->段への衝突で昇段完了を検知->execMoving()
      int speed = 10;
      
      if(mObstacleDitector->isObstacle()){
	mTailWalker->setAngle(111);//111 -> 112

	mCount++;
	if(mCount > 70){
	  speed -= (mCount - 70)/3;
	  if(speed < 0){
	    speed = 0;
	  }
	  mTailWalker->setSpeed(speed);
	  if(mCount > 500){
	    mTailWalker->setDoTrace(false);//added
	    mTailWalker->setSpeed(5);

	    if(mCount > 1150){
	      mTailWalker->setDoTrace(false);//added
	      mTailWalker->setSpeed(-7);
	      if(mCount > 1250){
		mTailWalker->setAngle(114);//116 -> 114
	      }
	      if(mCount > 1300){
		mTailWalker->setSpeed(0);
		//mLineTracer->init();
		if(mCount > 1400){
		  //mGyroSensor.reset();
		  mCount = 0;
		  currentStep++;
		  mObstacleDitector->init();
		  mState = MOVE_TO_CENTER;
		  ev3_speaker_play_tone(NOTE_A5,300);

		  mTailWalker->setSpeed(70);
		  mTailWalker->setAngle(90);
		}
	      }
	    }else{
	      if(mCount == 1100){
		mTailWalker->setSpeed(0);
	      }
	    }
	  }
	}
      }
      mTailWalker->run();
    }
    void StairWalker::execMoving(){
      //倒立走行に移って段中央へ移動->尻尾走行へ->execTurning()
      int speed = 70;//75 -> 70
      mCount++;

      if(mCount > 80){
	mTailWalker->setDoTrace(true);//added
	speed -= (mCount - 80)/1.5;
	if(speed < 0){
	  speed = 0;
	}
	mTailWalker->setSpeed(speed);
      }

      if(speed == 0 && mCount > 300){
	mTailWalker->setDoTrace(false);//added
	mTailWalker->setSpeed(-5);
	if(mTailWalker->onLine()){
	  mTailWalker->setSpeed(12);
	  mTailWalker->setDoTrace(true);//added
	  if(currentStep == 1){
	    mCount = 0;
	    mTailWalker->resetOnLine();
	    mState = WALKING_WITH_TAIL;
	    ev3_speaker_play_tone(NOTE_A5,300);
	  }
	}
      }

      mTailWalker->run();
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
