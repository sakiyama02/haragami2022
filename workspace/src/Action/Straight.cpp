#include "../../include/Action/Straight.h"
#include "../../include/FileOp/FileIO.hpp"

/// コンストラクタ引数なし
Straight::Straight()
{

}

/// コンストラクタ引数あり
/// メンバー変数に格納
Straight::Straight(COORDINATE _coordinate)
{
	target_coordinate = _coordinate;
}

int8_t Straight::run(int32_t speed)
{
	// 引数チェック
	if ( speed < -100 || speed > 100 )
	{
		
		return SYS_PARAM;
	}
	
	// 変数宣言
	CarData&		  car_data		= CarData::getInstance();
	TrapezoidControl& trapezoid 	= TrapezoidControl::getInstance();
	Steering&		steering		= Steering::getInstance();

	COORDINATE 	current_coordinate;
	MOTOR_POWER motor_power;
	float		distance		= 0.0f; 
	float		motor_revision  = 0.0f;
	
	// 目標座標までの距離を算出し台形制御に現在速度を取得する
	// if文の追加　山田
	if(0>speed){
		//speedを絶対値に変換する
		speed=speed*(-1);
		trapezoid.setVelocity(speed);
	current_coordinate = car_data.getPos();
	distance = std::sqrt(std::pow(current_coordinate.x - target_coordinate.x,2)+
						 std::pow(current_coordinate.y - target_coordinate.y,2));

	motor_revision =speed;// trapezoid.run(distance);
	
	motor_revision = trapezoid.run(distance);
	
	//変換した値をマイナス値に変更
	motor_revision=motor_revision*(-1);
	motor_power.left = motor_power.right = motor_revision;

	steering.run(motor_power);

	return SYS_OK;
	}
	else{

		trapezoid.setVelocity(speed);
		current_coordinate = car_data.getPos();
		distance = std::sqrt(std::pow(current_coordinate.x - target_coordinate.x,2)+
							std::pow(current_coordinate.y - target_coordinate.y,2));

		motor_revision =speed;// trapezoid.run(distance);
		
		motor_revision = trapezoid.run(distance);

		motor_power.left = motor_power.right = motor_revision;

		steering.run(motor_power);

		my_printf("%f,%f,%f\n",current_coordinate.x,current_coordinate.y,motor_revision);


		return SYS_OK;
	}
}