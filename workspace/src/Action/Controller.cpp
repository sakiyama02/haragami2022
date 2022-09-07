#include "../../include/Action/Controller.h"

Controller::Controller(){
    motor_revision=0;
    deviation=0;
}

Controller::~Controller(){}


int8 Controller::run(double _deviation){
    deviation=_deviation;
    calc();
    motor_revision=round(motor_revision);
    return motor_revision;
}

int8 Controller::calc(){
    return SYS_OK;
}
