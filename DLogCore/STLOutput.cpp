#include "../DLog.h"
#include "DLogInitializer.h"

#ifndef NO_STL

#ifdef STL_OUTPUT
#include <iostream>

void STLOutputFunction(Severity severity, const char* functionName, unsigned int line, const char* msg)
{
	static const char* severity_msg[] = {
		"   INFO     ", 
		"__WARNING__ ", 
		" ~~ERROR~~  ", 
		" ##FATAL##  ", 
		" !!ASSERT!! "
	};
	std::cout << severity_msg[static_cast<int>(severity)] << functionName << '(' << line << "): " << msg << std::endl;
}

static DLogInitializer init(STLOutputFunction);
#endif // STL_OUTPUT

DLogger& operator<<(DLogger& d, const std::string& item)
{
	return d.print(item.c_str());
}

#endif // NO_STL
