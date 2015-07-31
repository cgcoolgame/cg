
#ifndef cgRotate_h__
#define cgRotate_h__

#include "cgaction.h"

// ³ÖÐøÐý×ª
class cgRotate :
	public cgAction
{
public:
	cgRotate(void);
	cgRotate(float rotateSpeed);

	void SetRotateSpeed(float speed);
	float GetRotateSpeed();

protected:
	virtual void DoUpdate(float fDeltaTime);
protected:
	float m_fRotateSpeed;
};

#endif // cgRotate_h__
