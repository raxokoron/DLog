#pragma once

#include "../DLog.h"

class DLogInitializer
{
public:
	DLogInitializer(DLogger::OutputFunction func)
	{
		DLogger::setDefaultOutputFunction(func);
	}
};


