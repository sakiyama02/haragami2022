
/* -------------------------------------------------------------------------- */
/* includeファイル                                                            */
/* -------------------------------------------------------------------------- */

#include "../../include/ColorSpace/ColorSensor.h"
#include "../../include/system/system.h"
ColorSensor::ColorSensor(){}
ColorSensor::~ColorSensor(){}
int8_t ColorSensor::Init(){
	int8_t che = 0;
	ER errChk = ev3_sensor_config(static_cast<sensor_port_t>(SENSOR_COLOR), COLOR_SENSOR);
	if (errChk != E_OK)
	{
		//msg.LOG(LOG_ID_ERR, "init ev3_sensor_config エラー");
		return SYS_NG;
	}
	return SYS_OK;
}
RGB_DATA ColorSensor::getRGB(){
	rgb_raw_t rgbTmp;
	RGB_DATA rgb_Data;
	memset(&rgbTmp,0,sizeof(rgb_raw_t));
	ev3_color_sensor_get_rgb_raw(static_cast<sensor_port_t>(SENSOR_COLOR), &rgbTmp);

	rgb_Data.r = rgbTmp.r;
	rgb_Data.g = rgbTmp.g;
	rgb_Data.b = rgbTmp.b;

	return rgb_Data;
}