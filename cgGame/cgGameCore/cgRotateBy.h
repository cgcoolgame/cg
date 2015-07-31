#ifndef cgRotateBy_h__
#define cgRotateBy_h__

#include "cgaction.h"

// 旋转多少度
class cgRotateBy :
	public cgAction
{
public:
	cgRotateBy(void);
	cgRotateBy(float rotateBy, float rotateTime);

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	float m_fRotateBy;
	float m_fLeftRotateBy;
	float m_fRotateTime;
	float m_fRotateSpeed;
};

#endif // cgRotateBy_h__
