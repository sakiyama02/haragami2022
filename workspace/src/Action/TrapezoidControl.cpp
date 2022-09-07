///
/// @file 台形制御クラス
/// @note 台形制御による速度制御を行うクラス
/// @date 2022/06/29 谷口拓海
///
#include "../../include/Action/TrapezoidControl.h"

/**
	* @brief コンストラクタ
*/
TrapezoidControl::TrapezoidControl(){
	run_time = 0;
	start = 0;
	target = 0;
	distance = 0;
	motor_revision = 0;
	pre_deviation = 0;
	time_fst = 0;
}

/**
	* @brief デストラクタ
*/
TrapezoidControl::~TrapezoidControl() {
}

/**
	* @brief 制御機能の実行を行う
	* @param deviation		偏差
	* @return 	motor_revision	モーターパワー
*/
double TrapezoidControl::run(double deviation)
{
	int8_t ret = 0.0f;								/* 戻り値チェック変数		 */

	//return (double)target;

	//printf("%f,%f,%f,",deviation,run_time,ad.t_end());

	/* 走行距離が変化した時に真 */
	if (pre_deviation < deviation) {
		time_fst = 1.0f;
		distance = deviation;
		start = pre_target;
		run_time = 0.0;

		/* 台形制御計算 */
		ret = calc();
		if (ret != SYS_OK) {
			return SYS_NG;
		}
	}

	//printf("%lf,%f,%f,",ad.x_end(),deviation,V_MAX_WHEEL);
	//printf("\n%f\n",V_MAX_WHEEL);

	if(run_time <= ad.t_end()){
		/* 瞬間速度を代入 */
		motor_revision = ad.v(run_time);
	}else{
		motor_revision = target;
		my_printf("%lf,",motor_revision);
		return motor_revision;
	}
	pre_deviation = deviation;

	/* 実行回数を加算 */
	run_time += EXECTION_COUNT;

	motor_revision = conversion();
    
	return motor_revision;
}

/**
	* @brief 目標速度を設定する
	* @param velocity:double　目標速度
	* @return SYS_OK	正常終了
	*		  SYS_NG	引数エラー
*/
int8_t TrapezoidControl::setVelocity(double velocity)
{
	/* 引数チェック */
	if (velocity < VELOCITY_MIN || velocity > VELOCITY_MAX) {
		return SYS_PARAM;
	}

	//pre_target = target;
	pre_target = motor_revision;
	target = velocity;
   
	return SYS_OK;
}

/**
	* @brief 台形制御による計算を行う
	* @param none
	* @return SYS_OK	正常終了
	*		  SYS_NG	異常終了
*/
int8_t TrapezoidControl::calc(void)
{
	v_target = (target / VELOCITY_MAX) * V_MAX_WHEEL;
	v_start = (start / VELOCITY_MAX) * V_MAX_WHEEL;

	/* 曲線作成 */
	if(start < target){
		ad.reset(JERK_MAX, ACCEL_MAX, v_target, v_start, v_target, distance * 1.55, 0, 0);
	}else{
		ad.reset(JERK_MAX, ACCEL_MAX, v_start, v_start, v_target, distance * 1.61, 0, 0);
	}

	return SYS_OK;
}

/**
	* @brief 目標速度を設定する
	* @param velocity:double　目標速度
	* @return 	正常終了
*/
double TrapezoidControl::conversion() {
	double ret_conv = 0.0f;						/* 変換後戻り値				 */

	ret_conv = (double)(((double)motor_revision * VELOCITY_MAX) / V_MAX_WHEEL);
	
	return ret_conv;
}