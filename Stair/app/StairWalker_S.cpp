
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
      if(timefromstart < 1000){
        mTailController->run();
        mTailController->setAngle(0);
        mBalancingWalker->setCommand(0,0);
        mBalancingWalker->run();
      }else{
        mState=WALKING;
      }
    }
    void StairWalker::execStand(){
      timefromstart = timefromstart+1;
      mTailController->run();
      if(timefromstart > 500){
        mTailController->setAngle(100);
        if(mTailController->getAngle() >= 96){
          mTailController->setAngle(0);
          timefromstart=0;

          mStairTurner->init();
          mState=STAY;
          ev3_speaker_play_tone(NOTE_A5,300);

        }
      }
    }
    void StairWalker::execWalking(){
      timefromstart=timefromstart+1;
      mLineTracer->setStarting(false);
      mLineTracer->setSpeed(/*Stair::unit::BalancingWalker::LOW*/10);
      mLineTracer->run();
      //mTailWalker->run();
      mTailController->setAngle(0);
      mTailController->run();
      //mBalancingWalker->setCommand(BalancingWalker::NORMAL,0);
      //mBalancingWalker->run();
      if(mObstacleDitector->isObstacle() && mCount < 2){
	      //timefromstart = 1300;
        timefromstart = 0;
	      //mState = PREPARE_CLIMB;
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
      if(!mObstacleDitector->isDistance(-30)){
        mBalancingWalker->setCommand(-10,0);
        mBalancingWalker->run();
      }else{
        timefromstart = 0;
        ev3_speaker_play_tone(NOTE_A5,300);
        mState=CLIMBING;
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

      if(!mObstacleDitector->isDistance(180)){
        //mBalancingWalker->setCommand(Stair::unit::BalancingWalker::LOW,0);
        mBalancingWalker->setCommand(10,0);
        mBalancingWalker->run();
        mTailController->setAngle(0);
      }else{
        timefromstart=0;
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
        ev3_speaker_play_tone(NOTE_A5,300);
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
        mStairTurner->init();
        //mLineTracer->init();
        //mBalancingWalker->init();
        //mTailController->setAngle(100);
        mCount=mCount+1;
        timefromstart = 0;
        mState=STAND;
        ev3_speaker_play_tone(NOTE_A5,300);

      }

    }
    void StairWalker::execFinish(){
      timefromstart=timefromstart+1;
      mTailController->run();
      if(timefromstart < 500){
        mLineTracer->setStarting(true);
        mLineTracer->setSpeed(10);
        mLineTracer->run();
      }else{
        if(!mObstacleDitector->isDistance(300)){
          mBalancingWalker->setCommand(20,0);
          mBalancingWalker->run();
        }else{
          isFinished=true;
          ev3_speaker_play_tone(NOTE_A5,300);
        }
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
