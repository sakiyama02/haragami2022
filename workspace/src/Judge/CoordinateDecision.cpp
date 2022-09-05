//*****************************************
//座標判定
//*****************************************
#include "../../include/system/system.h"

#include "../../include/Judge/UseJudgement.h"
#include "../../include/Judge/CoordinateDecision.h"
#include "../../include/CarData/CarData.h"

CoordinateDecision::CoordinateDecision() {

	m_coordinate = { 0,0 };

	memset( m_range, 0, sizeof( m_range ) );

	return;
}

CoordinateDecision::CoordinateDecision( COORDINATE coordinate, uint8_t range[ USAGE_LIMIT ] ) {

	m_coordinate = coordinate;
	
	memcpy( m_range, range, sizeof( m_range ) );

	return;
}

//座標判定メソッド
int8_t CoordinateDecision::decide(void) {

	if ( ( m_coordinate.x < XPOS_MIN ) || ( m_coordinate.x > XPOS_MAX ) ) {

		return SYS_PARAM;
	}

	if ( ( m_coordinate.y < YPOS_MIN ) || ( m_coordinate.y > YPOS_MAX ) ) {

		return SYS_PARAM;
	}

	int8_t check_cnt = 0;
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

	//自己位置推定のインスタンスを取得
	CarData &cardata = CarData::getInstance();

	COORDINATE current_coordinate = { 0,0 };//現在座標
	int8_t success = 0;//判定成功回数
	int8_t usage = USAGE_LIMIT;//判定実行回数

	//自己位置座標取得
	current_coordinate = cardata.getPos();

	//x座標判定
	if ( ( m_range[ 0 ] == ABOVE ) && ( m_coordinate.x <= current_coordinate.x ) ) {

		success++;
	}
	else if ( ( m_range[ 0 ] == BELOW ) && ( m_coordinate.x >= current_coordinate.x ) ) {

		success++;
	}
	else if ( m_range[ 0 ] == 0 ) {

		usage--;
	}

	//y座標判定
	if ( ( m_range[ 1 ] == ABOVE ) && ( m_coordinate.y <= current_coordinate.y ) ) {

		success++;
	}
	else if ( ( m_range[ 1 ] == BELOW ) && ( m_coordinate.y >= current_coordinate.y ) ) {

		success++;
	}
	else if ( m_range[ 1 ] == 0 ) {

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