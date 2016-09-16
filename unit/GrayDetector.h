#ifndef EV3_UNIT_GRAY_DETECTOR_H_
#define EV3_UNIT_GRAY_DETECTOR_H_

#include "./LineTrace/unit/LineMonitor.h"
#include "./LineTrace/unit/BalancingWalker.h"
#include "ColorSensor.h"
#include <stdio.h>

namespace unit{

  class GrayDetector{
  public:
    GrayDetector(LineTrace::unit::LineMonitor* lineMonitor,
		 LineTrace::unit::BalancingWalker* balancingWalker,
		 const ev3api::ColorSensor& colorSensor);
    
    bool isGray();
    void init();
    
  private:
    LineTrace::unit::LineMonitor* mLineMonitor;
    LineTrace::unit::BalancingWalker* mBalancingWalker;
    const ev3api::ColorSensor& mColorSensor;

    static const int8_t TRACE_THRESHOLD;
    static const int8_t GRAY_THRESHOLD;
    static const int TIME_THRESHOLD;
    static const float KP;

    bool mDetected;
    int mCount;
    
    FILE* fp;
  };
}
#endif
