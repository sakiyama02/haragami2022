#include "../../include/Steering/TailMotor.h"
#include "../../include/Steering/Motor.h"

TailMotor::TailMotor()
{
	portNum = EV3_PORT_D;
	ev3_motor_config( static_cast<motor_port_t>(portNum), MEDIUM_MOTOR );
	ev3_motor_reset_counts(static_cast<motor_port_t>(portNum));
	tslp_tsk(10000);
	std_angle = getCounts();

}

TailMotor::~TailMotor()
{
}


int8 TailMotor::setCounts(int32 motorAngle, int32 motorPower)
{
    if (motorPower < -100 || motorPower > 100)
    {
        return SYS_PARAM;
    }
    int8 retChk = SYS_NG;
    int32 curAngle = 0;
    int32 angle =  getCounts() - std_angle;
	  int32 move_angle = motorAngle - angle;

    /* 指定回転角度まで回転を続ける */
    if(move_angle > 5)
    {
		setPWM(motorPower);

    }
    else if(move_angle < -5)
    {
		setPWM(-motorPower);

    }else{
		setPWM(0);
    return SYS_OK;
	}
   
  
    return SYS_NG;
}