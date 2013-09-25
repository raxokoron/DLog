#include "../DLog.h"

DLogger& operator<<(DLogger& d, bool item)
{
	return d.print(item);
}

DLogger& operator<<(DLogger& d, char item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, short item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, int item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, long item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, long long item)
{
	return d.print(item);
}

DLogger& operator<<(DLogger& d, unsigned char item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, unsigned short item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, unsigned int item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, unsigned long item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, unsigned long long item)
{
	return d.print(item);
}

DLogger& operator<<(DLogger& d, float item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, double item)
{
	return d.print(item);
}

DLogger& operator<<(DLogger& d, const char* item)
{
	return d.print(item);
}
DLogger& operator<<(DLogger& d, const void* item)
{
	if(item != NULL)
		return d.print(item);
	return d << "nullptr";
}
