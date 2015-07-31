#include "StdAfx.h"
#include "cgPlatform.h"
#ifdef WIN32
#include "cgWindowsPlatform.h"
#endif

cgPlatform * cgPlatform::ms_pkPlatform = NULL;

cgPlatform::cgPlatform(void)
{
}


cgPlatform::~cgPlatform(void)
{
}

cgPlatform * cgPlatform::Instance()
{
	if (!ms_pkPlatform )
	{
#ifdef WIN32
		ms_pkPlatform = new cgWindowsPlatform;
#else
		ms_pkPlatform = new cgXXXPlatform;
#endif
	}

	return ms_pkPlatform;
}

void cgPlatform::Destory()
{
	if (ms_pkPlatform)
	{
		delete ms_pkPlatform;
		ms_pkPlatform = NULL;
	}
}
