#pragma once
#include "cgaction.h"
class cgDestroy :
	public cgAction
{
public:
	cgDestroy(void);

protected:
	virtual void DoStart();
};

