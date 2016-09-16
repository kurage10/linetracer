#include "GrayDetector.h"

namespace unit{
  int8_t GrayDetector::TRACE_THRESHOLD = 28;
  int8_t GrayDetector::GRAY_THRESHOLD = 7;
  int GrayDetector::TIME_THRESHOLD = 350;
  const float GrayDetector::KP_Balance = 2.00;
  const float GrayDetector::KP_Tail = 4.00;
  
  GrayDetector::GrayDetector(LineTrace::unit::LineMonitor* lineMonitor,
			     LineTrace::unit::BalancingWalker* balancingWalker,
			     Garage::unit::TailWalker* tailWalker,
			     const ev3api::ColorSensor& colorSensor)
    :mLineMonitor(lineMonitor),
     mBalancingWalker(balancingWalker),
     mTailWalker(tailWalker),
     mColorSensor(colorSensor),
     mDetected(false),
     mCount() {
    fp = fopen("GrayLog.csv","w");
    fprintf(fp,"Brightness\n");
  }

  bool GrayDetector::isGray(){
    int8_t Brightness = mColorSensor.getBrightness() - TRACE_THRESHOLD;

    if(TRACE_THRESHOLD == 28){
      mBalancingWalker->setCommand(20, -1 * KP_Balance * Brightness);
      mBalancingWalker->run();
    }else{
      mTailWalker->setDirection(-1 * KP_Tail * Brightness);
      mTailWalker->run();
    }

    fprintf(fp,"%d\n",Brightness);
    if(Brightness*Brightness < GRAY_THRESHOLD*GRAY_THRESHOLD){
      mCount++;
    }else{
      if(mCount > TIME_THRESHOLD){
	ev3_speaker_play_tone(NOTE_A5,300);
	mDetected = true;
      }else{
	mCount = 0;
      }
    }

    return mDetected;
  }

  void GrayDetector::init(){
    mDetected = false;
    mCount = 0;
  }

  void GrayDetector::setTraceThreshold(int8_t threshold){
    TRACE_THRESHOLD = threshold;
  }

  void GrayDetector::setGrayThreshold(int8_t threshold){
    GRAY_THRESHOLD = threshold;
  }

  void GrayDetector::setTimeThreshold(int threshold){
    TIME_THRESHOLD = threshold;
  }
  
}
