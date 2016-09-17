
#include "StairWalker.h"

namespace Stair{
  namespace app{

    StairWalker::StairWalker(Stair::unit::StairTurner* stairTurner,
			     Stair::app::LineTracer* LineTracer,
			     Stair::unit::ObstacleDitector* obstacleDitector,
			     Stair::unit::TailWalker* tailWalker,
			     Stair::unit::BalancingWalker* balancingWalker,
			     Stair::unit::TailController* tailController,
           Waker* waker)
      :mStairTurner(stairTurner),
       mLineTracer(LineTracer),
       mObstacleDitector(obstacleDitector),
       mTailWalker(tailWalker),
       mBalancingWalker(balancingWalker),
       mTailController(tailController),
       mWaker(waker),
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
        case PREPARE_CLIMB:
          execPrepareClimb();
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
      mState=PREPARE;
    }
    void StairWalker::execPrepare(){
      timefromstart=timefromstart+1;
      if(timefromstart < 250){
        mTailController->setAngle(0);
        mTailController->run();
        mLineTracer->setStarting(false);
        mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
        mLineTracer->run();
      }else{
        mState=WALKING;
        ev3_speaker_play_tone(NOTE_A5,300);
      }
    }
    void StairWalker::execStand(){
      timefromstart = timefromstart+1;
      mTailController->run();
      if(timefromstart > 500){

        mTailController->setAngle(137);
        if(mTailController->getAngle() >= 110){
          mTailController->setAngle(0);
          timefromstart=0;
          mStairTurner->init();
          mState=STAY;
          ev3_speaker_play_tone(NOTE_A5,300);

        }/*
        if(mWaker->isWaked()){
          mTailController->setAngle(0);
          timefromstart=0;
          mStairTurner->init();
          mState=STAY;
          ev3_speaker_play_tone(NOTE_A5,300);
        }*/
      }/*else{
        mTailController->run();
      }*/
    }
    void StairWalker::execWalking(){
      //timefromstart=timefromstart+1;
      mLineTracer->setStarting(false);
      mLineTracer->setSpeed(Stair::unit::BalancingWalker::LOW);
      mLineTracer->run();

      mTailController->run();
      if(mObstacleDitector->isObstacle() && mCount < 2){
        timefromstart = 0;
	      mState = PREPARE_CLIMB;
        ev3_speaker_play_tone(NOTE_A5,300);
      }
      /*if(mObstacleDitector->isDistance(160) && mCount==1){
        timefromstart = 0;
	      mState = CLIMBING;
        ev3_speaker_play_tone(NOTE_A5,300);
      }*/
    }
    void StairWalker::execStay(){
      mTailController->setAngle(0);
      mTailController->run();
      timefromstart = timefromstart+1;
      if(timefromstart < 750){
        mBalancingWalker->setCommand(0,0);
        mBalancingWalker->run();
      }else{
        timefromstart=0;
        if(mCount==2){
          mObstacleDitector->setOffset();
          mState=FINISH;
        }
        else{
          //mObstacleDitector->setOffset();
          mState=WALKING;
        }
        ev3_speaker_play_tone(NOTE_A5,300);
      }
    }
    void StairWalker::execPrepareClimb(){
      if(mObstacleDitector->isDistance(-70) && timefromstart == 0){
        mBalancingWalker->setCommand(-15,0);
        //mBalancingWalker->run();
      }else{
        timefromstart++;
      	mBalancingWalker->setCommand(0,0);
      	if(timefromstart > 1000){
      	  mState=CLIMBING;
      	  mObstacleDitector->init();
      	  timefromstart = 0;
      	  ev3_speaker_play_tone(NOTE_A5,300);
      	}
      }
      mBalancingWalker->run();
      mTailController->run();
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

        //mBalancingWalker->setCommand(10,0);


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

      if((mObstacleDitector->isDistance(215) && !mObstacleDitector->isDistance(225)) || timefromstart > 0){
      	mBalancingWalker->setCommand(0,0);
      	timefromstart++;
      	if(timefromstart > 500){
          /* スピンの準備
          mTailController->setAngle(90);
          mTailController->run();
          if(mTailController->getAngle() > 80){
            mBalancingWalker->changeMode(false);
            mState=PREPARE_TURNING;
        	  timefromstart = 0;
        	  ev3_speaker_play_tone(NOTE_A5,300);
          }*/

          shortCutSpin();
      	}
      }else if(timefromstart == 0){
	      int speed = mObstacleDitector->calcSpeed(220);
      	if(speed > unit::BalancingWalker::LOW){
      	  mBalancingWalker->setCommand(unit::BalancingWalker::LOW,0);
      	}else{
      	  mBalancingWalker->setCommand(speed,0);
      	}
      }
      mBalancingWalker->run();
      mTailController->run();
    }

    void StairWalker::execPrepareTurning(){
      mTailController->setAngle(90);
      mTailController->run();
      timefromstart++;
      /*
      if(mTailController->getAngle() > 80){
	      mBalancingWalker->changeMode(false);
      }else{
	      timefromstart = 0;
      }
      */
      if(timefromstart < 10){
	      mBalancingWalker->setCommand(0,0);
	      mBalancingWalker->run();
      }else{
      	mTailWalker->setSpeed(0);
      	mTailWalker->run();
      	if(timefromstart > 250){
      	  mState = TURNING;
      	  timefromstart = 0;
      	  ev3_speaker_play_tone(NOTE_A5,300);
      	}
      }

      /*mTailController->run();

      timefromstart=timefromstart+1;
      if(timefromstart < 500){
        mBalancingWalker->setCommand(0,0);
        mBalancingWalker->run();
        mTailController->setAngle(0);

      }else if(timefromstart < 800){
        mBalancingWalker->setCommand(-20,0);
        mBalancingWalker->run();
        mTailController->setAngle(85);
      }
      else if(timefromstart < 1100){
  	    //timefromstart=0;
  	    mStairTurner->init();
        //mBalancingWalker->init();
        //mTailWalker->init();
          	      //mBalancingWalker->setCommand(-BalancingWalker::LOW,-100);

      }else{
        mState=TURNING;
        ev3_speaker_play_tone(NOTE_A5,300);
	}*/
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
        mStairTurner->init();
        //mLineTracer->init();
        //mBalancingWalker->init();
        //mTailController->setAngle(100);
        mCount=mCount+1;
        timefromstart = 0;
        mBalancingWalker->changeMode(true);
        mState=STAND;
        ev3_speaker_play_tone(NOTE_A5,300);

      }

    }
    void StairWalker::execFinish(){

      mTailController->run();
      if(!mObstacleDitector->onStraight()){
        //mObstacleDitector->setOffset();
        mLineTracer->setStarting(true);
        mLineTracer->setSpeed(10);
        mLineTracer->run();
      }else{
        if(!mObstacleDitector->isDistance(500)){
          mBalancingWalker->setCommand(20,0);
          mBalancingWalker->run();
        }else{
          timefromstart=timefromstart+1;
          mTailController->setAngle(90);
          if(timefromstart < 250){
            mBalancingWalker->setCommand(-10,0);
            mBalancingWalker->run();
          }
          else{
            mStairTurner->init();
            isFinished=true;
            ev3_speaker_play_tone(NOTE_A5,300);
          }
        }
      }

    }
    bool StairWalker::isDone(){

      return isFinished;
    }
    void StairWalker::shortCutSpin(){
      mCount=mCount+1;
      mTailController->setAngle(0);
      if(mCount==2){
        ev3_speaker_play_tone(NOTE_A5,300);
        mObstacleDitector->setOffset();
        mState = FINISH;
      }else{
        mObstacleDitector->init();
        mState=WALKING;
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
