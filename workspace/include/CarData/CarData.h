#pragma once
#include"../system/system.h"
#include"../Steering/Steering.h"


typedef struct WheelDist_s
{
	double left;
	double right;
} WheelDist;

class CarData
{
private:
	COORDINATE position;
	double car_angle;

	CarData( );
	~CarData( );
	CarData( const CarData &x );
	CarData&operator=( const CarData & ) { return *this; };

	int8 calcOdometry( WheelDist* wheel_dist );
public:
	static CarData &getInstance( )
	{
		static CarData carPosition;
		return carPosition;
	}

	int8 update( );

	COORDINATE getPos( void );

	int8 setPos( COORDINATE coordinate );

	int8 setPosX( double pos_x );

	int8 setPosY( double pos_y );

	double getAngle( void );

	int8 setAngle( double angle );
};