/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"
#include "Switcher.h"

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
static LineMonitor     *gLineMonitor;
static Balancer        *gBalancer;
static BalancingWalker *gBalancingWalker;
static LineTracer      *gLineTracer;
static LookUpGate      *gLookUpGate;
static Starter         *gStarter;
static TailController *gTailController;
static LineTracerWithStarter *gLineTracerWithStarter;
static Switcher *gSwitcher;

void *__dso_handle = 0;

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2);

    // オブジェクトの作成
    gBalancer               = new Balancer();
    gBalancingWalker        = new BalancingWalker(gGyroSensor,
                                           gLeftWheel,
                                           gRightWheel,
                                           gBalancer);
    gLineMonitor            = new LineMonitor(gColorSensor);
    gStarter                = new Starter(gTouchSensor);
    gTailController         = new TailController(gTailMotor);
    gLineTracer             = new LineTracer(gLineMonitor, gBalancingWalker);
    gLookUpGate             = new LookUpGate(gTailController, gSonarSensor, gLeftWheel, gRightWheel);
    ev3_led_set_color(LED_ORANGE);
    gLineTracerWithStarter  = new LineTracerWithStarter(gLineTracer, gStarter,gTailController,
                                                         gSonarSensor, 
                                                         gLookUpGate,
                                                         // gLeftWheel, gRightWheel, 
                                                         gBalancer);
    gSwitcher               = new Switcher(gLineTracerWithStarter);
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
    delete gSwitcher;
    delete gLineTracerWithStarter;
    delete gLineTracer;
    delete gLookUpGate;
    delete gTailController;
    delete gStarter;
    delete gLineMonitor;
    delete gBalancingWalker;
    delete gBalancer;
}

/**
 * トレース実行タイミング
 */
void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(TRACER_TASK);
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(EV3_CYC_TRACER);

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
