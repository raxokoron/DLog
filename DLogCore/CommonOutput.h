#pragma once

class DLogger;

DLogger& operator<<(DLogger& d, bool item);

DLogger& operator<<(DLogger& d, char item);
DLogger& operator<<(DLogger& d, short item);
DLogger& operator<<(DLogger& d, int item);
DLogger& operator<<(DLogger& d, long item);
DLogger& operator<<(DLogger& d, long long item);

DLogger& operator<<(DLogger& d, unsigned char item);
DLogger& operator<<(DLogger& d, unsigned short item);
DLogger& operator<<(DLogger& d, unsigned int item);
DLogger& operator<<(DLogger& d, unsigned long item);
DLogger& operator<<(DLogger& d, unsigned long long item);

DLogger& operator<<(DLogger& d, float item);
DLogger& operator<<(DLogger& d, double item);

DLogger& operator<<(DLogger& d, const char* item);
DLogger& operator<<(DLogger& d, const void* item);

