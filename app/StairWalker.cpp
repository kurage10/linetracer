
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

  mTailController->setAngle(0);
  mTailController->run();
  //mLineTracer->run(false);
  timefromstart=timefromstart+1;
  mBalancingWalker->setCommand(0,0);
  mBalancingWalker->run();
  if(timefromstart>3000){
    mState=WALKING;
    timefromstart=0;
  }
}
void StairWalker::execWalking(){
  //mLineTracer->run(false);
  //mTailWalker->run();
  mTailController->setAngle(0);
  mTailController->run();

  if(mObstacleDitector->isObstacle()){
    timefromstart=timefromstart+1;
    mBalancingWalker->run();
    if(timefromstart > 100)mBalancingWalker->setCommand(0,0);
    if(timefromstart > 700){
      mStairTurner->init();
      mState=TURNING;
    }
  }else{
    mBalancingWalker->setCommand(BalancingWalker::NORMAL,0);
    mBalancingWalker->run();
  }
}
void StairWalker::execTurning(){

  timefromstart=timefromstart+1;
  mStairTurner->run();
  if(timefromstart > 1900){
    mObstacleDitector->init();
    mStairTurner->init();
    timefromstart=0;
    mState=PREPARE;
  }
}
