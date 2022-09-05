#include "../../include/system/system.h"
#include "../../include/Judge/UseJudgement.h"
#include "../../include/Judge/RGBDecision.h"
#include "../../include/ColorSpace/ColorSpace.h"

RGBDecision::RGBDecision() {

	m_rgb = { 0,0,0 };

	memset( m_range, 0, sizeof( m_range ) );

	return;
}

RGBDecision::RGBDecision( RGB_DATA rgb, uint8_t range[ USAGE_LIMIT ] ) {

	m_rgb = rgb;

	memcpy( m_range, range, sizeof( m_range ) );

	return;
}

//RGB判定メソッド
int8_t RGBDecision::decide(void) {

	if ( m_rgb.r > R_LIMIT ) {

		return SYS_PARAM;
	}
	if ( m_rgb.g > G_LIMIT ) {

		return SYS_PARAM;
	}
	if ( m_rgb.b > B_LIMIT ) {

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

	RGB_DATA current_rgb = { 0,0,0 };//現在RGB
	int8_t success = 0;//成功回数
	int8_t usage = USAGE_LIMIT;//判定実行回数

	//RGB取得
	current_rgb = colorspace.getRGB();

	//RGB判定
	//R値判定
	if ( ( m_range[ RED ] == ABOVE ) && ( m_rgb.r <= current_rgb.r ) ) {

		success++;
	}
	else if ( ( m_range[ RED ] == BELOW ) && ( m_rgb.r >= current_rgb.r ) ) {

		success++;
	}
	else if ( m_range[ RED ] == 0 ) {

		usage--;
	}

	//G値判定
	if ( ( m_range[ GREEN ] == ABOVE ) && ( m_rgb.g <= current_rgb.g ) ) {

		success++;
	}
	else if ( ( m_range[ GREEN ] == BELOW ) && ( m_rgb.g >= current_rgb.g ) ) {

		success++;
	}
	else if ( m_range[ GREEN ] == 0 ) {

		usage--;
	}

	//B値判定
	if ( ( m_range[ 2 ] == ABOVE ) && ( m_rgb.b <= current_rgb.b ) ) {

		success++;
	}
	else if ( ( m_range[ BLUE ] == BELOW ) && ( m_rgb.b >= current_rgb.b ) ) {

		success++;
	}
	else if ( m_range[ BLUE ] == 0 ) {

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