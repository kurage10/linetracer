#include "./LookUpGate.h"
namespace LookUpGate{
  namespace app{
    int current_speed = 0;
    int base_speed = 40;
    int timer = 1;

    LookUpGate::LookUpGate(unit::TailController* tailController,
			   ev3api::SonarSensor& sonar,
			   ev3api::Motor& leftWheel,
			   ev3api::Motor& rightWheel)
      : mTailController(tailController),
	mSonar(sonar),
	mLeftWheel(leftWheel),
	mRightWheel(rightWheel),
	state(INIT) {
    }

    LookUpGate::~LookUpGate(){
      delete mTailController;
      delete &mSonar;
      delete &mLeftWheel;
      delete &mRightWheel;
      delete &state;
    }

    void LookUpGate::run() {
      switch(state) {
      case UNDEFINED:
	break;
      case INIT:
	init();
	break;
      case FIRST:
	firstPass();
	break;
      case BACK:
	backWard();
	break;
      case SECOND:
	secondPass();
	break;
      default:
	break;
      }
    }
    void LookUpGate::init() {
      mLeftWheel.setPWM(base_speed);
      mRightWheel.setPWM(base_speed);
      current_speed = base_speed;
      int dis = mSonar.getDistance();
      if (dis <= 20) {
	mTailController -> setAngle(80);
	state = FIRST;
      }
      mTailController -> run();

    }

    void LookUpGate::firstPass() {
      mTailController -> run();
      if (timer % 50 == 0) {
        int n = setSpeed(0, 0);
        if (1 == n) {
	  state = BACK;
	  timer = 0;
        }
      }
      timer ++;
    }

    void LookUpGate::backWard() {
      mTailController -> setAngle(76);
      mTailController -> run();

      if (timer % 20 == 0) {
        setSpeed(-10, 0);
      }
      if (timer == 2000) {
        state = SECOND;
        setSpeed(0, 0);
        timer = 0;
      } 
      timer ++;
    }

    void LookUpGate::secondPass() {
      mTailController -> run();
      if (timer % 50 == 0) {
        setSpeed(40, 0);
      }
      timer ++;
    }

    int LookUpGate::setSpeed(int speed, int time) {
      double s = speed;
      int d = current_speed - speed;
      if (d > 10 || d < -10) {
        s = s + d / 1.3;
        mLeftWheel.setPWM(s);
        mRightWheel.setPWM(s);
        current_speed = s;
        return 0;
      } else {
        mLeftWheel.setPWM(speed);
        mRightWheel.setPWM(speed);
        current_speed = speed;
        return 1;
      }
    }

    void LookUpGate::delay(int time) {

    }

    bool LookUpGate::isDone(){
      return false;
    }
  }
}
