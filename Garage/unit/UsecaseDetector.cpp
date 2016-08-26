#include "UsecaseDetector.h"

namespace unit{

  const int UsecaseDetector::STAIR_THRESHOLD = 1000;
  const int UsecaseDetector::GATE_THRESHOLD = 2000;
  const int UsecaseDetector::GARAGE_THRESHOLD = 3000;
  
  UsecaseDetector::UsecaseDetector(unit::DistanceMonitor* monitor)
    : mMonitor(monitor){
  }

  UsecaseDetector::Usecase UsecaseDetector::nextUsecase(){
    int currentDistance = mMonitor->measure();

    if(currentDistance > GARAGE_THRESHOLD){
      return GARAGE;
    }

    if(currentDistance > GATE_THRESHOLD){
      return LOOKUPGATE;
    }

    if(currentDistance > STAIR_THRESHOLD){
      return STAIR;
    }

    return LINETRACER;
  }

  void UsecaseDetector::init(){
    mMonitor->init();
  }
}
