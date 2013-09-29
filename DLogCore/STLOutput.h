#pragma once

#ifndef NO_STL

#include <string>

class DLogger;
DLogger& operator<<(DLogger& d, const std::string& item);

#ifdef STL_OUTPUT
// USE THIS MACRO TO ENABLE STL OUTPUT
#endif

#endif // NO_STL
