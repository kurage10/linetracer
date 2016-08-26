#ifndef EV3_UNIT_USECASE_DETECTOR_H_
#define EV3_UNIT_USECASE_DETECTOR_H_
#include "DistanceMonitor.h"

namespace unit{

  class UsecaseDetector{
  public:
    enum Usecase{
      UNDEFINED,
      LINETRACER,
      LOOKUPGATE,
      GARAGE,
      STAIR
    };
    
    UsecaseDetector(unit::DistanceMonitor* monitor);
    UsecaseDetector::Usecase nextUsecase();
    void init();

  private:
    static const int STAIR_THRESHOLD;
    static const int GATE_THRESHOLD;
    static const int GARAGE_THRESHOLD;
    
    unit::DistanceMonitor* mMonitor;
  };
}
#endif
