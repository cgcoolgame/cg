
#ifndef cgVisible_h__
#define cgVisible_h__

#include "cgaction.h"
class cgVisible :
	public cgAction
{
public:
	cgVisible(void);
	cgVisible(bool visible);

protected:
	virtual void DoStart();

protected:
	bool m_bVisible;
};

#endif // cgVisible_h__
