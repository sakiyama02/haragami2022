#include "../../include/CarData/CarData.h"

/* -------------------------------------------------------------------------*/
/* 関数名		： CarPosition				              	    			*/
/* 機能名		： コンストラクタ                                  			 */
/* 機能概要		： 座標と向きの初期化										  */
/* 引数			： なし														*/
/* 戻り値		： なし                                     				*/
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				 */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				 */
/* -------------------------------------------------------------------------*/
CarData::CarData( )
{
	car_angle = 0.0f;

	/* Lコース初期位置座標 */
	position.x = 2494.0f;//3552 * 0.3527 * 2;
	position.y = 242.0f;//93 * 0.3527 * 2;
}

CarData::~CarData( ) {}

/* -------------------------------------------------------------------------*/
/* 関数名		： update									    			*/
/* 機能名		： 更新       												*/
/* 機能概要		： 自己位置を更新する                   					  */
/* 引数			： なし														*/
/* 戻り値		： int8				:0				:正常終了				 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
int8 CarData::update( void )
{
	int8 retChk = SYS_NG;
	Steering &steering = Steering::getInstance( );
	MOTOR_ANGLE preAngle;
	MOTOR_ANGLE nowAngle;
	WheelDist wheelDist;

	memset( &preAngle, 0, sizeof( MOTOR_ANGLE ) );
	memset( &nowAngle, 0, sizeof( MOTOR_ANGLE ) );
	memset( &wheelDist, 0, sizeof( WheelDist ) );

	preAngle = steering.getMotorAngle( );
	
	retChk = steering.update( );
	if ( retChk != SYS_OK ) {
		return retChk;
	}

	nowAngle = steering.getMotorAngle( );

	wheelDist.left = (double)(nowAngle.left - preAngle.left);
	wheelDist.right = (double)(nowAngle.right - preAngle.right);

	wheelDist.left *= DIST;
	wheelDist.right *= DIST;

	retChk = calcOdometry( &wheelDist );
	if ( retChk != SYS_OK ) {
		return retChk;
	}
	
	if ( car_angle >= 600 || car_angle <= -600 ) {		
		//act_tsk( END_TASK );
		return SYS_NG;
	}
	return SYS_OK;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： calcOdometry								    			 */
/* 機能名		： オドメトリ計算 											  */
/* 機能概要		： オドメトリ計算を行う                   	   				  */
/* 引数			： WheelDist*       :wheel_dist     :両モータの差分			 */
/* 戻り値		： int8				:0				:正常終了				 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
int8 CarData::calcOdometry( WheelDist* wheel_dist )
{
	if ( wheel_dist == NULL ) {
		return SYS_PARAM;
	}
	double  angle = 0.0f;
	double dist = 0.0f;
	double rad = 0.0f;
	double addRad = 0.0f;
	COORDINATE addPos;

	memset( &addPos, 0, sizeof( COORDINATE ) );

	dist = (double)(wheel_dist->right + wheel_dist->left) / 2.0f;
	angle = (double)(360.0f / (2.0f * PI * CAR_WIDTH)) * (wheel_dist->left - wheel_dist->right);

	addRad = ((double)(angle)) * (PI / 180.0f);
	rad = ((double)(car_angle)) * (PI / 180.0f);

	addPos.x = (double)-(dist * std::sin( rad + addRad / 2.0f ));
	addPos.y = (double)(dist * std::cos( rad + addRad / 2.0f ));

	position.x += addPos.x;
	position.y += addPos.y;

	car_angle += angle;

	return SYS_OK;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： getPos							    	    			*/
/* 機能名		： 自己位置座標を取得 										  */
/* 機能概要		： 自己位置座標を返す                   	   		   		  */
/* 引数			： none														*/
/* 戻り値		： COORDINATE		:position		:現在位置座標（ｘ、ｙ）	  */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
COORDINATE CarData::getPos( void )
{
	return position;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： setPos							    	    			 */
/* 機能名		： 自己位置座標(x,y)を上書き 								  */
/* 機能概要		： 自己位置座標(x,y)を上書きする                   			  */
/* 引数			： COORDINATE		:coordinate     :座標					 */
/* 戻り値		： int8				:0				:正常終了				 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
int8 CarData::setPos( COORDINATE coordinate )
{
	position = coordinate;
	return SYS_OK;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： setPosX							    	    			 */
/* 機能名		： 自己位置座標(x)を上書き 									  */
/* 機能概要		： 自己位置座標(x)を上書きする                   			  */
/* 引数			： double			:pos_x		    :X座標					 */
/* 戻り値		： int8				:0				:正常終了				 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
int8 CarData::setPosX( double pos_x )
{
	position.x = pos_x;
	return SYS_OK;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： setPosY							    	    			 */
/* 機能名		： 自己位置座標(y)を上書き 									  */
/* 機能概要		： 自己位置座標(y)を上書きする                   			  */
/* 引数			： double			:pos_y		    :X座標					 */
/* 戻り値		： int8				:0				:正常終了				 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
int8 CarData::setPosY( double pos_y )
{
	position.y = pos_y;
	return SYS_OK;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： getAngle							    	    			*/
/* 機能名		： 自己位置角度を取得		            	    			  */
/* 機能概要		： 自己位置角度を返す	                                     */
/* 引数			： none														*/
/* 戻り値		： double			:car_angle		:自己位置角度			 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
double CarData::getAngle( void )
{
	return car_angle;
}

/* -------------------------------------------------------------------------*/
/* 関数名		： setAngle							    	    			*/
/* 機能名		： 自己位置角度を上書き		            	    			  */
/* 機能概要		： 自己位置角度を上書きする                                   */
/* 引数			： double            :angle          :角度					*/
/* 戻り値		： int8				:0				:正常終了				 */
/* 作成日		： 2021/07/23		 崎山　勇人		 新規作成				  */
/* 作成日		： 2022/07/16		 山田　龍之介	:新規作成				  */
/* -------------------------------------------------------------------------*/
int8 CarData::setAngle( double angle )
{
	car_angle = angle;
	return SYS_OK;
}
