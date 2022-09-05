
#include "../system/system.h"
#include "./Action.h"
#include "../CarData/CarData.h"

class Turn : public Action {
private:
	unsigned char  angle;
public:
	Turn(unsigned char );
	~Turn();

	int8_t run(int32_t speed);

};