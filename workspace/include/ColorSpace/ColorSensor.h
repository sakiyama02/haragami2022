#include "../system/system.h"


#ifndef _ColorSensor_H_
#define _ColorSensor_H_
class ColorSensor
{
private:
		static ColorSensor* _singleton;

public:
	int8_t Init();
	static RGB_DATA getRGB();
	static ColorSensor& getInstance()
    {
	static ColorSensor ColorSensor_;	
    return ColorSensor_;
    }
	ColorSensor();

	~ColorSensor();
}; 
#endif