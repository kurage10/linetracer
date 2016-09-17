#include "./Seeker.h"

namespace Stair{
  namespace unit{
    Seeker::Seeker(Stair::unit::BalancingWalker* balancingWalker,const ev3api::ColorSensor& colorSensor)
      : mBalancingWalker(balancingWalker),
        mColorSensor(colorSensor),
        mState(TURN),
        crossLine(false),
        straight(false){

    }
    void Seeker::setOffset(){
      left_offset = mBalancingWalker->getLeftCount();
      right_offset = mBalancingWalker->getRightCount();
    }
      bool Seeker::isLost(){
      int color=mColorSensor.getBrightness();
      if(color > 20){
        return true;
      }else{
        return false;
      }
    }
    bool Seeker::seek(){
      int color=mColorSensor.getBrightness();
      int left,right,diff;
      left = mBalancingWalker->getLeftCount();
      right = mBalancingWalker->getRightCount();
      switch(mState){
        case TURN:
          if(!isLost())return true;
          if(left - left_offset > 30){
            mState = STRAIGHT;
          }else{
            mBalancingWalker->setCommand(0,-10);
            mBalancingWalker->run();
          }
        break;
        case STRAIGHT:
          if(!isLost())return true;
          if(left - left_offset > 100){
            mState = BACK;
          }else{
            mBalancingWalker->setCommand(10,0);
            mBalancingWalker->run();
          }
        break;
        case BACK:
          if(color < 7){
            crossLine=true;
          }
          if(crossLine && color > 20){
            return true;
          }
          mBalancingWalker->setCommand(-10,0);
          mBalancingWalker->run();
        break;
        default:
        break;
      }
      return false;
    }
    void Seeker::init(){
      crossLine=false;
      straight = false;
      setOffset();
      mState=TURN;
    }
    bool Seeker::onStraight(){
      int left,right,diff,r_dis,l_dis;
      left = mBalancingWalker->getLeftCount();
      right = mBalancingWalker->getRightCount();
      l_dis=left-left_offset;
      r_dis=right-right_offset;
      diff = (l_dis > r_dis) ? l_dis : r_dis;
      if(straight || (left > 10 && diff < 15)){
        straight=true;
        return true;
      }
      return false;
    }
  }
}
