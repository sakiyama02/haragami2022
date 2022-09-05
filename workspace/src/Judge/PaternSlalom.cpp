#include "../../include/Judge/PaternSlalom.h"
#include "../../include/Sonic/UltraSonic.h"
PaternSlalom::PaternSlalom(){
    distance=0;
}

PaternSlalom::~PaternSlalom(){}

int8_t PaternSlalom::decide(){
    int8_t slalomstate=0;
    UltraSonic ultrasonic = UltraSonic::getInstance();
    distance=ultrasonic.getDistance();
    //距離によってパターン１，２を判定する
    if(distance<10){
        slalomstate=SLALOMPATERNA;
    }
    else{
        slalomstate=SLALOMPATERNB;
    }
    return slalomstate;
}
