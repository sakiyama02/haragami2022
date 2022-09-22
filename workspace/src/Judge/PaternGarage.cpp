#include "../../include/Judge/PaternGarage.h"
#include "../../include/ColorSpace/ColorSpace.h"

PaternGarage::PaternGarage(){}

PaternGarage::~PaternGarage(){}

int8_t PaternGarage::decide(){
    ColorSpace color = ColorSpace::getInstance();
    rgb=color.getRGB();
    //printf("r:%d,g:%d,b:%d\n",rgb.r,rgb.g,rgb.b);
    //黄色
    if(rgb.r>70&&rgb.g>70&&rgb.b<30){
        return YELLOWTHRESHOLD;
    }
    //赤
    else if(rgb.r>80&&rgb.g<30&&rgb.b<30){
        return REDTHRESHOLD;
    }
    //緑
    else if(rgb.r<30&&rgb.g>60&&rgb.b<30){
        return GREENTHRESHOLD;
    }
    //青
    else if(rgb.r<40&&rgb.g<70&&rgb.b>80){
        return BLUETHRESHOLD;
    }
    else{
        return EMPTYTHRESHOLD;
        //return REDTHRESHOLD;
    }
}
