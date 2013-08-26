#include "DLogImpl.h"

#include <iostream>

void OutputSTL(Severity severity, const char* functionName, unsigned int line, const char* msg)
{
	static const char* severity_msg[] = {
		" ", "__WARNING__ ", "~~ERROR~~ ", "##FATAL## ", "!!ASSERT!! "
	};
	std::cout << severity_msg[static_cast<int>(severity)] << functionName << '(' << line << ')' << msg;
}

DLoggerImpl& operator<<(DLoggerImpl& d, const std::string& item)
{
	return d.print(item.c_str());
}
