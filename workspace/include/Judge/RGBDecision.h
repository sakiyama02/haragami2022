#ifndef RGBDECISION

#define RGBDECISION

#include "../system/system.h"

#define USAGE_LIMIT 3//判定実行上限
#define RANGE_LIMIT 2//使用範囲上限
#define R_LIMIT 255//R最大値
#define G_LIMIT 255//G最大値
#define B_LIMIT 255//B最大値
#define RED 0
#define GREEN 1
#define BLUE 2

class RGBDecision : public UseJudgement {

public:

	RGBDecision();
	RGBDecision( RGB_DATA rgb, uint8_t range[ USAGE_LIMIT ] );

	int8_t decide();//判定メソッド

private:

	RGB_DATA m_rgb;//目標RGB
	uint8_t m_range[ USAGE_LIMIT ];//使用範囲
};

#endif