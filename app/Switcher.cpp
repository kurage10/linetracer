#include "Switcher.h"

namespace app{
  Switcher::Switcher(Task* linetrace,
		     Task* garage,
		     Task* stair,
		     Task* gate):
    mLineTrace(linetrace),
    mGarage(garage),
    mStair(stair),
    mGate(gate),
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
    //mUsecase = LINETRACER;
    mUsecase = GARAGE;
  }
  void Switcher::execLineTracer(){
    mLineTrace->run();
    if(mLineTrace -> isDone()){
      mUsecase = STAIR;
    }
  }
  void Switcher::execLookupGate(){
    mGate->run();
    if(mGate -> isDone()){
      mUsecase = GARAGE;
    }
  }
  void Switcher::execGarage(){
    mGarage->run();
    if(mGarage -> isDone()){
      mUsecase = GARAGE;
    }
  }
  void Switcher::execStair(){
    mStair->run();
    if(mStair -> isDone()){
      mUsecase = GARAGE;
    }
  }
}
