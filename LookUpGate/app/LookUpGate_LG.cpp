#include "./LookUpGate.h"
namespace LookUpGate{
  namespace app{
    int current_speed = 0;
    int base_speed = 40;
    int timer = 1;
    int flag = 0;
    bool done = false;

    LookUpGate::LookUpGate(LineTrace::unit::TailController* tailController,
                    ev3api::SonarSensor& sonar,
                    ev3api::Motor& leftWheel,
                    ev3api::Motor& rightWheel,
                    unit::GateTracer* gateTracer,
                    LineTrace::app::LineTracer* lineTracer,
                    LineTrace::unit::BalancingWalker* balancingWalker)
        : mTailController(tailController),
          mSonar(sonar),
          mLeftWheel(leftWheel),
          mRightWheel(rightWheel),
          mGateTracer(gateTracer),
          mLineTracer(lineTracer),
          mBalancingWalker(balancingWalker),
          state(SEEK),
	  time(0),
	  LeftCount(),
	  RightCount(){
    }

    LookUpGate::~LookUpGate(){
          delete mTailController;
          delete &mSonar;
          delete &mLeftWheel;
          delete &mRightWheel;
          delete &mLineTracer;
          delete &mBalancingWalker;
          delete &state;
    }

    void LookUpGate::run() {
        switch(state) {
            case UNDEFINED:
                break;
            case SEEK:
                seek();
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

    void LookUpGate::seek() {
      int dis = mSonar.getDistance();
      if (50 < dis && dis < 55) {
        mTailController -> setAngle(85);
        flag = 1;
      }
      // dis = 35, 45
      if (dis < 45 && flag == 1) {
        state = INIT;
      }
      // mLineTracer->setSpeed(10);
      mLineTracer->setStarting(false);
      mLineTracer->run();
      mTailController -> run();
    }

    void LookUpGate::init() {
        if (timer <= 100) {
          mBalancingWalker -> setCommand(0, 0);
          mBalancingWalker -> run();
        } else if(timer < 400){
          mBalancingWalker -> setCommand(-25,0);
          mBalancingWalker -> run();
        } else if (timer < 800) {
          mLeftWheel.setPWM(0);
          mRightWheel.setPWM(0);
        } else if (timer < 1000) {
          // mLeftWheel.setPWM(0);
          // mRightWheel.setPWM(0);
          mTailController -> setAngle(80);
        } else if (timer >= 1100) {
          mGateTracer -> run();
        }

        int dis = mSonar.getDistance();
        if (dis <= 15) {
          // mTailController -> setAngle(90);
          ev3_speaker_play_tone(NOTE_A4,300);
          state = FIRST;
          timer = 1;
          getCount();
        }
        mTailController -> run();
        timer ++;
    }

    void LookUpGate::firstPass() {
        mTailController -> run();
        if (timer < 400) {
          mGateTracer -> run();
        } else if (timer >= 420) {
            int n = setSpeed(0, 0);
            if (1 == n) {
      	      mTailController -> setAngle(80);
      	      time++;
      	      if (time > 250) {
    		          time = 0;
                  state = BACK;
  		            ev3_speaker_play_tone(NOTE_A5,300);
                  timer = 0;
      	      }
            }
        }
        timer ++;
    }

    void LookUpGate::backWard() {
// 1: no line trace when back
// 0: do line trace when back
#if 1
      int dis = mSonar.getDistance();
      mTailController -> run();
        // if (timer % 20 == 0) {
        mLeftWheel.setPWM(-8);
        mRightWheel.setPWM(-8);
        // }
        if (15 < dis && dis < 40) {
            mTailController -> setAngle(80);
            setSpeed(0, 0);
      	    time++;
      	    if(time > 250){
      	      time = 0;
              ev3_speaker_play_tone(NOTE_A5,300);
      	      state = SECOND;
      	      timer = 0;
      	    }
        }
        // mGateTracer -> back();
        timer ++;
#else
      mTailController->run();
      if (mGateTracer -> back(LeftCount,RightCount)) {
      	mTailController -> setAngle(80);
      	state = SECOND;
      	setSpeed(0,0);
      	timer = 0;
      }
#endif
    }

    void LookUpGate::secondPass() {
        mTailController -> run();
        mGateTracer -> run();
        // if (timer % 50 == 0) {
        //     setSpeed(base_speed, 0);
        // }
        if (timer > 500) {
          if (timer < 501) {
            ev3_speaker_play_tone(NOTE_A5,300);
          }

          mTailController -> setAngle(90);
          mLeftWheel.setPWM(0);
          mRightWheel.setPWM(0);

        }
        if (timer > 1000) {
          done = true;
        }
        timer ++;
    }

    void LookUpGate::getCount(){
      LeftCount = mLeftWheel.getCount() - 300;
      RightCount = mRightWheel.getCount() - 300;
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
        return done;
    }
  }
}
