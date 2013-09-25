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

class DLogger;

DLogger& operator<<(DLogger& d, const Tizen::Base::String& item);
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Rectangle& item);
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Point& item);
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Dimension& item);
DLogger& operator<<(DLogger& d, const Tizen::Graphics::Color& item);
DLogger& operator<<(DLogger& d, const Tizen::Base::DateTime& item);
DLogger& operator<<(DLogger& d, const Tizen::Base::ByteBuffer& item);

#endif


