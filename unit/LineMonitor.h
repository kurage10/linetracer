/******************************************************************************
 *  LineMonitor.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_UNIT_LINEMONITOR_H_
#define EV3_UNIT_LINEMONITOR_H_

#include "ColorSensor.h"
#include "Motor.h"

// 定義
class LineMonitor {
public:
  explicit LineMonitor(const ev3api::ColorSensor& colorSensor,
		       ev3api::Motor& leftMotor, ev3api::Motor& rightMotor);
    float calcDirection(bool starting);
    void setThreshold(int8_t threshold);
    int distanceMonitor();
    
private:
    static const int8_t INITIAL_THRESHOLD;
    static const float KP_80;        // 比例係数
    static const float KP_30;        // 比例係数
    static const float KP_Start;        // 比例係数
    static const float KI_80;
    static const float KI_30;
    static const float KD_80;
    static const float KD_30;
    static const float DIRECTION_MAX;
    static const int ENC_THRESHOLD;
    const ev3api::ColorSensor& mColorSensor;
    ev3api::Motor& mLeftWheel;
    ev3api::Motor& mRightWheel;
    int8_t mThreshold;
    float diff[2];
    float integral;
    int mSpeed;
    int leftWheelEnc;
    int rightWheelEnc;
    int startMeasuringEnc;
    //int mState;
    
    FILE* fp;
    float time;
};

#endif  // EV3_UNIT_LINEMONITOR_H_
