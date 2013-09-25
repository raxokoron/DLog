#pragma once

// TODO:
// 1) Add names for pointers
// 2) Validation

// Disable log with this macro. Works on seperate files;
//#define DLOG_DISABLED

#ifdef __cplusplus
#include <cstdarg>
#include <sstream>

enum class Severity
{
	VERBOSE = 0,
	WARNING,
	ERROR,
	FATAL,
	ASSERT // Always logged
};

#ifdef DLOG_DISABLED
	#ifdef SEVERITY_FILTER
		#undef SEVERITY_FILTER
	#endif
	#define SEVERITY_FILTER Severity::ASSERT
#endif

#ifndef SEVERITY_FILTER
#define SEVERITY_FILTER Severity::VERBOSE
#endif

#include "DLogCore/CommonOutput.h"
#include "DLogCore/STLOutput.h"
#include "DLogCore/TizenOutput.h"
#include "DLogCore/AndroidOutput.h"

class DLogger
{
public:
	typedef void (* OutputFunction) (Severity severity, const char* functionName, unsigned int line, const char* msg);
public:
	DLogger(unsigned int line, const char* functionName, Severity severity);
	DLogger(const DLogger& other) = delete;
	const DLogger& operator=(const DLogger& other) = delete;
	~DLogger(){ flush(); }
public:
	void setOutputFunction(OutputFunction func) { output_ = func; }
	void flush();
public:
	DLogger& print(const char* format, ...);
	DLogger& print(const char* format, va_list args);
	template<typename T>
	inline DLogger& print(const T& t)
	{
		stream_ << t;
		return *this;
	}
	template<typename T>
	DLogger& operator<<(T t)
	{
		return ::operator<<(*this, t);
	}
public:
	static void setDefaultOutputFunction(OutputFunction func);
	static OutputFunction getOutputFunction();
private:
	static OutputFunction defaultOutputFunction_;
private:
	OutputFunction output_;
	unsigned int line_;
	const char* functionName_;
	Severity severity_;
private:
	mutable std::stringstream stream_;
};

// System stuff starts
//template<Severity filter, Severity severity, bool val = (filter <= severity)>
//struct DLOG_GETTER
//{
//	typedef DLoggerProxy value_type;
//};
//template<Severity filter, Severity severity>
//struct DLOG_GETTER<filter, severity, false>
//{
//	typedef DLoggerNull value_type;
//};

#define DLOG_STREAM_TYPE(__severity__) DLogger(__LINE__, __PRETTY_FUNCTION__, __severity__)
// System stuff ends

#define DLOG  DLOG_STREAM_TYPE(Severity::VERBOSE)
#define DLOGW DLOG_STREAM_TYPE(Severity::WARNING)
#define DLOGE DLOG_STREAM_TYPE(Severity::ERROR)
#define DLOGF DLOG_STREAM_TYPE(Severity::FATAL)
#define DLOGA DLOG_STREAM_TYPE(Severity::ASSERT)

#define NAMED(__var__) ' ' << #__var__ ": " << (__var__) << ' '
#define QUOTE(__var__) '\'' << (__var__) << '\''
#define DQUOTE(__var__) "\"" << (__var__) << "\""

#define __TRACER_NAME__(line) __TRACER_ ## line ## __
#define _TRACER_NAME_(line) __TRACER_NAME__(line)
#define TRACER_NAME _TRACER_NAME_(__LINE__)
#define TRACE \
	; \
	DLogger TRACER_NAME(__LINE__, __PRETTY_FUNCTION__, Severity::VERBOSE); \
	TRACER_NAME << ">>>>>> FUNCTION STARTED;"; \
	TRACER_NAME.flush(); \
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
