#pragma once
#include"../system/system.h"
#include"../Steering/Steering.h"


#define PI (3.141592653589793f)
#define DIST (((PI) * CAR_WHEEL_WIDTH) / 360.0f)

typedef struct WheelDist_s
{
	float left;
	float right;
} WheelDist;

class CarData
{
private:
	COORDINATE position;
	float car_angle;

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

	int8 setPosX( float pos_x );

	int8 setPosY( float pos_y );

	float getAngle( void );

	int8 setAngle( float angle );
};