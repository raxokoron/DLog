#include "../DLog.h"

void __ASSERT__(bool expr_value, const char* expression, int line, const char* func_name)
{
	if(!expr_value)
	{
		DLoggerProxy(line, func_name, Severity::ASSERT) << "Assertion " << expression << " failed;";
		exit(0);
	}
}

