#include "./Waker.h"

namespace LineTrace{
  namespace unit{

    Waker::Waker(unit::TailController* tailController,
		 unit::BalancingWalker* balancingWalker)
      : mTailController(tailController),
	mBalancingWalker(balancingWalker),
	pushUp(false) {
    }
    
    bool Waker::isWaked(){
      if(mTailController->getAngle() < 10){
	pushUp = false;
	return true;
      }

      //通常スタート
      /*mBalancingWalker->setCommand(0,0);
      mTailController->setAngle(0);
      
      mBalancingWalker->run();
      mTailController->run();

      return false;*/
      
      //改善版
      if(pushUp){
	mBalancingWalker->run();
	mTailController->setAngle(0);
	mTailController->run();
      }else{
	if(mTailController->getAngle() >= 104){
	  mBalancingWalker->setCommand(0,0);
	  mBalancingWalker->run();
	  mTailController->setAngle(0);
	  mTailController->run();
	  pushUp = true;
	}else{
	  mTailController->setAngle(107);
	  mTailController->run();
	}
      }
      
      return false;

    }

  }
}
