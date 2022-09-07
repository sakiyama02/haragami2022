#pragma once


#include "../system/system.h"

class Controller
{
protected:
    double motor_revision;
    double deviation;
    virtual int8 calc();
public:
    Controller();

    ~Controller();

    int8 run(double);
};