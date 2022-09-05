

/* -------------------------------------------------------------------------- */
/* includeファイル                                                            */
/* -------------------------------------------------------------------------- */

#include "../../include/system/system.h"

#include "../../include/ColorSpace/ColorSpace.h"
#include "../../include/ColorSpace/ColorSensor.h"
#include "../../include/ColorSpace/HSV.h"
ColorSpace::ColorSpace(){
    rgb.r=0;
    rgb.g=0;
    rgb.b=0;
    hsv.h=0;
    hsv.s=0;
    hsv.v=0;
    ColorSensor color_sensor =ColorSensor::getInstance();
    color_sensor.Init();
}
ColorSpace::~ColorSpace(){}

int8 ColorSpace::update(){
    ColorSensor color_sensor =ColorSensor::getInstance();
    HSV hsvdata;
    rgb = color_sensor.getRGB();
    hsv = hsvdata.convert(rgb);

    return SYS_OK;
}
RGB_DATA ColorSpace::getRGB(){
    return rgb;
}
HSV_DATA ColorSpace::getHSV(){

    return hsv;
}