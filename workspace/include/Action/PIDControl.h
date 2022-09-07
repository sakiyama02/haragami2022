#pragma once
#define DELTA_TIME 0.01f

#include "../system/system.h"
#include "./Controller.h"

class PIDControl : public Controller
{
private:
    GAIN gain;
    double target;
    double stack_integral;
    double prevdeviation;
    int8 calc();
public:
    PIDControl();
    ~PIDControl();
    int8 init(GAIN);
    static PIDControl& getInstance()
    {
        static PIDControl PIDControl_;	// インスタンスの生成 
        return PIDControl_;
    }
};