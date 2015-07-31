
#ifndef cgRotateAround_h__
#define cgRotateAround_h__

#include "cgaction.h"

class cgRotateAround :
	public cgAction
{
public:
	cgRotateAround(void);
	cgRotateAround(float rotateSpeed, const cgVector& rotateCenter);
	cgRotateAround(float rotateSpeed, float centerX, float centerY);

	void SetRotateSpeed(float rotateSpeed);
	float GetRotateSpeed();

	void SetRotateCenter(const cgVector& rotateCenter);
	const cgVector & GetRotateCenter();

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	float m_fRotateSpeed;
	cgVector m_kRotateCenter;
};

#endif // cgRotateAround_h__
