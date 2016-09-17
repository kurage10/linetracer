#ifndef EV3_STAIR_UNIT_WAKER_H_
#define EV3_STAIR_UNIT_WAKER_H_

#include "./TailController.h"
#include "./BalancingWalker.h"
#include "ev3api.h"

namespace Stair{
  namespace unit{

    class Waker {
    public:
      Waker(unit::TailController* tailWalker,
	    unit::BalancingWalker* balancingWalker);

      bool isWaked();

    private:
      unit::TailController* mTailController;
      unit::BalancingWalker* mBalancingWalker;

      bool pushUp;
    };

  }
}

#endif
