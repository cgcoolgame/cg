#ifndef cgILSConfigManager_h__
#define cgILSConfigManager_h__
#include <vector>
#include "cgSingleton.h"
#include "cgILoveShootingDef.h"
/**
*	配置管理器
*	加载所有的配置
*	【注意】一般的配置都是用vector存放，并提供顺序访问接口
*	【注意】如果量比较大，并且需要经常查找，则是用map存放，取消顺序访问接口
**/

typedef std::vector<cgBulletConfig*> cgBulletConfigList;
typedef std::vector<cgWeaponConfig*> cgWeaponConfigList;
typedef std::vector<cgAircraftConfig*> cgAircraftConfigList;
typedef std::vector<cgBattleConfig*> cgBattleConfigList;
typedef std::vector<cgFlyBoxConfig*> cgFlyBoxConfigList;


class cgILSConfigManager:
	public cgSingleton<cgILSConfigManager>
{
public:
	cgILSConfigManager(void);
	~cgILSConfigManager(void);
	
	bool Initialize();
private:

	// 加载所有的配置
	void LoadAllConfigs();

	// 释放所有的配置
	void FreeAllConfigs();
// ------------------------------------------------------
private:
	// 子弹配置
	void LoadBulletConfigs();
	void FreeBulletConfigs();

	// 武器配置
	void LoadWeaponConfigs();
	void FreeWeaponConfigs();

	// 飞行器配置
	void LoadAircraftConfigs();
	void FreeAircraftConfigs();

	// 战斗关卡配置
	void LoadBattleConfigs();
	void FreeBattleConfigs();

// 战斗关卡配置
	void LoadFlyBoxConfigs();
	void FreeFlyBoxConfigs();
public:
	// 子弹配置
	size_t GetBulletConfigNum();
	cgBulletConfig * GetBulletConfigByIndex(size_t index);
	cgBulletConfig * FindBulletConfigByID(int nID);

// ------------------------------------------------------

	// 武器配置

	size_t GetWeaponConfigNum();
	cgWeaponConfig * GetWeaponConfigByIndex(size_t index);
	cgWeaponConfig * FindWeaponConfig(int nID, int nLvl);

// ------------------------------------------------------
	
	// 飞行器配置

	size_t GetAircraftConfigNum();
	cgAircraftConfig * GetAircraftConfigByIndex(size_t index);
	cgAircraftConfig * FindAircraftConfigByID(int nID);

// ------------------------------------------------------
	// 关卡配置
	size_t GetBattleConfigNum();
	cgBattleConfig * GetBattleConfigByIndex(size_t index);
	cgBattleConfig * FindBattleConfigByID(int nID);
// ------------------------------------------------------
	// 箱子配置
	size_t GetFlyBoxConfigNum();
	cgFlyBoxConfig * GetFlyBoxConfigByIndex(size_t index);
	cgFlyBoxConfig * FindFlyBoxConfigByID(int nID);

private:
	cgBulletConfigList m_kBulletConfigList;
	cgWeaponConfigList m_kWeaponConfigList;
	cgAircraftConfigList m_kAircraftConfigList;
	cgBattleConfigList m_kBattleConfigList;
	cgFlyBoxConfigList	m_kFlyBoxConfigList;
};

#endif // cgILSConfigManager_h__
