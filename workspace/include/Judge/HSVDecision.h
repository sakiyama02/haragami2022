#ifndef HSVDECISION

#define HSVDECISION

#include "../system/system.h"

#define USAGE_LIMIT 3//判定実行上限
#define RANGE_LIMIT 2//使用範囲上限
#define H_LIMIT 255//H最大値
#define S_LIMIT 255//S最大値
#define V_LIMIT 255//V最大値
#define HUE 0//色相
#define SATURATION 1//彩度
#define BRIGHTNESS 2//明度

class HSVDecision : public UseJudgement {

public:

	HSVDecision();
	HSVDecision( HSV_DATA hsv, uint8_t range[ USAGE_LIMIT ] );

	int8_t decide();//判定メソッド

private:

	HSV_DATA m_hsv;//目標HSV
	uint8_t m_range[ USAGE_LIMIT ];//使用範囲
};

#endif