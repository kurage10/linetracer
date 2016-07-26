
#include "StairWalker.h"
StairWalker::StairWalker(TailWalker* tailWalker,StairTurner* stairTurner)
  :mtailWalker(tailWalker),
  mstairTurner(stairTurner),
  mState(UNDEFINED),
  mCount(0){
}
void StairWalker::run(){
  switch (mState) {
    case UNDEFINED:
      execUndefined();
    break;
    case WALKING:
      execWalking();
    break;
    case TURNING:
      execTurning();
    break;
  }
}
void StairWalker::execUndefined(){
  mState=WALKING;
}
void StairWalker::execWalking(){
  mtailWalker->run();
  distance=distance+1;
  if(distance%1000==0 && mCount < 2){
    mState = TURNING;
  }
}
void StairWalker::execTurning(){
  mstairTurner->run();
  //mCount=mCount+1;
}
