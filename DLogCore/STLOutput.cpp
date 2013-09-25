#include "../DLog.h"
#include "DLogInitializer.h"

#include <iostream>

void STLOutputFunction(Severity severity, const char* functionName, unsigned int line, const char* msg)
{
	static const char* severity_msg[] = {
		" ", "__WARNING__ ", "~~ERROR~~ ", "##FATAL## ", "!!ASSERT!! "
	};
	std::cout << severity_msg[static_cast<int>(severity)] << functionName << '(' << line << ')' << msg;
}

static DLogInitializer init(STLOutputFunction);

DLogger& operator<<(DLogger& d, const std::string& item)
{
	return d.print(item.c_str());
}
