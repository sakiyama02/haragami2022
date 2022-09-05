#ifndef CORRECTION
#define CORRECTION

#include "../system/system.h"

#define COLORSENSOR_POS 60
#define ULTRASONICSENSOR_POS 50

#define RGB 4
#define HSV 5
#define UltraSonic 6

#define XPOS 0
#define YPOS 1
#define ANGLE 2

class Correction {

public:

	int8_t run( CorrectionData correctionData );
};

#endif // !CORRECTION