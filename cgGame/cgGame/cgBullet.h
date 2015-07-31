#ifndef cgBullet_h__
#define cgBullet_h__

#include "cgILoveShootingDef.h"
#include <cgGameObject.h>
#include <cgGameSprite.h>

class cgBullet :
	public cgGameObject
{
public:
	~cgBullet(void);
	
	void SetAttack(int nAttack);
	int GetAttack();

	void SetSpeed(int nSpeed);
	int GetSpeed();

	// ����
	void SetConfig(cgBulletConfig * pkConfig);
	cgBulletConfig * GetConfig();

	void SetModel(const cgString & strPath);

	void SetInvalid(bool bInvalid);
	bool IsInvalid();

	// ��Ӫ
	void SetCamp(cgFlyObjectCamp enmCamp);
	cgFlyObjectCamp GetCamp();

	static cgBulletPtr CreateBullet(int nConfigID);

private:
	cgBullet();

private:

	int m_nAttack;
	int m_nSpeed;
	// ������Ϣ
	cgBulletConfig * m_pkConfig;
	
	cgGameSpiritPtr m_spImage;
	cgFlyObjectCamp	m_enmCamp;

	bool m_bInvalid; // �Ƿ���Ч��

};

#endif // cgBullet_h__
