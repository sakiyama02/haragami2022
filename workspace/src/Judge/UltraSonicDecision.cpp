#include "../../include/system/system.h"
#include "../../include/Judge/UseJudgement.h"
#include "../../include/Judge/UltraSonicDecision.h"
#include "../../include/Sonic/UltraSonic.h"

UltraSonicDecision::UltraSonicDecision() {

	m_target_distance = 0;
	m_range = 0;

	return;
}

UltraSonicDecision::UltraSonicDecision( int16_t target_distance, int8_t range ) {

	m_target_distance = target_distance;
	m_range = range;

	return;
}

//超音波判定メソッド
int8_t UltraSonicDecision::decide() {

	//メンバ変数チェック
	if ( m_range > RANGE_LIMIT ) {

		return SYS_PARAM;
	}

	//超音波のインスタンスを取得
	UltraSonic &ultrasonic = UltraSonic::getInstance();

	int16_t current_distance = 0;//現在距離

	//現在距離取得
	current_distance = ultrasonic.getDistance();

	//超音波判定
	if ( ( m_range == ABOVE ) && ( m_target_distance <= current_distance ) ) {

		return RESULT_TRUE;
	}
	else if ( ( m_range == BELOW ) && ( m_target_distance >= current_distance ) ) {

		return RESULT_TRUE;
	}

	return RESULT_FALSE;
}