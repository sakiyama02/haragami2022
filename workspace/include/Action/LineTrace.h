#pragma once

#include "./Action.h"
#include "../system/system.h"
#include "../CarData/CarData.h"
#include "./TrapezoidControl.h"
#include "./PIDControl.h"
#include "../ColorSpace/ColorSpace.h"

#define LEFT_LINE 1
#define RIGHT_LINE 2


/// 7/13 new
/// sakiyama
/// LineTrace
/// 閾値(target_val)-hsv.vをpid制御に渡し、pid制御から操作量を取得する
/// その次に台形制御へspeedを渡し、現在速度を取得する
/// 取得した値たちで計算し、ステアリング制御に計算結果を渡す
class LineTrace : public Action{
	private:
	GAIN 		gain;				// ゲイン値
	double 		target_val;			// 閾値
	int8_t 		edge;				// ライン際
	COORDINATE 	target_coordinate;	// 目標座標

	public:
	LineTrace();
	LineTrace(GAIN gain,double target_val,int8_t edge,COORDINATE target_coordinate);
	~LineTrace();

	int8_t run(int32_t speed);
};