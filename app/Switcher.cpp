#include "Switcher.h"

Switcher::Switcher(LineTracerWithStarter* linetracer,StairWalker* stairWalker):
  mLineTracerWithStarter(linetracer),
  mStairWalker(stairWalker),
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
  //mUsecase= LINETRACER;
  mUsecase= STAIR;
}
void Switcher::execLineTracer(){
  mLineTracerWithStarter->run();
}
void Switcher::execLookupGate(){

}
void Switcher::execGarage(){

}
void Switcher::execStair(){
  mStairWalker->run();
}
