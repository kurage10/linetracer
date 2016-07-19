
#include "StairWalker.h"
StairWalker::StairWalker(TailWalker* tailWalker)
  :mtailWalker(tailWalker),
  mCount(0){
}
StairWalker::run(){
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
StairWalker::execUndefined(){
  mState=WALKING;
}
StairWalker::execWalking(){
  tailWalker->run();
  if(/*距離の条件をここに入れる*/mCount < 2){
    mState = TURNING;
  }
}
StairWalker::execTurning(){

}
