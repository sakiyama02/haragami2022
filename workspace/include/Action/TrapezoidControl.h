///
/// @file ��`����N���X
/// @note ��`���ɂ�鑬�x����N���X
/// @date 2022/06/29 �J����C
///



#ifndef TARPEZOID_HEADER
#define TARPEZOID_HEADER

#include "../system/system.h"
#include "AccelerationDesigner.h"
#include <ostream>
#include <cstdio>
#include <fstream>

using namespace std;

#define DEBUG_EV3
//#define DEBUG_SPIKE

#define PI				(3.141592653589793f)	/* �~����					 */

#ifdef DEBUG_EV3
//#define RPS				(   2.31f)				/* ���[�^�[�̉�]���x [r/s]	 */
#define RPS				(   2.75)
#define WHEEL_WIDTH		(	CAR_WHEEL_WIDTH)				/* �ԗւ̒��a(mm)			 */
#define V_MAX_WHEEL		(RPS * WHEEL_WIDTH * PI)	
												/* �ő��]���x				 */
#endif

#ifdef DEBUG_SPIKE
#define RPS				(   2.25)				/* ���[�^�[�̉�]���x [r/s]	 */
#define WHEEL_WIDTH		(100.0)				/* �ԗւ̒��a(mm)			 */
#define V_MAX_WHEEL		(RPS * WHEEL_WIDTH * PI)	
												/* �ő��]���x				 */
#endif

#define JERK_MAX		( 15000.0)				/* �ő���x					 */
#define ACCEL_MAX		( V_MAX_WHEEL)				/* �ő�����x				 */
#define VELOCITY_MAX	(  100.0f)				/* �ő呬�x					 */
#define VELOCITY_MIN	(    0.0f)				/* �Œᑬ�x					 */
#define EXECTION_COUNT	(   0.01f)				/* �o�ߎ���					 */

class TrapezoidControl {
public:
	TrapezoidControl();
	~TrapezoidControl();

	TrapezoidControl( const TrapezoidControl &x );
	TrapezoidControl&operator=( const TrapezoidControl & ) { return *this; };

	float run(float input);
	int8_t setVelocity(float velocity);

	static TrapezoidControl &getInstance()
	{
		static TrapezoidControl TrapezoidControl_;	// �C���X�^���X�̐���
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

	float conversion();
};

#endif