

#ifndef cgMoveBy_h__
#define cgMoveBy_h__
#include "cgAction.h"

class cgMoveBy :
	public cgAction
{
public:
	cgMoveBy();
	cgMoveBy(float xMove, float yMove, float moveTime);
	cgMoveBy(const cgVector& moveBy, float moveTime);

	static cgMoveBy * FromSpeed(float xMove, float yMove, float moveSpeed);
	static cgMoveBy * FromSpeed(const cgVector& moveBy, float moveSpeed);

protected:
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgVector m_kMoveBy;
	cgVector m_kLeftMoveBy;
	cgVector m_kSpeed;
	float m_fMoveTime;
};

#endif // cgMoveBy_h__
