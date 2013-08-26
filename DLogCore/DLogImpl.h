#pragma once

#include <cstdarg>
#include <sstream>
#include <deque>
#include "Manipulators.h"

enum class Severity
{
	VERBOSE = 0,
	WARNING,
	ERROR,
	FATAL,
	ASSERT // Always logged
};

class DLoggerImpl
{
public:
	typedef void (* OutputFunction) (Severity severity, const char* functionName, unsigned int line, const char* msg);
public:
	DLoggerImpl(unsigned int line, const char* functionName, Severity severity);
	DLoggerImpl(const DLoggerImpl& other) = delete;
	const DLoggerImpl& operator=(const DLoggerImpl& other) = delete;
	~DLoggerImpl(){ flush(); }
public:
	void setOutputFunction(OutputFunction func) { output_ = func; }
	void flush();
public:
	DLoggerImpl& print(const char* format, ...);
	DLoggerImpl& print(const char* format, va_list args);
	template<typename T>
	inline DLoggerImpl& print(const T& t)
	{
		stream_ << t;
		return *this;
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
	std::stringstream stream_;
};

DLoggerImpl& operator<<(DLoggerImpl& d, bool item);

DLoggerImpl& operator<<(DLoggerImpl& d, char item);
DLoggerImpl& operator<<(DLoggerImpl& d, short item);
DLoggerImpl& operator<<(DLoggerImpl& d, int item);
DLoggerImpl& operator<<(DLoggerImpl& d, long item);
DLoggerImpl& operator<<(DLoggerImpl& d, long long item);

DLoggerImpl& operator<<(DLoggerImpl& d, unsigned char item);
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned short item);
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned int item);
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned long item);
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned long long item);

DLoggerImpl& operator<<(DLoggerImpl& d, float item);
DLoggerImpl& operator<<(DLoggerImpl& d, double item);

DLoggerImpl& operator<<(DLoggerImpl& d, const char* item);
DLoggerImpl& operator<<(DLoggerImpl& d, const void* item);

DLoggerImpl& operator<<(DLoggerImpl& d, const DLogFlush& item);

#include "STLFunc.h"
#include "TizenFunc.h"
#include "AndroidFunc.h"

