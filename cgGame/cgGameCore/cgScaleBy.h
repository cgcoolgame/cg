
#ifndef cgScaleBy_h__
#define cgScaleBy_h__

#include "cgaction.h"
class cgScaleBy :
	public cgAction
{
public:
	cgScaleBy(void);
	cgScaleBy(float scaleX, float scaleY, float scaleTime);
	cgScaleBy(const cgVector& scale, float scaleTime);

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgVector m_kScaleBy;
	cgVector m_kLeftScale;
	cgVector m_kScaleSpeed;
	float m_fScaleTime;
};

#endif // cgScaleBy_h__
