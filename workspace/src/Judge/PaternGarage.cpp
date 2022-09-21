#include "../../include/Judge/PaternGarage.h"
#include "../../include/ColorSpace/ColorSpace.h"

PaternGarage::PaternGarage(){}

PaternGarage::~PaternGarage(){}

int8_t PaternGarage::decide(){
    ColorSpace color = ColorSpace::getInstance();
    rgb=color.getRGB();
    //printf("r:%d,g:%d,b:%d\n",rgb.r,rgb.g,rgb.b);
    //黄色
    if(rgb.r>100&&rgb.g>100&&rgb.b<30){
        return YELLOWTHRESHOLD;
    }
    //赤
    else if(rgb.r>90){
        return REDTHRESHOLD;
    }
    //緑
    else if(rgb.g>70){
        return GREENTHRESHOLD;
    }
    //青
    else if(rgb.b>100){
        return BLUETHRESHOLD;
    }
    else{
        //return EMPTYTHRESHOLD;
        return REDTHRESHOLD;
    }
}
