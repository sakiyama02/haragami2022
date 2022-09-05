#pragma once
#define SLALOMPATERNA 1
#define SLALOMPATERNB 2

#include "../system/system.h"
#include "../../include/Judge/UseJudgement.h"
class PaternSlalom  : public UseJudgement
{
private:
    int16 distance;
public:
    PaternSlalom();

    ~PaternSlalom();

    int8_t decide(); 
};

