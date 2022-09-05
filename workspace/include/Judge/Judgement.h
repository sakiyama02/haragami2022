#ifndef JUDGEMENT

#define JUDGEMENT

#define LOGICAL_CONJUNCTION 2//論理積
#define LOGICAL_DISJUNCTION 1//論理和

#include "../system/system.h"

class Judgement {

public:

	int8_t judge( DecisionData decisiondata );

};
#endif