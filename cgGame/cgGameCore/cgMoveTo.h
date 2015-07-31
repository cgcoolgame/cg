
#ifndef cgMoveTo_h__
#define cgMoveTo_h__

#include "cgMoveBy.h"
class cgMoveTo :
	public cgMoveBy
{
public:
	cgMoveTo();
	cgMoveTo(const cgVector& dest, float moveTime);
	cgMoveTo(float xDest, float yDest, float moveTime);

protected:
	virtual void DoStart();

protected:
	cgVector m_kDest;
};

#endif // cgMoveTo_h__
