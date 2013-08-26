#pragma once

#ifdef TIZEN
#include <FBaseDataType.h>

namespace Tizen {
	namespace Graphics {
		class Bitmap;
		class Canvas;
		class EnrichedText;
		class Color;
		class Rectangle;
		class Dimension;
		class Point;
		class DateTime;
	}

	namespace Base {
		class ByteBuffer;
		class String;
		class DateTime;
	}
}

DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Base::String& item);
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Rectangle& item);
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Point& item);
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Dimension& item);
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Graphics::Color& item);
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Base::DateTime& item);
DLoggerImpl& operator<<(DLoggerImpl& d, const Tizen::Base::ByteBuffer& item);

#endif


