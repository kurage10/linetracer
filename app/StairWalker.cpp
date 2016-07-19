
#include "StairWalker.h"
StairWalker::StairWalker(TailWalker* tailWalker)
  :mtailWalker(tailWalker),
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
  if(/*距離の条件をここに入れる*/mCount < 2){
    mState = TURNING;
  }
}
void StairWalker::execTurning(){
  mCount=mCount+1;
}
