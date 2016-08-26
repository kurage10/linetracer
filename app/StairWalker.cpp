
#include "StairWalker.h"

StairWalker::StairWalker(StairTurner* stairTurner,
  LineTracer* LineTracer,
  ObstacleDitector* obstacleDitector,
  TailWalker* tailWalker,
  BalancingWalker* balancingWalker,
  TailController* tailController)
  :mStairTurner(stairTurner),
  mLineTracer(LineTracer),
  mObstacleDitector(obstacleDitector),
  mTailWalker(tailWalker),
  mBalancingWalker(balancingWalker),
  mTailController(tailController),
  mState(UNDEFINED),
  timefromstart(0),
  mCount(0){
}
void StairWalker::run(){
  switch (mState) {
    case UNDEFINED:
      execUndefined();
    break;
    case PREPARE:
      execPrepare();
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
  mState=WALKING;
}
void StairWalker::execPrepare(){

  mTailController->setAngle(90);
  mTailController->run();
  //mLineTracer->run(false);
  timefromstart=timefromstart+1;
  mBalancingWalker->setCommand(0,0);
  mBalancingWalker->run();
  if(timefromstart>750){
    timefromstart=0;
    mState=WALKING;
  }
}
void StairWalker::execWalking(){
  mLineTracer->run(true);
  //mTailWalker->run();
  mTailController->setAngle(0);
  mTailController->run();
  //mBalancingWalker->setCommand(BalancingWalker::NORMAL,0);
  //mBalancingWalker->run();
  if(mObstacleDitector->isObstacle() && mCount < 2){
    timefromstart = 0;
    mState = CLIMBING;
  }
}
void StairWalker::execClimbing(){
  timefromstart=timefromstart+1;
  if(timefromstart <= 700){
    mBalancingWalker->setCommand(-BalancingWalker::LOW,0);
  }
  else if(timefromstart <= 1300){
    mBalancingWalker->setCommand(BalancingWalker::NORMAL,0);
    mTailController->setAngle(90);
    mTailController->run();
  }
  else if(timefromstart < 1500){
    mBalancingWalker->setCommand(0,0);
    mTailController->setAngle(90);
    mTailController->run();
  }
  else if(timefromstart < 1900){
    mBalancingWalker->setCommand(-BalancingWalker::LOW,0);
  }
  else{
    timefromstart=0;
    mStairTurner->init();
    //mBalancingWalker->setCommand(-BalancingWalker::LOW,-100);
    //mStairTurner->setSpinSpeed(10);

    mState=TURNING;

  }
  mBalancingWalker->run();
}
void StairWalker::execTurning(){
  timefromstart = timefromstart + 1;
//  int speed = mStairTurner->getSpinSpeed();
  mStairTurner->run();
  if(timefromstart < 200){
    mStairTurner->setSpinSpeed(10);
  }else if(timefromstart < 800){
    mStairTurner->setSpinSpeed(20);
  }else if(timefromstart < 1000){
    mStairTurner->setSpinSpeed(10);
  }else if(timefromstart < 1200){
    mStairTurner->setSpinSpeed(0);
  }else{
    mObstacleDitector->init();
    timefromstart = 0;
    mCount = mCount + 1;
    mState=PREPARE;
  }
}
