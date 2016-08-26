#include "Switcher.h"

namespace app{

  Switcher::Switcher(Task* linetracer):
  mLineTracerWithStarter(linetracer),
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
  mUsecase = LINETRACER;
  //mUsecaseDetector->init();
}
void Switcher::execLineTracer(){
  mLineTracerWithStarter->run();
  if(mLineTracerWithStarter -> isDone()){
    mUsecase = LOOKUPGATE;
  }
/*
  if(mUsecaseDetector->nextUsecase()){
    mUsecase = xxxx
  }*/
}
void Switcher::execLookupGate(){
  //mUsecase = mUsecaseDetector->nextUsecase();
}
void Switcher::execGarage(){
  //mUsecase = mUsecaseDetector->nextUsecase();
}
void Switcher::execStair(){
  //mUsecase = mUsecaseDetector->nextUsecase();
}

}
