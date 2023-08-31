#pragma once
#include "CarBase.h"
class RightFrontWheel;


class Car_RB6:public CarBase, Noncopyable
{
public:
	Car_RB6();
	~Car_RB6();
private:
	
	RightFrontWheel* m_rightfrontwheel;
};

