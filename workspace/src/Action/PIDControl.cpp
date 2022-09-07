#include "../../include/Action/Controller.h"
#include "../../include/Action/PIDControl.h"

PIDControl::PIDControl(){}

PIDControl::~PIDControl(){}

int8 PIDControl::init(GAIN _gain){
    memcpy(&gain,&_gain,sizeof(GAIN));
    stack_integral=0.0f;
    motor_revision = 0.0f;
    prevdeviation=0.0f;
    deviation=0.0f;
    return SYS_OK;
}

int8 PIDControl::calc(){
    double   kP = 0;                             //比例ゲイン
    double   kI = 0;                             //積分ゲイン
    double   kD = 0;                             //微分ゲイン
     //偏差の積み上げ
    stack_integral += ((prevdeviation + deviation)) / 2.0f * DELTA_TIME;
    //比例ゲイン(kP)
    kP = gain.p * deviation;
    //積分ゲイン(kI)
    kI = gain.i* stack_integral;
    //微分ゲイン(kD)
    if(prevdeviation!=0.0f){
        kD = gain.d* (deviation - prevdeviation) / DELTA_TIME;
    }
    prevdeviation=stack_integral;
    //モーター速度
    motor_revision = kP + kI + kD;
    if(motor_revision>100||motor_revision<-100){
        motor_revision=100;
    }
    return SYS_OK;
}
