#ifndef cgAlphaBy_h__
#define cgAlphaBy_h__

#include "cgaction.h"

class cgAlphaBy :
	public cgAction
{
public:
	cgAlphaBy(void);
	cgAlphaBy(float alphaBy, float alphaTime);

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	float m_fAlphaBy;
	float m_fLeftAlphaBy;
	float m_fAlphaTime;
	float m_fAlphaSpeed;
};

#endif // cgAlphaBy_h__
