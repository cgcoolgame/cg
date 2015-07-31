#include "StdAfx.h"
#include "cgTime.h"

static LARGE_INTEGER freq;
static LARGE_INTEGER beginCount;
static LARGE_INTEGER curCount;

bool cgTime::Initialize()
{
	return 	QueryPerformanceFrequency(&freq) && QueryPerformanceCounter(&beginCount);
}

float cgTime::GetTime()
{
	QueryPerformanceCounter(&curCount);

	return (float)( ((long double)(curCount.QuadPart-beginCount.QuadPart))
		/(long double)freq.QuadPart);
}
