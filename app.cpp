/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"
#include "Switcher.h"
#include <stdio.h>

// using宣言
using ev3api::ColorSensor;
using ev3api::GyroSensor;
using ev3api::TouchSensor;
using ev3api::Motor;
using ev3api::SonarSensor;

// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_4);
TouchSensor gTouchSensor(PORT_1);
SonarSensor gSonarSensor(PORT_2);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
Motor       gTailMotor(PORT_A);

// オブジェクトの定義
static LineTrace::unit::LineMonitor     *gLineMonitor_LT;
static LineTrace::unit::Balancer        *gBalancer_LT;
static LineTrace::unit::BalancingWalker *gBalancingWalker_LT;
static LineTrace::app::LineTracer      *gLineTracer_LT;
static LineTrace::unit::Starter         *gStarter_LT;
static LineTrace::unit::TailController *gTailController_LT;
static LineTrace::app::LineTracerWithStarter *gLineTracerWithStarter_LT;
static LineTrace::unit::Waker           *gWaker_LT;

static Garage::app::Stopper             *gStopper_G;
static Garage::app::GarageStopper       *gGarageStopper_G;
static Garage::unit::Starter            *gStarter_G;
static Garage::unit::LineMonitor        *gLineMonitor_G;
static Garage::unit::TailController     *gTailController_G;
static Garage::unit::TailWalker         *gTailWalker_G;

static Stair::unit::LineMonitor           *gLineMonitor_S;
static Stair::unit::LineMonitorForTail    *gLineMonitorForTail_S;
static Stair::unit::Balancer              *gBalancer_S;
static Stair::unit::BalancingWalker       *gBalancingWalker_S;
static Stair::app::LineTracer            *gLineTracer_S;
static Stair::unit::Starter               *gStarter_S;
static Stair::unit::TailController        *gTailController_S;
static Stair::app::LineTracerWithStarter *gLineTracerWithStarter_S;
static Stair::unit::ObstacleDitector      *gObstacleDitector_S;
static Stair::unit::StairTurner           *gStairTurner_S;
static Stair::app::StairWalker           *gStairWalker_S;
static Stair::unit::TailWalker            *gTailWalker_S;
static Stair::unit::Waker                 *gWaker_S;

static LookUpGate::app::LookUpGate *gLookUpGate_LG;
static FILE* gBt= ev3_serial_open_file(EV3_SERIAL_BT);
bool bt_cmd;
//static LookUpGate::unit::LineMonitor     *gLineMonitor_LG;
//static LookUpGate::unit::Balancer        *gBalancer_LG;
//static LookUpGate::unit::BalancingWalker *gBalancingWalker_LG;
//static LookUpGate::unit::Starter         *gStarter_LG;
static LookUpGate::unit::TailController *gTailController_LG;

static app::Switcher *gSwitcher;
static unit::InitValues *gInitValues;
static unit::GrayDetector *gGrayDetector;

void *__dso_handle = 0;

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2);

    // オブジェクトの作成
    gInitValues = new unit::InitValues();

    gBalancer_LT               = new LineTrace::unit::Balancer();
    gBalancingWalker_LT        = new LineTrace::unit::BalancingWalker(gGyroSensor,
								      gLeftWheel,
								      gRightWheel,
								      gBalancer_LT,
								      gInitValues);
    gLineMonitor_LT     = new LineTrace::unit::LineMonitor(gColorSensor,
							   gLeftWheel,
							   gRightWheel);
    gStarter_LT         = new LineTrace::unit::Starter(gTouchSensor);
    gTailController_LT  = new LineTrace::unit::TailController(gTailMotor);
    gWaker_LT           = new LineTrace::unit::Waker(gTailController_LT,
						     gBalancingWalker_LT);
    gLineTracer_LT      = new LineTrace::app::LineTracer(gLineMonitor_LT, gBalancingWalker_LT);

    gLineTracerWithStarter_LT = new LineTrace::app::LineTracerWithStarter(gLineTracer_LT,
									  gStarter_LT,
									  gTailController_LT,
									  gWaker_LT,
									  gGyroSensor);

    gLineMonitor_G     = new Garage::unit::LineMonitor(gColorSensor);
    gTailController_G  = new Garage::unit::TailController(gTailMotor);
    gStarter_G         = new Garage::unit::Starter(gTouchSensor);
    gTailWalker_G      = new Garage::unit::TailWalker(gLeftWheel,
						      gRightWheel,
						      gTailController_G,
						      gLineMonitor_G);
    gStopper_G         = new Garage::app::Stopper(gLeftWheel, gRightWheel, gTailMotor);
    gGrayDetector = new unit::GrayDetector(gLineMonitor_LT,
					   gBalancingWalker_LT,
					   gTailWalker_G,
					   gColorSensor);
    gGarageStopper_G   = new Garage::app::GarageStopper(gTailWalker_G,
							gStarter_G,
							gGrayDetector);
    
    gBalancer_S               = new Stair::unit::Balancer();
    gBalancingWalker_S        = new Stair::unit::BalancingWalker(gGyroSensor,
								 gLeftWheel,
								 gRightWheel,
								 gBalancer_S,
								 gInitValues);
    gObstacleDitector_S       = new Stair::unit::ObstacleDitector(gGyroSensor,gLeftWheel,gRightWheel,gColorSensor);

    gTailController_S         = new Stair::unit::TailController(gTailMotor);
    gLineMonitor_S            = new Stair::unit::LineMonitor(gColorSensor);
    gLineMonitorForTail_S     = new Stair::unit::LineMonitorForTail(gColorSensor);
    gStarter_S                = new Stair::unit::Starter(gTouchSensor);
    gStairTurner_S            = new Stair::unit::StairTurner(gLeftWheel,
							     gRightWheel,
							     gTailController_S,
							     gColorSensor);
    gLineTracer_S             = new Stair::app::LineTracer(gLineMonitor_S, gBalancingWalker_S);
    gTailWalker_S             = new Stair::unit::TailWalker(gLeftWheel,
							    gRightWheel,
							    gTailController_S,
							    gLineMonitorForTail_S);
    gWaker_S           = new Stair::unit::Waker(gTailController_S,
						     gBalancingWalker_S);
    gStairWalker_S            = new Stair::app::StairWalker(gStairTurner_S,
					      gLineTracer_S,
					      gObstacleDitector_S,
					      gTailWalker_S,
					      gBalancingWalker_S,
					      gTailController_S,
							    gWaker_S);
    gLineTracerWithStarter_S  = new Stair::app::LineTracerWithStarter(gLineTracer_S,
							  gStarter_S,
							  gTailController_S);

    //gBalancer_LG               = new LookUpGate::unit::Balancer();
    //gBalancingWalker_LG        = new LookUpGate::unit::BalancingWalker(gGyroSensor,
    //								   gLeftWheel,
    //								   gRightWheel,
    //								   gBalancer_LG);
    //gLineMonitor_LG     = new LookUpGate::unit::LineMonitor(gColorSensor,
    //							    gLeftWheel,
    //							    gRightWheel);
//gStarter_LG         = new LookUpGate::unit::Starter(gTouchSensor);
    gTailController_LG  = new LookUpGate::unit::TailController(gTailMotor);
    gLookUpGate_LG = new LookUpGate::app::LookUpGate(gTailController_LG,
						     gSonarSensor,
						     gLeftWheel,
						     gRightWheel);

    gSwitcher        = new app::Switcher(gLineTracerWithStarter_LT,
					 //gStopper_G,
					 gGarageStopper_G,
					 gStairWalker_S,
					 gLookUpGate_LG);

    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();
    gTailMotor.reset();
    fclose(gBt);
    delete gSwitcher;
    delete gInitValues;
    delete gGrayDetector;

    delete gLineTracerWithStarter_LT;
    delete gLineTracer_LT;
    delete gWaker_LT;
    delete gTailController_LT;
    delete gStarter_LT;
    delete gLineMonitor_LT;
    delete gBalancingWalker_LT;
    delete gBalancer_LT;

    delete gStopper_G;
    delete gGarageStopper_G;
    delete gLineMonitor_G;
    delete gStarter_G;
    delete gTailController_G;
    delete gTailWalker_G;

    delete gTailWalker_S;
    delete gStairWalker_S;
    delete gWaker_S;
    delete gStairTurner_S;
    delete gObstacleDitector_S;
    delete gLineTracerWithStarter_S;
    delete gLineTracer_S;
    delete gTailController_S;
    delete gStarter_S;
    delete gLineMonitor_S;
    delete gLineMonitorForTail_S;
    delete gBalancingWalker_S;
    delete gBalancer_S;

    delete gTailController_LG;
    //delete gStarter_LG;
    //delete gLineMonitor_LG;
    //delete gBalancingWalker_LG;
    //delete gBalancer_LG;
    delete gLookUpGate_LG;
}

void prepare_restart() {
  gLeftWheel.setPWM(0);
  gRightWheel.setPWM(0);
  gTailMotor.setPWM(0);

  gLeftWheel.reset();
  gRightWheel.reset();
  gTailMotor.reset();
}


/**
 * トレース実行タイミング
 */
void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(TRACER_TASK);
}

void ev3_cyc_remote(intptr_t exinf) {
    act_tsk(REMOTE_TASK);
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);
    ev3_sta_cyc(EV3_CYC_REMOTE);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止

    ev3_stp_cyc(EV3_CYC_TRACER);
    ev3_stp_cyc(EV3_CYC_REMOTE);
    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        gSwitcher->run();  // 倒立走行
    }

    ext_tsk();
}
void remote_task(intptr_t exinf){

  if(gBt != NULL){
    uint8_t c = fgetc(gBt); /* 受信 */
    if(c=='1'){
      gStarter_LT->setRemote(true);
      gStarter_G->setRemote(true);
    }else if(c=='0'){
      gStarter_LT->setRemote(false);
      gStarter_G->setRemote(false);

      prepare_restart();

      gStarter_LT->reset();
      gLineTracer_LT->reset();
      gLineTracerWithStarter_LT->reset();
      gLineTracer_S->reset();
      gLineTracerWithStarter_S->reset();
      gStairWalker_S->reset();
      gLookUpGate_LG->reset();
      gGarageStopper_G->reset();
      gStopper_G->reset();
    }else{
      gStarter_LT->setRemote(false);
      gStarter_G->setRemote(false);
    }
    fputc(c, gBt); /* エコーバック */

  }else{
    gStarter_LT->setRemote(false);
    gStarter_G->setRemote(false);
  }
  ext_tsk();
}

