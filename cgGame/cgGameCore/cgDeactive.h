#ifndef cgDeactive_h__
#define cgDeactive_h__

#include "cgaction.h"
class cgDeactive :
	public cgAction
{
public:
	cgDeactive(void);

protected:
	virtual void DoStart();
};

#endif // cgDeactive_h__
