
#include "../../include/Steering/RightMotor.h"
#include "../../include/Steering/Motor.h"

RightMotor::RightMotor()
{
    portNum = EV3_PORT_B;
    ev3_motor_config( static_cast<motor_port_t>(portNum), LARGE_MOTOR);
    ev3_motor_reset_counts(static_cast<motor_port_t>(portNum));
}

RightMotor::~RightMotor()
{
}