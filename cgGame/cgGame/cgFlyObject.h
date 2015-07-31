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

	// ��Ӫ���
	void SetCamp(cgFlyObjectCamp enmCamp);
	cgFlyObjectCamp GetCamp();

	// ״̬���
	void Active();
	bool IsActive();

	void SetDead();
	bool IsDead();

	void SetInvalid();
	bool IsInvalid();

	cgFlyObjectState GetState();

protected:
	int m_nBoundWidth;				// ��
	int m_nBoundHeight;				// ��

	cgVector m_kPos;				// λ��
	cgVector m_kDirection;			// ���򣬹�һ����
	int m_nSpeed;					// �ٶ�ֵ

	cgFlyObjectCamp m_enmCamp;		// ��Ӫ
	cgFlyObjectState m_enmState;	// ״̬
};

bool cgXFlyObjectCanAttack(cgFlyObjectCamp enmRed, cgFlyObjectCamp enmBlue);
#endif // cgFlyObject_h__
