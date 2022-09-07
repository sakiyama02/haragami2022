#include "../../include/Action/Turn.h"

Turn::Turn(unsigned char _angle) {
	angle=_angle;
}
Turn::~Turn() {}

int8_t Turn::run(int32_t speed)
{

	int8 retChk = SYS_NG;
	double nowAngle = 0.0f;
	MOTOR_POWER motor_power;
	CarData&		 carPosiiton = CarData::getInstance();
	Steering         &steering = Steering::getInstance();

	memset(&motor_power, 0, sizeof(motor_power));

	// 現在の車体角度取得
	nowAngle = carPosiiton.getAngle();
	printf("nowangle:%f,angle:%f\n",nowAngle,angle);
	// 方向を決める
	if ( angle==1 ) {
		motor_power.left = -speed;
		motor_power.right = speed;
	}
	else {
		motor_power.left = speed;
		motor_power.right = -speed;
	}

	steering.run(motor_power);
	return SYS_OK;
}