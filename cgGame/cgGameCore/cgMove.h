
#ifndef cgMove_h__
#define cgMove_h__

#include "cgaction.h"

// 最基本的移动，就是给你一个速度，你就一直移动去吧
class cgMove :
	public cgAction
{
public:
	cgMove();
	cgMove(const cgVector& speed);
	cgMove(float xSpeed, float ySpeed);

	// 设置速度，可以动态改变它
	const cgVector& SetSpeed(const cgVector& speed);
	const cgVector& SetSpeed(float xSpeed, float ySpeed);
	const cgVector& GetSpeed()const;

protected:
	// 更新
	virtual void DoUpdate(float fDeltaTime);

protected:
	cgVector m_kSpeed;
};

typedef cgSmartPointer<cgMove> cgMovePtr;
#endif // cgMove_h__
