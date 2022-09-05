
#define _USE_MATH_DEFINES

#include "../../include/system/system.h"
#include "../../include/Correction/Correction.h"
#include "../../include/Judge/Judgement.h"
#include "../../include/CarData/CarData.h"

int8_t Correction::run( CorrectionData correctiondata ) {

	int8_t check_cnt = 0;//確認回数
	int8_t unused_cnt = 0;//未使用チェック

	for ( check_cnt = 0; check_cnt < ( sizeof( correctiondata.correction ) / sizeof( uint8_t ) ); check_cnt++ ) {

		if ( correctiondata.correction[ check_cnt ] == 0 ) {

			unused_cnt++;
		}

		if ( unused_cnt >= 3 ) {

			return SYS_NG;
		}
	}

	Judgement judgement;

	int8_t result_check = 0;//判定結果
	COORDINATE coordinate = correctiondata.coordinate;//補正座標
	float angle = correctiondata.angle;//補正角度
	uint8_t pattern[ 3 ];//使用軸
	float degree = 0;//機体角度(degree)
	float radian = 0;//機体角度(radian)
	float senser_pos = 0;//機体の中心座標からセンサまでの距離
	
	memset( pattern, 0, sizeof( pattern ) );
	memcpy( pattern, correctiondata.correction, sizeof( pattern ) );

	//インスタンスを取得
	CarData &cardata = CarData::getInstance();

	//判定
	result_check = judgement.judge( correctiondata.decisionData );

	if ( result_check <= SYS_NG ) {

		return SYS_NG;
	}

	//判定
	if ( result_check == RESULT_TRUE ) {

		//補正座標・機体角度設定
		if ( pattern[ XPOS ] == 1 || pattern[ YPOS ] == 1 ) {

			if ( ( correctiondata.decisionData.decision[ 0 ] == RGB )
				|| ( correctiondata.decisionData.decision[ 0 ] == HSV )
				|| ( correctiondata.decisionData.decision[ 0 ] == UltraSonic ) ) {

				degree = cardata.getAngle();

				//degreeをradianに変換
				radian = degree * ( M_PI / 180 );

				if ( ( correctiondata.decisionData.decision[ 0 ] == RGB )
					|| ( correctiondata.decisionData.decision[ 0 ] == HSV ) ) {

					senser_pos = COLORSENSOR_POS;//カラーセンサの位置
				}
				else if ( correctiondata.decisionData.decision[ 0 ] == UltraSonic ) {

					senser_pos = ULTRASONICSENSOR_POS;//超音波センサの位置
				}

				if ( pattern[ XPOS ] == 1 ) {//X軸補正

					coordinate.x = coordinate.x + ( senser_pos / 10 ) * sin( radian );

					//座標設定
					result_check = cardata.setPosX( coordinate.x );

					if ( result_check <= SYS_NG ) {

						return SYS_NG;
					}
				}
				if ( pattern[ YPOS ] == 1 ) {//Y軸補正

					coordinate.y = coordinate.y - ( senser_pos / 10 ) * cos( radian );

					//座標設定
					result_check = cardata.setPosY( coordinate.y );

					if ( result_check <= SYS_NG ) {

						return SYS_NG;
					}
				}
			}
		}
		if ( pattern[ ANGLE ] == 1 ) {//機体角度補正

			//機体角度設定
			result_check = cardata.setAngle( angle );

			if ( result_check <= SYS_NG ) {

				return SYS_NG;
			}
		}

		return RESULT_TRUE;
	}
	else if ( result_check == RESULT_FALSE ) {

		return RESULT_FALSE;
	}
}