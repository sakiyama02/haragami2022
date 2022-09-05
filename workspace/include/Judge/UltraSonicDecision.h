#ifndef ULTRASONICDECISION

#define ULTRASONICDECISION

#include "../system/system.h"

#define RANGE_LIMIT 2//使用範囲上限

class UltraSonicDecision : public UseJudgement {

public:

	UltraSonicDecision();
	UltraSonicDecision( int16_t target_distance, int8_t range );

	int8_t decide();//判定メソッド

private:
	int16_t m_target_distance;//目標距離
	uint8_t m_range;//使用範囲

};

#endif