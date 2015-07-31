#ifndef cgUILoader_h__
#define cgUILoader_h__
#include "cgUIWidget.h"

struct cgUILoader
{
	virtual cgUIWidgetPtr LoadScreen(const char * pcScreen) = NULL;
	virtual cgUIWidgetPtr LoadDynamic(const char * pcID) = NULL;
};

#endif // cgUILoader_h__
