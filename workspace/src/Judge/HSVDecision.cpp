#include "../../include/system/system.h"
#include "../../include/Judge/UseJudgement.h"
#include "../../include/Judge/HSVDecision.h"
#include "../../include/ColorSpace/ColorSpace.h"

HSVDecision::HSVDecision() {

	m_hsv = { 0,0,0 };

	memset( m_range, 0, sizeof( m_range ) );

	return;
}

HSVDecision::HSVDecision( HSV_DATA hsv, uint8_t range[ USAGE_LIMIT ] ) {

	m_hsv = hsv;

	memcpy( m_range, range, sizeof( m_range ) );

	return;
}

//HSV判定メソッド
int8_t HSVDecision::decide() {

	if ( m_hsv.h > H_LIMIT ) {

		return SYS_PARAM;
	}
	if ( m_hsv.s > S_LIMIT ) {

		return SYS_PARAM;
	}
	if ( m_hsv.v > V_LIMIT ) {

		return SYS_PARAM;
	}

	int8_t check_cnt = 0;//確認回数
	int8_t unused_cnt = 0;//未使用チェック

	for ( check_cnt = 0; check_cnt < ( sizeof( m_range ) / sizeof( int8_t ) ); check_cnt++ ) {

		if ( m_range[ check_cnt ] > RANGE_LIMIT ) {

			return SYS_PARAM;
		}

		if ( m_range[ check_cnt ] == 0 ) {

			unused_cnt++;
		}

		if ( unused_cnt >= USAGE_LIMIT ) {

			return SYS_NG;
		}
	}

	//色空間のインスタンスを取得
	ColorSpace &colorspace = ColorSpace::getInstance();

	HSV_DATA current_hsv = { 0,0,0 };//現在HSV
	int8_t success = 0;//成功回数
	int8_t usage = USAGE_LIMIT;//判定実行回数

	//HSV取得
	current_hsv = colorspace.getHSV();

	//HSV判定
	//H値判定
	if ( ( m_range[ HUE ] == ABOVE ) && ( m_hsv.h <= current_hsv.h ) ) {

		success++;
	}
	else if ( ( m_range[ HUE ] == BELOW ) && ( m_hsv.h >= current_hsv.h ) ) {

		success++;
	}
	else if ( m_range[ HUE ] == 0 ) {

		usage--;
	}

	//S値判定
	if ( ( m_range[ SATURATION ] == ABOVE ) && ( m_hsv.s <= current_hsv.s ) ) {

		success++;
	}
	else if ( ( m_range[ SATURATION ] == BELOW ) && ( m_hsv.s >= current_hsv.s ) ) {

		success++;
	}
	else if ( m_range[ SATURATION ] == 0 ) {

		usage--;
	}

	//V値判定
	if ( ( m_range[ BRIGHTNESS ] == ABOVE ) && ( m_hsv.v <= current_hsv.v ) ) {

		success++;
	}
	else if ( ( m_range[ BRIGHTNESS ] == BELOW ) && ( m_hsv.v >= current_hsv.v ) ) {

		success++;
	}
	else if ( m_range[ BRIGHTNESS ] == 0 ) {

		usage--;
	}

	//比較
	if ( success == usage ) {

		return RESULT_TRUE;
	}
	else {

		return RESULT_FALSE;
	}
}