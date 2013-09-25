#include "../DLog.h"

#include <vector>

void EmptyOutputFunction(Severity severity, const char* functionName, unsigned int line, const char* msg)
{}

DLogger::OutputFunction DLogger::defaultOutputFunction_ = EmptyOutputFunction;

DLogger::DLogger(unsigned int line, const char* functionName, Severity severity) :
	output_(defaultOutputFunction_),
	line_(line),
	functionName_(functionName),
	severity_(severity)
{
	stream_ << std::boolalpha << std::showbase;
}

void DLogger::flush()
{
	std::string str = stream_.str();
	if(str.size() == 0)
		str = '_';
	output_(severity_, functionName_, line_, str.c_str());
	stream_.str("");
}

DLogger& DLogger::print(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	print(format, args);
	va_end(args);
	return *this;
}
DLogger& DLogger::print(const char* format, va_list args)
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

void DLogger::setDefaultOutputFunction(OutputFunction func)
{
	if(defaultOutputFunction_ == EmptyOutputFunction)
	{
		defaultOutputFunction_ = func;
	}
}
DLogger::OutputFunction DLogger::getOutputFunction()
{
	return defaultOutputFunction_;
}

