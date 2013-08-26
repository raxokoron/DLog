#include "../DLog.h"

#ifdef TIZEN
#include <FBase.h>
#include <FGraphics.h>

static void OutputTizen(Severity severity, const char* functionName, unsigned int line, const char* msg)
{
	switch(severity)
	{
	case Severity::VERBOSE:
		AppLogInternal(functionName, line, msg);
		break;
	case Severity::WARNING:
		AppLogDebugInternal(functionName, line, msg);
		break;
	case Severity::ERROR:
		AppLogExceptionInternal(functionName, line, msg);
		break;
	case Severity::FATAL:
		AppLogExceptionInternal(functionName, line, msg);
		break;
	case Severity::ASSERT:
		AppLogInternal(functionName, line, msg);
		AppLogDebugInternal(functionName, line, msg);
		AppLogExceptionInternal(functionName, line, msg);
		break;
	};
}

class TizenInitializer
{
public:
	TizenInitializer()
	{
		DLoggerImpl::setDefaultOutputFunction(OutputTizen);
	}
};

static TizenInitializer init;

DLoggerImpl& operator<<(DLoggerImpl& d, wchar_t item)
{
	return d << Tizen::Base::String(item);
}
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Base::String& item)
{
	return d.print("%S", item.GetPointer());
}
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Rectangle& item)
{
	return d.print("(x = %d, y = %d, width = %d, height = %d)", item.x, item.y, item.width, item.height);
}
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Point& item)
{
	return d.print("(x = %d, y = %d)", item.x, item.y);
}
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Dimension& item)
{
	return d.print("(width = %d, height = %d)", item.width, item.height);
}
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Color& item)
{
	return d.print("(r = %d, g = %d, b = %d, a = %d)", item.GetRed(), item.GetGreen(), item.GetBlue(), item.GetAlpha());
}
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Base::DateTime& item)
{
	return d << item.ToString();
}

#endif
