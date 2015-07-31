#ifndef cgAlphaTo_h__
#define cgAlphaTo_h__


#include "cgalphaby.h"
class cgAlphaTo :
	public cgAlphaBy
{
public:
	cgAlphaTo(void);
	cgAlphaTo(float alphaTo, float alphaTime);

protected:
	virtual void DoStart();

protected:
	float m_fAlphaTo;
};

#endif // cgAlphaTo_h__
