#ifndef EV3_LINETRACE_UNIT_WAKER_H_
#define EV3_LINETRACE_UNIT_WAKER_H_

#include "GyroSensor.h"
#include "./TailController.h"
#include "./BalancingWalker.h"
#include "ev3api.h"

namespace LineTrace{
  namespace unit{

    class Waker {
    public:
      Waker(const ev3api::GyroSensor& gyroSensor,
	    unit::TailController* tailWalker,
	    unit::BalancingWalker* balancingWalker);

      bool isWaked();

    private:
      const ev3api::GyroSensor& mGyroSensor;
      unit::TailController* mTailController;
      unit::BalancingWalker* mBalancingWalker;

      bool pushUp;
    };

  }
}

#endif
