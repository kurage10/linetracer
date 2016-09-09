#include "Switcher.h"

namespace app{
<<<<<<< HEAD
  
  Switcher::Switcher(LineTrace::app::LineTracerWithStarter* linetracer,
		     unit::UsecaseDetector* usecasedetector, Stopper* stopper):
  mLineTracerWithStarter(linetracer),
  mUsecaseDetector(usecasedetector), 
  mUsecase(unit::UsecaseDetector::UNDEFINED),
  mStopper(stopper){
=======

  Switcher::Switcher(Task* linetracer):
  mLineTracerWithStarter(linetracer),
  mUsecase(UNDEFINED){
>>>>>>> refs/remotes/origin/master

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
<<<<<<< HEAD
  mStopper->run();
  mUsecase = mUsecaseDetector->nextUsecase();
=======
  //mUsecase = mUsecaseDetector->nextUsecase();
>>>>>>> refs/remotes/origin/master
}
void Switcher::execStair(){
  //mUsecase = mUsecaseDetector->nextUsecase();
}

}
