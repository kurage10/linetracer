#include "Switcher.h"

Switcher::Switcher(LineTracerWithStarter* linetracer,StairWalker* stairWalker,TailWalker *tailWalker):
  mLineTracerWithStarter(linetracer),
  mStairWalker(stairWalker),
  mTailWalker(tailWalker),
  mUsecase(UNDEFINED){

}
void Switcher::run(){
  switch(mUsecase){
    case UNDEFINED:
      execUndefined();
    break;
    case LINETRACER:
      execLineTracer();
    break;
    case LOOKUPGATE:
      execLookupGate();
	  break;
    case GARAGE:
      execGarage();
    break;
    case STAIR:
      execStair();
    break;
    default:
    break;
  }
}
void Switcher::execUndefined(){
  //各種初期化
  mUsecase= LINETRACER;
  timeFromStart=0;
  //mUsecase= STAIR;
}
void Switcher::execLineTracer(){
  mLineTracerWithStarter->run();
  timeFromStart++;
  if(timeFromStart > 5000){
    mUsecase=STAIR;
    timeFromStart=0;
  }
}
void Switcher::execLookupGate(){

}
void Switcher::execGarage(){

}
void Switcher::execStair(){
  //mLineTracerWithStarter->run();
  //mTailWalker->run();
  mStairWalker->run();
}
