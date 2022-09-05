#pragma once

#define RANGE_LIMIT 2 //使用範囲上限

#include "../system/system.h"

class AngleDecision : public UseJudgement {

public:

	AngleDecision();
	AngleDecision( float target_angle, int8_t range );

	int8_t decide( void );//角度判定メソッド

private:

	float m_target_angle;//目標角度
	uint8_t m_range;//使用範囲
};

