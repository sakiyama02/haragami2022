#pragma once
#include "UseJudgement.h"
#include "../system/system.h"
enum GarageColor
{
  YELLOWTHRESHOL,
  REDTHRESHOLD ,
  GREENTHRESHOLD,
  BLUETHRESHOLD ,
};

class PaternGarage : public UseJudgement {

private:
    RGB_DATA rgb;
public:
    PaternGarage();

    ~PaternGarage();

    int8_t decide(); 

};
