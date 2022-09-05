#pragma once
#include "../system/system.h"

class Task {
private:
	MoveData moveData;
	CorrectionData correctionData;
	//PARAMETER parameter;
public:
	Task();
	Task(MoveData movedata,CorrectionData correctiondata);
	~Task();

	int8 init();
	int8 run();
};