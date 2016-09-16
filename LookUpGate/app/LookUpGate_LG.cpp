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
          state(SEEK) {
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
      if (60 < dis && dis < 65) {
        mTailController -> setAngle(85);
        flag = 1;
      }
      if (dis < 50 && flag == 1) {
        state = INIT;
      }
      mLineTracer->setStarting(false);
      mLineTracer->run();
      mTailController -> run();
    }

    void LookUpGate::init() {
        mBalancingWalker -> setCommand(0, 0);
        mBalancingWalker -> run();
        if(timer > 100 && timer < 400){
          mBalancingWalker -> setCommand(-25,0);
          mBalancingWalker -> run();
        } else if (400 <= timer && timer < 500) {
          mLeftWheel.setPWM(0);
          mRightWheel.setPWM(0);
        } else if (timer >= 500) {
          mGateTracer -> run();
        }

        // mLeftWheel.setPWM(base_speed);
        // mRightWheel.setPWM(base_speed);
        // current_speed = base_speed;
        // mGateTracer -> run();
        int dis = mSonar.getDistance();
        if (dis <= 15) {
          mTailController -> setAngle(80);
          state = FIRST;
          timer = 1;
        }
        mTailController -> run();
        timer ++;
    }

    void LookUpGate::firstPass() {
        mTailController -> run();
        if (timer < 400) {
          mGateTracer -> run();
        } else if (timer % 70 == 0) {
            int n = setSpeed(0, 0);
            if (1 == n) {
                state = BACK;
                timer = 0;
            }
        }
        timer ++;
    }

    void LookUpGate::backWard() {
        int dis = mSonar.getDistance();
        mTailController -> setAngle(83);
        mTailController -> run();
        // if (timer % 20 == 0) {
            setSpeed(-8, 0);
        // }
        if (15 < dis && dis < 30) {
            mTailController -> setAngle(80);
            state = SECOND;
            setSpeed(0, 0);
            timer = 0;
        }
        // mGateTracer -> back();
        timer ++;
    }

    void LookUpGate::secondPass() {
        mTailController -> run();
        mGateTracer -> run();
        // if (timer % 50 == 0) {
        //     setSpeed(base_speed, 0);
        // }

        if (timer > 600) {
          done = true;
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
          if (done == true) {
            mLeftWheel.setPWM(30);
            mRightWheel.setPWM(-30);
          }
          return false;
    }
  }
}
