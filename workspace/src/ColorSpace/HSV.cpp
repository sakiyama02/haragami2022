

/* -------------------------------------------------------------------------- */
/* includeファイル                                                            */
/* -------------------------------------------------------------------------- */

#include "../../include/system/system.h"
#include "../../include/ColorSpace/ColorSpace.h"
#include "../../include/ColorSpace/HSV.h"


HSV::HSV(){}
HSV::~HSV(){}

HSV_DATA HSV::convert(RGB_DATA rgb){
    int16_t red = 0;
    int16_t green = 0;
    int16_t bule = 0;
    red=rgb.r;
    green=rgb.g;
    bule =rgb.b;
    double h=0.0f;
    double s=0.0f;
    double v=0.0f;
    HSV_DATA hsv_Data;
    //赤が最大の時
    if((red>green)&&(red>bule)){
        if(green>=bule){
            h=(double)(60*((double)(green-bule)/(double)(red-bule)));
            s=(double)((double)(red-bule)/red)*255;
        }else{
            h=(double)(60*((double)(green-bule)/(double)(red-green)));
            s=(double)((double)(red-green)/red)*255;
        }    
        hsv_Data.v=red;
    }
    //青が最小の時
    if((red==green)&&(red>bule)){
        if(green>=bule){
            h=(double)(60*((double)(green-bule)/(double)(red-bule)));
            s=(double)((double)(red-bule)/red)*255;
        }
        hsv_Data.v=red;
    }
    
    //青が最大の時
    if((bule>green)&&(bule>red)){
        if(green>=red){
            h=(double)(60*((double)(red-green)/(double)(bule-red)))+240;
            s=(double)((double)(bule-red)/bule)*255; 
        }else{
            h=(double)(60*((double)(red-green)/(double)(bule-green)))+240;
            s=(double)((double)(bule-green)/bule)*255; 
        }
        hsv_Data.v=bule;
    }
    
    //赤が最小の時
    if((bule==green)&&(bule>red)){
         if(green>=red){
            h=(double)(60*((double)(red-green)/(double)(bule-red)))+240;
            s=(double)((double)(bule-green)/bule)*255; 
        }
         hsv_Data.v=bule;
    }
    
    //緑が最大の時
    if((green>red)&&(green>bule)){
        if(red>=bule){
            h=(double)(60*((double)(red-green)/(double)(green-bule)))+120;
            s=(double)((double)(green-bule)/green)*255; 
        }else{
            h=(double)(60*((double)(red-green)/(double)(green-red)))+120;
            s=(double)((double)(green-red)/green)*255;
        } 
        hsv_Data.v=green;
    }
    
    //緑が最小の時
    if((bule==red)&&(bule>green)){
        if(red>=green){
            h=(double)(60*((double)(red-green)/(double)(bule-green)))+240;
            s=(double)((double)(bule-green)/bule)*255; 
        }
         hsv_Data.v=green;
    }
    hsv_Data.h=h;
    hsv_Data.s=s;
    //最大と最小の時
    if((red==green)&&(green==bule)){
        hsv_Data.h=0;
        hsv_Data.s=0;
        hsv_Data.v=red;
    }
    //Hの値がマイナスの時
    if(hsv_Data.h<0){
        hsv_Data.h=hsv_Data.h+360;
    }
    return  hsv_Data;
}