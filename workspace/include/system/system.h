#pragma once

#include <cstdint>
#include <algorithm>
#include <array>
#include <string.h>
#include <memory>
#include <string>
#include <math.h>
#include <cmath>
#include <complex>
#include <ostream>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <stdarg.h>
#include <vector>

#include "ev3api.h"

#define EV3

#define SYS_OK 0    //正常終了
#define SYS_NG -1    //異常終了
#define SYS_PARAM -2 //引数エラー
#define ALL_SCENE_END 3 //全シナリオ終了
#define ABOVE 1	//以上
#define BELOW 2
#define XPOS_MAX 10000
#define XPOS_MIN 0
#define YPOS_MAX 10000
#define YPOS_MIN 0
#define RESULT_TRUE 1
#define RESULT_FALSE 2

#define PI				(3.141592653589793)	/* 円周率					 */

#if defined(EV3) || defined(SPIKE)
	#define CAR_WHEEL_WIDTH (100.0)
#else
	#define CAR_WHEEL_WIDTH (90.33)
#endif

#ifdef SPIKE
	#define CAR_WIDTH (127.0)
#else
	#define CAR_WIDTH (142.0)
#endif

#define DIST ((PI) * (double)CAR_WHEEL_WIDTH) / 360.0
// integer 8bit
using int8 = int8_t;

// integer 16bit
using int16 = int16_t;

// integer 32bit
using int32 = int32_t;

// integer 64bit
using int64 = int64_t;

// unsigned integer 8bit
using uint8 = uint8_t;

// unsigned integer 16bit
using uint16 = uint16_t;

// unsigned integer 32bit
using uint32 = uint32_t;

// unsigned integer 64bit
using uint64 = uint64_t;

// int pointer
using intptr = intptr_t;

// uint pointer
using uintptr = uintptr_t;

/* 列挙型の定義 */
#if defined(SPIKE)
enum SensorPort
{
  SENSOR_TOUCH = EV3_PORT_1, //タッチセンサー
  SENSOR_COLOR = EV3_PORT_2, //カラーセンサー
  SENSOR_SONAR = EV3_PORT_3, //超音波センサー
  SENSOR_GYRO  = EV3_PORT_4,  //ジャイロセンサー
};
#else
enum SensorPort
{
  SENSOR_TOUCH , //タッチセンサー
  SENSOR_COLOR , //カラーセンサー
  SENSOR_SONAR , //超音波センサー
  SENSOR_GYRO  ,  //ジャイロセンサー
};
#endif



/* 構造体定義 */
// RGBの構造体
typedef struct GAIN_TAG {
	double p;
	double i;
	double d;
}GAIN;

typedef struct COORDINATE_TAG {
	double x;
	double y;
}COORDINATE;


typedef struct RGB_TAG {	
	unsigned short r;
	unsigned short g;
	unsigned short b;
}RGB_DATA;

//HSVの構造体
typedef struct HSV_TAG {	
	unsigned short h;
	unsigned short s;
	unsigned short v;
}HSV_DATA;

typedef struct MOTOR_POWER_TAG {
	int32_t right;
	int32_t left;
}MOTOR_POWER;

typedef struct MOTOR_ANGLE_TAG {
	int32_t right;
	int32_t left;
}MOTOR_ANGLE;

enum Motion{
	LINETRACE,
	CURVE,
	TURN,
	STRAIGHT
};

struct MoveData
{
	unsigned char motion;				// 使用動作
	unsigned char edge;				// ライントレース位置（右ライン or 左ライン）
	GAIN gain;					// ゲイン
	double target_val;			// 閾値
	double speed;				// 目標速度
	double radius;				// カーブ半径
	COORDINATE coordinate;		// 目標座標
	unsigned char direction;			// 旋回方向
	short arm_angle;			// アーム角度
	short tail_angle;
	int arm_pwm;				// アーム速度
};

struct DecisionData
{
	unsigned char decision[2];			// 使用判定
	COORDINATE coordinate;			// 目標座標
	unsigned char coordinate_range[2];	// 目標座標範囲
	unsigned char color;					// 目標色
	unsigned short distance;				// 目標距離
	unsigned char distance_range;			// 目標距離範囲
	RGB_DATA rgb;					// 目標RGB
	unsigned char rgb_range[3];			// 使用RGB
	HSV_DATA hsv;					// 目標HSV
	unsigned char hsv_range[3];			// 使用HSV
	double angle;					// 目標角度
	unsigned char angle_range;			// 目標角度範囲
	unsigned char logic;					// 論理演算方法
};

struct CorrectionData
{
	COORDINATE coordinate; 		// 補正座標
	double angle;				// 補正角度
	unsigned char correction[3];			// 使用軸
	DecisionData decisionData;	// 判定情報クラス
};

struct PaternDecisionData
{
	unsigned char slalom_decision;			// スラロームパターンフラグ
	unsigned char garage_decision;			// ガレージパターンフラグ
	unsigned char garage_point;			// ガレージパターンフラグ
};

struct SceneData
{
	int num;
	MoveData moveData;
	DecisionData decisionData;
	CorrectionData correctionData;
	PaternDecisionData paterndecisiondata;
};
