#include "GrayDetector.h"

namespace unit{
  const int8_t GrayDetector::TRACE_THRESHOLD = 28;
  const int8_t GrayDetector::GRAY_THRESHOLD = 7;
  const int GrayDetector::TIME_THRESHOLD = 350;
  const float GrayDetector::KP = 2.00;
  
  GrayDetector::GrayDetector(LineTrace::unit::LineMonitor* lineMonitor,
			     LineTrace::unit::BalancingWalker* balancingWalker,
			     const ev3api::ColorSensor& colorSensor)
    :mLineMonitor(lineMonitor),
     mBalancingWalker(balancingWalker),
     mColorSensor(colorSensor),
     mDetected(false),
     mCount() {
    fp = fopen("GrayLog.csv","w");
    fprintf(fp,"Brightness\n");
  }

  bool GrayDetector::isGray(){
    int8_t Brightness = mColorSensor.getBrightness() - TRACE_THRESHOLD;
    
    mBalancingWalker->setCommand(20, -1 * KP * Brightness);
    mBalancingWalker->run();

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
  
}
