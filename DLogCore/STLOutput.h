#pragma once

#include <string>

class DLogger;

DLogger& operator<<(DLogger& d, const std::string& item);


