// ������������

#ifndef cgFlyObjectManager_h__
#define cgFlyObjectManager_h__
#include "cgSingleton.h"
#include <list>
#include "cgAircraft.h"
#include "cgBullet.h"
#include "cgFlyBox.h"
typedef std::list<cgAircraftPtr> cgAircraftList;
typedef std::list<cgBulletPtr> cgBulletList;
typedef std::list<cgFlyBoxPtr> cgFlyBoxList;

class cgFlyObjectManager:
	public cgSingleton<cgFlyObjectManager>
{
public:
	cgFlyObjectManager(void);
	~cgFlyObjectManager(void);

	bool Initialize();
public:

	void Update(float fDeltaTime);

	// ��ӷ�����
	void AddAircraft(cgAircraftPtr spAircraft);
	size_t GetAircraftCount();
	//����ӵ�
	void AddBullet(cgBulletPtr spBullet);
	size_t GetBulletCount();

	// �������
	void AddFlyBox(cgFlyBoxPtr spBox);
	size_t GetFlyBoxCount();

	// ������������
	void ClearAll();
private:

	// ���λ��
	void CheckPosition();

	void CheckBulletPosition();
	void CheckAircraftPosition();
	void CheckFlyBoxPosision();

	// ��ײ���
	void CheckCollision();

	// �ӵ���ײ
	bool TryBulletHitAircrafts(cgBulletPtr spBullet);
	void DoBulletHitAircraft(cgBulletPtr spBullet, cgAircraftPtr spAircraft);

	// ��������ײ
	bool TryAircraftHitAircrafts(cgAircraftPtr spAttacker);
	void DoAircraftHitAircraft(cgAircraftPtr spAttacker, cgAircraftPtr spAttackee);

	// ������ײ������
	bool TryFlyBoxAffectAircrafts(cgFlyBoxPtr spBox);
	void DoFlyBoxAffectAircraft(cgFlyBoxPtr spBox, cgAircraftPtr spCraft);

	// ������Ч����
	void CleanupInvalidObjects();

private:
	cgAircraftList m_kAircraftList;
	cgBulletList m_kBulletList;
	cgFlyBoxList m_kFlyBoxList;
};

bool cgXFlyObjectCanAttack( cgFlyObjectCamp enmRed, cgFlyObjectCamp enmBlue );


#endif // cgAircraftManager_h__
