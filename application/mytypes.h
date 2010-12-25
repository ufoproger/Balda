#pragma once

#include <glibmm.h>

struct SMyGUniChar
{
	gunichar ch;
	bool f;
	int x;
	int y;
	
	SMyGUniChar () {}
	SMyGUniChar (gunichar _ch, int _x, int _y, bool _f): ch(_ch), x(_x), y(_y), f(_f) {}
};
