//*******************************************
//角度判定
//*******************************************
#include "../../include/system/system.h"
#include "../../include/Judge/UseJudgement.h"
#include "../../include/Judge/AngleDecision.h"
#include "../../include/CarData/CarData.h"

AngleDecision::AngleDecision() {

	m_target_angle = 0;
	m_range = 0;

	return;
}

AngleDecision::AngleDecision( double target_angle, int8_t range ) {

	m_target_angle = target_angle;
	m_range = range;

	return;
}
//角度判定メソッド
int8_t AngleDecision::decide(void) {

	//メンバ変数チェック
	if ( m_range > RANGE_LIMIT ) {

		return SYS_PARAM;
	}

	//自己位置推定のインスタンスを取得
	CarData &cardata = CarData::getInstance();

	double current_angle = 0;

	//現在角度取得
	current_angle = cardata.getAngle();

	//角度判定
	if ( ( m_range == ABOVE ) && ( m_target_angle <= current_angle ) ) {

		return RESULT_TRUE;
	}
	else if ( ( m_range == BELOW ) && ( m_target_angle >= current_angle ) ) {

		return RESULT_TRUE;
	}
	
	return RESULT_FALSE;
}