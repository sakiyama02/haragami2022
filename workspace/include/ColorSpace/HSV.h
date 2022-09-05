#pragma once
#ifndef _HSV_H_
#define _HSV_H_

#include "../system/system.h"

class HSV
{
public:
	int8_t Init();
    HSV_DATA  convert(RGB_DATA rgb);
    HSV();

	~HSV();
}; 
#endif