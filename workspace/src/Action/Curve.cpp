/// 2022/07/13
/// yoshitome
/// Curve

#include "../../include/Action/Curve.h"

/// コンストラクタ引数なし
Curve::Curve(){};

/// コンストラクタ引数あり
Curve::Curve(double _radius, int8_t _direction,COORDINATE _coordinate){
    target_coordinate   = _coordinate;
	direction           = _direction;
	radius 				= _radius; 
}

Curve::~Curve(){};

int8_t Curve::run(int32_t speed){
    if( speed < -100 || speed > 100 ) {
        return SYS_PARAM;
    }
    // 変数宣言
    CarData&            car_data    = CarData::getInstance();
    TrapezoidControl&   trapezoid   = TrapezoidControl::getInstance();
	Steering&			steering	= Steering::getInstance();
	double           ratio_left;             // 左比率
    double           ratio_right;            // 右比率
    double           angle;                  // 角度
    double           circle;                 // 円周
    double			motor_revision;
	COORDINATE      current_coordinate;     // 自己位置
    MOTOR_POWER     motor_power;            // モーターパワー
	double           target_distance;        // 目標直線距離
    double           theta;                  // シータ


    // 変数初期化
    target_distance     = 0.0f;
    circle              = 0.0f;
    ratio_left          = 0.0f;
    ratio_right         = 0.0f;
    current_coordinate  = car_data.getPos();

    /// 走行距離計算
    // 自己位置、目標座標感の距離計算
    // 直線距離 = √ (x2-x)(x2-x) + (y2-y)(y2-y)
    //target_distance = std::sqrt( std::pow(target_coordinate.x - current_coordinate.x, 2) + std::pow(target_coordinate.y - current_coordinate.y, 2) );
    //if (target_distance > (radius * 2.0f)) {
	//	target_distance = (radius * 2.0f);
	//}
    // 半径 半径 目標座標までの距離　から角度計算
    //        b*b + c*c - a*a
    // cosA = ----------------
    //              2bc

    theta = ((std::pow(radius, 2) * 2) - std::pow(target_distance, 2)) / (std::pow(radius, 2) * 2);

    angle = (double)180 / PI * (acos(theta));

    //printf("%f,%f\n",current_coordinate.x,current_coordinate.y);

    // 角度と辺の長さから扇形の円周を求める
    // 円周　＝　2πr * (角度 / 360)
    circle = (2 * PI * radius * angle) / 360;

    //printf("%f\n",angle);

    /// 加減速どうこう
	trapezoid.setVelocity(speed);
	motor_revision = trapezoid.run(circle);
    
    /// 比率計算@
    // 左カーブの比率
    if( direction == LEFT_CURVE ) {
        ratio_left = (radius - (CAR_WIDTH / 2)) / (radius + (CAR_WIDTH / 2));
        ratio_right = 1;
    } 
    // 左カーブの比率
    else if( direction == RIGHT_CURVE ) {
        ratio_left  = 1;
        ratio_right = (radius - (CAR_WIDTH / 2)) / (radius + (CAR_WIDTH / 2));
    }
    // カーブの比率計算
    motor_power.left = motor_revision * ratio_left;
    motor_power.right = motor_revision * ratio_right;

	//printf("%d,%d\n",motor_power.left,motor_power.right);
	steering.run(motor_power);

    return SYS_OK;


}