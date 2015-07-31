
#ifndef cgScaleTo_h__
#define cgScaleTo_h__

#include "cgAction.h"
class cgScaleTo :
	public cgAction
{
public:
	cgScaleTo(void);
	cgScaleTo(const cgVector & destScale, float scaleTime);
	cgScaleTo(float destScaleX, float destScaleY, float scaleTime);
	
protected:
	virtual void DoStart();
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgVector m_kDestScale;
	cgVector m_kScaleSpeed;
	float m_fScaleTime;
};

#endif // cgScaleTo_h__
