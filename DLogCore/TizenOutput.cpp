#include "../DLog.h"
#include "DLogInitializer.h"

#ifdef TIZEN
#include <FBase.h>
#include <FGraphics.h>

static void TizenOutputFunction(Severity severity, const char* functionName, unsigned int line, const char* msg)
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

static DLogInitializer init(TizenOutputFunction);

DLogger& operator<<(DLogger& d, wchar_t item)
{
	return d << Tizen::Base::String(item);
}
DLogger& operator<<(DLogger& d, const Tizen::Base::String& item)
{
	return d.print("%S", item.GetPointer());
}
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Rectangle& item)
{
	return d.print("(x = %d, y = %d, width = %d, height = %d)", item.x, item.y, item.width, item.height);
}
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Point& item)
{
	return d.print("(x = %d, y = %d)", item.x, item.y);
}
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Dimension& item)
{
	return d.print("(width = %d, height = %d)", item.width, item.height);
}
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Color& item)
{
	return d.print("(r = %d, g = %d, b = %d, a = %d)", item.GetRed(), item.GetGreen(), item.GetBlue(), item.GetAlpha());
}
DLogger& operator<<(DLogger& d, const Tizen::Base::DateTime& item)
{
	return d << item.ToString();
}
DLogger& operator<<(DLogger& d, const Tizen::Base::ByteBuffer& item)
{
	Tizen::Base::String tmp;
	result r = Tizen::Base::Utility::StringUtil::Utf8ToString((const char*)item.GetPointer(), tmp);
	if(r != E_SUCCESS)
	{
		d.print("FAILED TO CONVERT BYTEBUFFER: %p", &item);
	}
	else
	{
		d << tmp;
	}
	return d;
}

#endif
