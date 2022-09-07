///
/// @file 台形制御クラス
/// @note 台形式による速度制御クラス
/// @date 2022/06/29 谷口拓海
///

#ifndef TARPEZOID_HEADER
#define TARPEZOID_HEADER

#include "../system/system.h"
#include "AccelerationDesigner.h"
#include <ostream>
#include <cstdio>
#include <fstream>

using namespace std;



#define RPS				(   2.75)				/* モーターの回転速度 [r/s]	 */
#define WHEEL_WIDTH		(	CAR_WHEEL_WIDTH)	/* 車輪の直径(mm)			 */
	
#ifdef SPIKE
#define RPS				(   2.25)				/* モーターの回転速度 [r/s]	 */
#endif

#define V_MAX_WHEEL		(RPS * WHEEL_WIDTH * PI)/* 最大回転速度				 */
#define JERK_MAX		( 15000.0)				/* 最大躍度					 */
#define ACCEL_MAX		( V_MAX_WHEEL)			/* 最大加速度				 */
#define VELOCITY_MAX	(  100.0)				/* 最大速度					 */
#define VELOCITY_MIN	(    0.0)				/* 最低速度					 */
#define EXECTION_COUNT	(   0.01)				/* 経過時間					 */

class TrapezoidControl {
public:
	TrapezoidControl();
	~TrapezoidControl();

	TrapezoidControl( const TrapezoidControl &x );
	TrapezoidControl&operator=( const TrapezoidControl & ) { return *this; };

	double run(double input);
	int8_t setVelocity(double velocity);

	static TrapezoidControl &getInstance()
	{
		static TrapezoidControl TrapezoidControl_;		// インスタンスの生成
		return TrapezoidControl_;
	}

private:
	AccelDesigner ad;
	double run_time;
	double start;
	double target;
	double distance;
	double motor_revision;
	double pre_deviation;
	double pre_target;
	double time_fst;
	double v_target = 0;							/* 目標速度					 */
	double v_start = 0;							/* 初速度					 */

	int8_t calc(void);

	double conversion();
};

#endif