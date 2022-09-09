#pragma once
#include"../system/system.h"


class Motor
{
protected:
	motor_port_t portNum;
public:
	Motor( );
	~Motor( );
	int8_t setPWM( int8_t );
	int32 getCounts();
	
private:
	
};