/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 二輪差動型ライントレースロボットのTOPPERS/HRP3用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/
#include "./workspace/include/system/system.h"
#include "ev3api.h"
#include "app.h"

#ifndef SPIKE
#include "etroboc_ext.h"
#endif

#include "./workspace/include/CarData/CarData.h"
#include "./workspace/include/Scene/SceneControl.h"
#include "./workspace/include/SceneInfo/SceneInfo.hpp"
#include "./workspace/include/Sonic/UltraSonic.h"
#include "./workspace/include/ColorSpace/ColorSpace.h"
#include "./workspace/include/FileOp/FileIO.hpp"


#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

/**
 * EV3システム生成
 * モーター設定
 */

/*  スタート処理タスク */
void start_task(intptr_t unused)
{

    ev3_sensor_config(EV3_PORT_1, TOUCH_SENSOR);
    /* 動的に生成するインスタンスの初期化 */

    //ファイル読み込み
	tslp_tsk(10 * 1000U);
    SceneInfo& sceneInfo    = SceneInfo::getInstance();
	sceneInfo.init();
	ColorSpace &colorspace = ColorSpace::getInstance();
    colorspace.update();
	UltraSonic &ultrasonic = UltraSonic::getInstance();
    ultrasonic.update();
  
    //フライング
    while (1)
    {
        #ifdef SPIKE
        if (ev3_button_is_pressed(LEFT_BUTTON) == 1)
		#endif
		if (ev3_touch_sensor_is_pressed(EV3_PORT_1) == 1)
        {
            break;
        }
        tslp_tsk(10 * 1000U);
    }
    printf("button_on\n");
    act_tsk(MAIN_TASK);
    ext_tsk();
}

/* メインタスク */
void main_task(intptr_t unused)
{
	CarData&            car_data    = CarData::getInstance();
    SceneControl &scenecontrol = SceneControl::getInstance();
    FileIO &mlog = FileIO::getInstance();
	ColorSpace &colorspace = ColorSpace::getInstance();
    colorspace.update();
	UltraSonic &ultrasonic = UltraSonic::getInstance();
    ultrasonic.update();
	car_data.update();

    int8 retChk = SYS_NG;
    sta_cyc(SONIC_PERIOD);
    sta_cyc(COLOR_PERIOD);
    sta_cyc(CARDATA_PERIOD);

    mlog.log_open();
    while(1){
       
        retChk = scenecontrol.run();
        if(retChk == ALL_SCENE_END){
            break;
        }
        retChk = scenecontrol.SceneSwitch();
        if(retChk == SYS_NG){
            ext_tsk();
        }
        tslp_tsk(10 * 1000U);
    }

    mlog.log_close();
    MOTOR_POWER stop = {0,0};
   	Steering &steering = Steering::getInstance( );
    steering.run(stop);
   	stp_cyc(SONIC_PERIOD);
    stp_cyc(COLOR_PERIOD);
    stp_cyc(CARDATA_PERIOD);
#ifndef SPIKE
	ETRoboc_notifyCompletedToSimulator();
#endif
    ext_tsk();
}

/* 周期タスク */
void sonic_task(intptr_t exinf)
{
    int8 retChk = SYS_NG;
    UltraSonic &ultrasonic = UltraSonic::getInstance();
    retChk = ultrasonic.update();
    if( retChk != SYS_OK ){
    }
}

void color_task(intptr_t exinf)
{
    int8 retChk = SYS_NG;
    ColorSpace &colorspace = ColorSpace::getInstance();
    retChk = colorspace.update();
    if( retChk != SYS_OK ){
    }
}

void cardata_task(intptr_t exinf)
{
    int8 retChk = SYS_NG;
    CarData &cardata = CarData::getInstance();
    retChk = cardata.update();
    if( retChk != SYS_OK ){
    }
}


