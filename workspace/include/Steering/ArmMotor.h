#pragma once
#include"../system/system.h"
#include"./Motor.h"

class ArmMotor:public Motor
{
private:
    /* data */
	int32 std_angle;
    ArmMotor();
    ~ArmMotor();
    ArmMotor( const ArmMotor &x );
	
	ArmMotor&operator=( const ArmMotor & ) { return *this; };
public:
	int8 setCounts(int32 motorAngle, int32 motorPower);
    static ArmMotor &getInstance( )
	{
		static ArmMotor ArmMotor_;
		return ArmMotor_;
	}
};