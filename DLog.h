#pragma once

// TODO:
// 1) Add names for pointers
// 2) Validation

// Disable log with this macro. Works on seperate files;
//#define DLOG_DISABLED

#ifdef DLOG_DISABLED
	#ifdef SEVERITY_FILTER
		#undef SEVERITY_FILTER
	#endif
	#define SEVERITY_FILTER Severity::ASSERT
#endif

#ifndef SEVERITY_FILTER
#define SEVERITY_FILTER Severity::VERBOSE
#endif

#ifdef __cplusplus
#include <cstdarg>
#include "DLogCore/DLogImpl.h"

class DLoggerProxy
{
public:
	DLoggerProxy(unsigned int line, const char* functionName, Severity severity) :
		dlogger_(line, functionName, severity)
	{}
public:
	inline void setOutputFunction(DLoggerImpl::OutputFunction func) { dlogger_.setOutputFunction(func); }
	inline void flush(){ dlogger_.flush(); }
public:
	inline DLoggerProxy& print(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		print(format, args);
		va_end(args);
		return *this;
	}
	inline DLoggerProxy& print(const char* format, va_list args)
	{
		dlogger_.print(format, args);
		return *this;
	}
public:
	template<typename T>
	inline DLoggerProxy& operator<<(const T& t)
	{
		dlogger_ << t;
		return *this;
	}
	template<typename T>
	inline DLoggerProxy& operator<<(const T* t)
	{
		dlogger_ << t;
		return *this;
	}
private:
	DLoggerImpl dlogger_;
};

class DLoggerNull
{
public:
	DLoggerNull() {}
	DLoggerNull(unsigned int line, const char* functionName, Severity severity) {}
public:
	inline void setOutputFunction(DLoggerImpl::OutputFunction func) {}
	inline void flush() {}
public:
	inline DLoggerNull& print(const char* format, ...) { return *this; }
	inline DLoggerNull& print(const char* format, va_list args) { return *this; }
public:
	template<typename T> inline DLoggerNull& operator<<(const T& t) { return *this; }
	template<typename T> inline DLoggerNull& operator<<(const T* t) { return *this; }
};

// System stuff starts
template<Severity filter, Severity severity, bool val = (filter <= severity)>
struct DLOG_GETTER
{
	typedef DLoggerProxy value_type;
};
template<Severity filter, Severity severity>
struct DLOG_GETTER<filter, severity, false>
{
	typedef DLoggerNull value_type;
};

#define DLOG_TYPE(severity) DLOG_GETTER<SEVERITY_FILTER, severity>::value_type
#define DLogger(line, functionName, severity) DLOG_TYPE(severity)(line, functionName, severity)
#define DLOG_STREAM_TYPE(__severity__) DLogger(__LINE__, __PRETTY_FUNCTION__, __severity__)
// System stuff ends

#define DLOG  DLOG_STREAM_TYPE(Severity::VERBOSE)
#define DLOGW DLOG_STREAM_TYPE(Severity::WARNING)
#define DLOGE DLOG_STREAM_TYPE(Severity::ERROR)
#define DLOGF DLOG_STREAM_TYPE(Severity::FATAL)
#define DLOGA DLOG_STREAM_TYPE(Severity::ASSERT)

#define AND << ' ' <<
#define NAMED(__var__) ' ' << #__var__ ": " << (__var__) << ' '
#define QUOTE(__var__) '\'' << (__var__) << '\''
#define DQUOTE(__var__) "\"" << (__var__) << "\""

#define __TRACER_NAME__(line) __TRACER_ ## line ## __
#define _TRACER_NAME_(line) __TRACER_NAME__(line)
#define TRACER_NAME _TRACER_NAME_(__LINE__)
#define TRACE \
	; \
	DLOG_TYPE(Severity::VERBOSE) TRACER_NAME(__LINE__, __PRETTY_FUNCTION__, Severity::VERBOSE); \
	TRACER_NAME << ">>>>>> FUNCTION STARTED;" << DFlush; \
	TRACER_NAME << ">>>>>> FUNCTION EXITED;";

#define DLOG_ONCE(__skip_times__, __message__, severity) \
	{ \
		static unsigned int __inner_counter__ = __skip_times__;\
		--__inner_counter__; \
		if(__inner_counter__ <= 0) \
		{ \
			__inner_counter__ = __skip_times__; \
			DLOG_STREAM_TYPE(severity) << __message__; \
		} \
	}

#include "DLogCore/Assert.h"

#else

#include "DLogCore/cDLog.h"

#endif
