
#include "StairWalker.h"
StairWalker::StairWalker(TailWalker* tailWalker,StairTurner* stairTurner,BalancingWalker* balancingWalker)
  :mTailWalker(tailWalker),
  mStairTurner(stairTurner),
  mBalancingWalker(balancingWalker),
  mStairState(WALKING),
  timefromstart(0),
  mCount(0){
}
void StairWalker::run(){
  switch (mStairState) {
    case UNDEFINED:
      execUndefined();
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
  mTailWalker->init();
  mStairState=WALKING;
  //mStairState=TURNING;

}
void StairWalker::execWalking(){
  mTailWalker->run();
  timefromstart=timefromstart+1;
  if(timefromstart%1000==0 && mCount < 2){
    mStairState = TURNING;
  }
}
void StairWalker::execTurning(){
  mStairTurner->run();
  //mCount=mCount+1;
}
