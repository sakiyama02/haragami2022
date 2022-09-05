#include "../../include/Action/LineTrace.h"

/// コンストラクタ引数なし
LineTrace::LineTrace()
{
	memset(&gain,0,sizeof(GAIN));
	target_val = 0;
	edge = 0;
}

/// コンストラクタ引数あり
/// メンバー変数に格納
LineTrace::LineTrace(GAIN _gain,float _target_val,int8_t _edge,COORDINATE _coordinate)
{
	gain = _gain;
	target_val = _target_val;
	target_coordinate = _coordinate;
	edge = _edge;
	
}

LineTrace::~LineTrace()
{

}

int8_t LineTrace::run(int32_t speed)
{
	// 引数チェック
	if ( speed < -100 || speed > 100 )
	{
		//std::cout << "LineTrace PARAM err  value = " << speed << std::endl;
		return SYS_PARAM;
	}
	

	// 変数宣言
	ColorSpace&		  color_space	= ColorSpace::getInstance();
	PIDControl& 	  pid_control	= PIDControl::getInstance();
	CarData&		  car_data		= CarData::getInstance();
	TrapezoidControl& trapezoid 	= TrapezoidControl::getInstance();
	Steering&		  steering		= Steering::getInstance();

	HSV_DATA 	hsv_data;
	COORDINATE 	current_coordinate;
	MOTOR_POWER motor_power;
	float 		deviation 		= 0.0f;
	float 		pid_revision 	= 0.0f;
	float		distance		= 0.0f; 
	float		motor_revision  = 0.0f;
	color_space.update();
	// 色空間からhsv値を取得してから、閾値と取得した値との差分をpid制御へ渡し、操作量を取得する
	hsv_data 		= color_space.getHSV();
	deviation		= target_val - hsv_data.v;
	pid_control.init(gain);
	pid_revision 	= pid_control.run(deviation);

	// 目標座標までの距離を算出し台形制御に現在速度を取得する
	trapezoid.setVelocity(speed);
	current_coordinate = car_data.getPos();
	distance = std::sqrt(std::pow(current_coordinate.x - target_coordinate.x,2)+
						 std::pow(current_coordinate.y - target_coordinate.y,2));
	motor_revision = trapezoid.run(distance);

	if ( edge == LEFT_LINE ){
		motor_power.right =motor_revision - pid_revision;
		motor_power.left  =motor_revision + pid_revision;
	} else if ( edge == RIGHT_LINE ){
		motor_power.right =motor_revision + pid_revision;
		motor_power.left  =motor_revision - pid_revision;
	}
	steering.run(motor_power);

	return SYS_OK;
}