#ifndef cgWait_h__
#define cgWait_h__


#include "cgaction.h"
class cgWait :
	public cgAction
{
public:
	cgWait(void);
	cgWait(float waitTime);

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	float m_fWaitTime;
};

#endif // cgWait_h__
