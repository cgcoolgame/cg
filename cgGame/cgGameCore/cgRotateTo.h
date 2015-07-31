#ifndef cgRotateTo_h__
#define cgRotateTo_h__

#include "cgrotateby.h"

class cgRotateTo :
	public cgRotateBy
{
public:
	cgRotateTo(void);
	cgRotateTo(float rotateTo, float rotateTime);

protected:
	virtual void DoStart();

protected:
	float m_fRotateTo;
};

#endif // cgRotateTo_h__
