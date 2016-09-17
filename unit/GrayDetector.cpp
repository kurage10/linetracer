#include "GrayDetector.h"

namespace unit{
  int8_t GrayDetector::TRACE_THRESHOLD = 28;
  int8_t GrayDetector::GRAY_THRESHOLD = 7;
  int GrayDetector::TIME_THRESHOLD = 350;
  const float GrayDetector::KP_Balance = 2.00;
  const float GrayDetector::KP_Tail = 20.0;//25で振動(20~25?):24.5?//speed20で15.0//20?
  
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
    fprintf(fp,"%d\n",Brightness);

    
    if(TRACE_THRESHOLD > 20){
      mBalancingWalker->setCommand(20, -1 * KP_Balance * Brightness);
      mBalancingWalker->run();

      if(Brightness*Brightness <= GRAY_THRESHOLD*GRAY_THRESHOLD){
	mCount++;
      }else{
	if(mCount > TIME_THRESHOLD){
	  ev3_speaker_play_tone(NOTE_A5,300);
	  mDetected = true;
	}else{
	  mCount = 0;
	}
      }
      
    }else{
      mTailWalker->setSpeed(10);
      if(Brightness > 0){
	mTailWalker->setDirection(-1 * KP_Tail * Brightness * Brightness);
      }else{
	mTailWalker->setDirection(KP_Tail * Brightness * Brightness);
      }
      mTailWalker->run();

      if(Brightness >= -1*GRAY_THRESHOLD){
	mCount++;
      }else{
	if(mCount > TIME_THRESHOLD){
	  ev3_speaker_play_tone(NOTE_A5,300);
	  mDetected = true;
	}else{
	  mCount = 0;
	}
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