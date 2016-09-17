/******************************************************************************
 *  LineTracerWithStarter.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracerWithStarter
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracerWithStarter.h"
#include "Task.h"

#include <stdio.h>

namespace LineTrace{
  namespace app{

    /**
     * コンストラクタ
     * @param lineTracer ライントレーサ
     * @param starter    スタータ
     */
    LineTracerWithStarter::LineTracerWithStarter(app::LineTracer* lineTracer,
						 unit::Starter* starter,
						 unit::TailController* tailController,
						 unit::Waker* waker,
						 ev3api::GyroSensor& gyroSensor)
      : mLineTracer(lineTracer),
	mStarter(starter),
	mTailController(tailController),
	mWaker(waker),
	mGyroSensor(gyroSensor),
	mState(UNDEFINED),
	timeFromStart(0){
      fp = fopen("angleLog.txt","w");
    }

    /**
     * ライントレースする
     */
    void LineTracerWithStarter::run() {
      switch (mState) {
      case UNDEFINED:
        execUndefined();
        break;
      case WAITING_FOR_START:
        execWaitingForStart();
        break;
      case PREPARE_STARTING:
        execPrepare();
        break;
      case ROCKET_STARTING:
        execStarting();
	break;
      case WALKING:
        execWalking();
	break;
      default:
        break;
      }
    }

    /**
     * 未定義状態の処理
     */
    void LineTracerWithStarter::execUndefined() {
      mTailController->init();
      mTailController->setAngle(102);//メモ：107で直立、現在102

      mState = WAITING_FOR_START;
    }

    /**
     * 開始待ち状態の処理
     */
    void LineTracerWithStarter::execWaitingForStart() {
      mTailController -> run();

      if (mStarter->isPushed()) {
	ev3_speaker_play_tone(NOTE_A5,300);
	mLineTracer->init();
	//mGyroSensor.reset();
	//mTailController->setAngle(110);
	//mTailController->setAngle(0);//
	mState = PREPARE_STARTING;
      }
    }

    void LineTracerWithStarter::execPrepare() {
      //mTailController -> run();//

      //if(mTailController -> getAngle() >= 108){
      //fprintf(fp,"Angle = %d\n",mGyroSensor.getAngle());
      //if(mGyroSensor.getAngle()>1 || mTailController->getAngle() >= 106) {
      //if(mGyroSensor.getAngle()>2 || timeFromStart != 0) {
      //mTailController -> setAngle(0);
      mLineTracer->setStarting(true);
      //mLineTracer->run();//
      //timeFromStart += 4;//

      //if(timeFromStart > 50){//
      if(mWaker->isWaked()){
	mLineTracer->setSpeed(80);
	//timeFromStart = 0;
	mState = ROCKET_STARTING;
      }
    }

    void LineTracerWithStarter::execStarting() {
      //mLineTracer->setStarting(true);
      mLineTracer->run();
      mTailController -> run();

      if(timeFromStart > 3000){
	//mState = WALKING;
	mState = WALKING;
      }else{
	timeFromStart += 4;
      }
    }

    /**
     * 走行中状態の処理
     */
    void LineTracerWithStarter::execWalking() {
      mLineTracer->setStarting(false);
      mLineTracer->run();
      mTailController -> run();
    }

    bool LineTracerWithStarter::isDone(){
      if(mLineTracer -> isDone()){
	ev3_speaker_play_tone(NOTE_A5,300);
      }
      return mLineTracer -> isDone();
    }

    LineTracerWithStarter::~LineTracerWithStarter(){
      delete mLineTracer;
      delete mStarter;
      delete mTailController;
      delete &mGyroSensor;
      delete &mState;
    }
  }
}
