#pragma once
#include "../system/system.h"

/// 2022/07/13
/// yoshitome
/// Action.h

class Action {
    private:

    public:
		Action();
		~Action() ;

        virtual int8_t run(int32_t speed) =0;

};