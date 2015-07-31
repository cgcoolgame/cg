// 飞行器管理器

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

	// 添加飞行器
	void AddAircraft(cgAircraftPtr spAircraft);
	size_t GetAircraftCount();
	//添加子弹
	void AddBullet(cgBulletPtr spBullet);
	size_t GetBulletCount();

	// 添加箱子
	void AddFlyBox(cgFlyBoxPtr spBox);
	size_t GetFlyBoxCount();

	// 主动清理所有
	void ClearAll();
private:

	// 检查位置
	void CheckPosition();

	void CheckBulletPosition();
	void CheckAircraftPosition();
	void CheckFlyBoxPosision();

	// 碰撞检测
	void CheckCollision();

	// 子弹碰撞
	bool TryBulletHitAircrafts(cgBulletPtr spBullet);
	void DoBulletHitAircraft(cgBulletPtr spBullet, cgAircraftPtr spAircraft);

	// 飞行器碰撞
	bool TryAircraftHitAircrafts(cgAircraftPtr spAttacker);
	void DoAircraftHitAircraft(cgAircraftPtr spAttacker, cgAircraftPtr spAttackee);

	// 飞行器撞击箱子
	bool TryFlyBoxAffectAircrafts(cgFlyBoxPtr spBox);
	void DoFlyBoxAffectAircraft(cgFlyBoxPtr spBox, cgAircraftPtr spCraft);

	// 清理无效物体
	void CleanupInvalidObjects();

private:
	cgAircraftList m_kAircraftList;
	cgBulletList m_kBulletList;
	cgFlyBoxList m_kFlyBoxList;
};

bool cgXFlyObjectCanAttack( cgFlyObjectCamp enmRed, cgFlyObjectCamp enmBlue );


#endif // cgAircraftManager_h__
