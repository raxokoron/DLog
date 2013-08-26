#include "DLogImpl.h"

#include <vector>

DLoggerImpl::OutputFunction DLoggerImpl::defaultOutputFunction_ = NULL;

DLoggerImpl::DLoggerImpl(unsigned int line, const char* functionName, Severity severity) :
	output_(defaultOutputFunction_),
	line_(line),
	functionName_(functionName),
	severity_(severity)
{
	stream_ << std::boolalpha << std::showbase;
}

void DLoggerImpl::flush()
{
	std::string str = stream_.str();
	if(str.size() == 0)
		str = '_';
	output_(severity_, functionName_, line_, str.c_str());
	stream_.str("");
}

DLoggerImpl& DLoggerImpl::print(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	print(format, args);
	va_end(args);
	return *this;
}
DLoggerImpl& DLoggerImpl::print(const char* format, va_list args)
{
	static unsigned int DEFAULT_BUFFER_SIZE = 512;
	std::vector<char> buffer;
	unsigned int size = DEFAULT_BUFFER_SIZE - 1; // without '\0' char
	while(size >= buffer.size())
	{
		buffer.resize(size+1);
		size = vsnprintf(buffer.data(), buffer.size(), format, args);
	}

	stream_ << static_cast<const char*>(buffer.data());

	return *this;
}

void DLoggerImpl::setDefaultOutputFunction(OutputFunction func)
{
	if( (defaultOutputFunction_ == NULL) || (defaultOutputFunction_ == OutputSTL) )
	{
		defaultOutputFunction_ = func;
	}
}
DLoggerImpl::OutputFunction DLoggerImpl::getOutputFunction()
{
	return defaultOutputFunction_;
}

DLoggerImpl& operator<<(DLoggerImpl& d, bool item)
{
	return d.print(item);
}

DLoggerImpl& operator<<(DLoggerImpl& d, char item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, short item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, int item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, long item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, long long item)
{
	return d.print(item);
}

DLoggerImpl& operator<<(DLoggerImpl& d, unsigned char item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned short item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned int item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned long item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, unsigned long long item)
{
	return d.print(item);
}

DLoggerImpl& operator<<(DLoggerImpl& d, float item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, double item)
{
	return d.print(item);
}

DLoggerImpl& operator<<(DLoggerImpl& d, const char* item)
{
	return d.print(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, const void* item)
{
	if(item != NULL)
		return d.print(item);
	return d << "NULL";
}

DLoggerImpl& operator<<(DLoggerImpl& d, const DLogFlush& item)
{
	d.flush();
	return d;
}
