#ifndef cgFlyObject_h__
#define cgFlyObject_h__
#include "cgILoveShootingDef.h"
#include "..\cgEngineCore\cgSpirit.h"

class cgFlyObject:
	public cgSpirit
{
public:
	cgFlyObject(void);
	~cgFlyObject(void);

	// 阵营相关
	void SetCamp(cgFlyObjectCamp enmCamp);
	cgFlyObjectCamp GetCamp();

	// 状态相关
	void Active();
	bool IsActive();

	void SetDead();
	bool IsDead();

	void SetInvalid();
	bool IsInvalid();

	cgFlyObjectState GetState();

protected:
	int m_nBoundWidth;				// 宽
	int m_nBoundHeight;				// 高

	cgVector m_kPos;				// 位置
	cgVector m_kDirection;			// 方向，归一化的
	int m_nSpeed;					// 速度值

	cgFlyObjectCamp m_enmCamp;		// 阵营
	cgFlyObjectState m_enmState;	// 状态
};

bool cgXFlyObjectCanAttack(cgFlyObjectCamp enmRed, cgFlyObjectCamp enmBlue);
#endif // cgFlyObject_h__
