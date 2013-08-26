#pragma once

// C support for dlog
#ifndef __cplusplus

typedef enum
{
	SEVERITY_VERBOSE = 0,
	SEVERITY_WARNING,
	SEVERITY_ERROR,
	SEVERITY_FATAL,
	SEVERITY_ASSERT

} Severity;

#ifndef DLOG_DISABLED
void cDLogger(int line, const char* prettyFunction, Severity severity, const char* format, ...);
#define DLOG_INNER(severity, format, ...) cDLogger(__LINE__, __PRETTY_FUNCTION__, severity, format, ##__VA_ARGS__)
#else
#define DLOG_INNER(severity, format, ...) ((void)0)
#endif

#define DLOG(format, ...) DLOG_INNER(SEVERITY_VERBOSE, format, ##__VA_ARGS__)
#define DLOGW(format, ...) DLOG_INNER(SEVERITY_WARNING, format, ##__VA_ARGS__)
#define DLOGE(format, ...) DLOG_INNER(SEVERITY_PROBLEM, format, ##__VA_ARGS__)
#define DLOGF(format, ...) DLOG_INNER(SEVERITY_FATAL, format, ##__VA_ARGS__)

#endif


