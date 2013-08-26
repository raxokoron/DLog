#pragma once

#include <string>

void OutputSTL(Severity severity, const char* functionName, unsigned int line, const char* msg);

DLoggerImpl& operator<<(DLoggerImpl& d, const std::string& item);


