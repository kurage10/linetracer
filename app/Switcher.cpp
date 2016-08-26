#include "Switcher.h"

namespace app{
  
  Switcher::Switcher(LineTrace::app::LineTracerWithStarter* linetracer,
		     unit::UsecaseDetector* usecasedetector,
         LookUpGate::app::LookUpGate* lookupgate):
  mLineTracerWithStarter(linetracer),
  mUsecaseDetector(usecasedetector), 
  mUsecase(unit::UsecaseDetector::UNDEFINED),
  mLookUpGate(lookupgate){

}
void Switcher::run(){
  switch(mUsecase){
    case unit::UsecaseDetector::UNDEFINED:
      execUndefined();
      break;
    case unit::UsecaseDetector::LINETRACER:
      execLineTracer();
      break;
    case unit::UsecaseDetector::LOOKUPGATE:
      execLookupGate();
      break;
    case unit::UsecaseDetector::GARAGE:
      execGarage();
      break;
    case unit::UsecaseDetector::STAIR:
      execStair();
      break;
    default:
      break;
  }
}
void Switcher::execUndefined(){
  //各種初期化
  mUsecase= unit::UsecaseDetector::LINETRACER;
  mUsecaseDetector->init();
}
void Switcher::execLineTracer(){
  mLineTracerWithStarter->run();
  mUsecase = mUsecaseDetector->nextUsecase();
}
void Switcher::execLookupGate(){
  mLookUpGate->run();
  mUsecase = mUsecaseDetector->nextUsecase();
}
void Switcher::execGarage(){
  mUsecase = mUsecaseDetector->nextUsecase();
}
void Switcher::execStair(){
  mUsecase = mUsecaseDetector->nextUsecase();
}

}
