#ifndef EV3_UNIT_GRAY_DETECTOR_H_
#define EV3_UNIT_GRAY_DETECTOR_H_

#include "../LineTrace/unit/LineMonitor.h"
#include "../LineTrace/unit/BalancingWalker.h"
#include "../Garage/unit/TailWalker.h"
#include "ColorSensor.h"
#include <stdio.h>

namespace unit{

  class GrayDetector{
  public:
    GrayDetector(LineTrace::unit::LineMonitor* lineMonitor,
		 LineTrace::unit::BalancingWalker* balancingWalker,
		 Garage::unit::TailWalker* tailWalker,
		 const ev3api::ColorSensor& colorSensor);
    
    bool isGray();
    void init();
    void setTraceThreshold(int8_t threshold);
    void setGrayThreshold(int8_t threshold);
    void setTimeThreshold(int threshold);
    
  private:
    LineTrace::unit::LineMonitor* mLineMonitor;
    LineTrace::unit::BalancingWalker* mBalancingWalker;
    Garage::unit::TailWalker* mTailWalker;
    const ev3api::ColorSensor& mColorSensor;

    static int8_t TRACE_THRESHOLD;
    static int8_t GRAY_THRESHOLD;
    static int TIME_THRESHOLD;
    static const float KP_Balance;
    static const float KP_Tail;

    bool mDetected;
    int mCount;
    
    FILE* fp;
  };
}
#endif
