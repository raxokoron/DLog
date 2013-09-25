#include "../DLog.h"

#include <cstdarg>

extern "C"
{

void cDLogger(int line, const char* prettyFunction, Severity severity, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	DLogger d(line, prettyFunction, severity);
	d.print(format, args);
	va_end(args);
}

}
