#ifndef EV3_APP_SEEKER_H_
#define EV3_APP_SEEKER_H_

#include "ColorSensor.h"
#include "../unit/BalancingWalker.h"
#include<stdio.h>

namespace Stair{
  namespace unit{

    class Seeker{
      public:
        Seeker(Stair::unit::BalancingWalker* balancingWalker,const ev3api::ColorSensor& colorSensor);
        void setOffset();
        bool isLost();
        bool seek();
        void init();
        bool onStraight();

      private:
        enum State{
          UNDEFINED,
          TURN,
          STRAIGHT,
          BACK
        };
        State mState;
        int left_offset;
        int right_offset;
        Stair::unit::BalancingWalker* mBalancingWalker;
        const ev3api::ColorSensor& mColorSensor;
        bool crossLine;
        bool straight;
    };
  }
}
#endif
