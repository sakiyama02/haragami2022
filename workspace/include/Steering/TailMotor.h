#pragma once
#include"../system/system.h"
#include"./Motor.h"

class TailMotor:public Motor
{
private:
    /* data */
	int32 std_angle;
    TailMotor();
    ~TailMotor();
    TailMotor( const TailMotor &x );
	
	TailMotor&operator=( const TailMotor & ) { return *this; };
public:
	int8 setCounts(int32 motorAngle, int32 motorPower);
    static TailMotor &getInstance( )
	{
		static TailMotor TailMotor_;
		return TailMotor_;
	}
};