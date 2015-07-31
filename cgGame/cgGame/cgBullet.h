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

	// 配置
	void SetConfig(cgBulletConfig * pkConfig);
	cgBulletConfig * GetConfig();

	void SetModel(const cgString & strPath);

	void SetInvalid(bool bInvalid);
	bool IsInvalid();

	// 阵营
	void SetCamp(cgFlyObjectCamp enmCamp);
	cgFlyObjectCamp GetCamp();

	static cgBulletPtr CreateBullet(int nConfigID);

private:
	cgBullet();

private:

	int m_nAttack;
	int m_nSpeed;
	// 表现信息
	cgBulletConfig * m_pkConfig;
	
	cgGameSpiritPtr m_spImage;
	cgFlyObjectCamp	m_enmCamp;

	bool m_bInvalid; // 是否无效了

};

#endif // cgBullet_h__
