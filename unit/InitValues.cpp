#include "InitValues.h"

namespace unit{
  InitValues::InitValues()
    : GyroOffset() {
  }

  void InitValues::put(Name name, int value){
    switch(name){
    case GYRO_OFFSET:
      GyroOffset = value;
      break;      
    default:
      break;
    }

    return;
  }

  float InitValues::get(Name name){
    switch(name){
    case GYRO_OFFSET:
      return GyroOffset;

    default:
      return 0;
    }
  }
  
}
