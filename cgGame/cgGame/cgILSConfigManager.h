#ifndef cgILSConfigManager_h__
#define cgILSConfigManager_h__
#include <vector>
#include "cgSingleton.h"
#include "cgILoveShootingDef.h"
/**
*	���ù�����
*	�������е�����
*	��ע�⡿һ������ö�����vector��ţ����ṩ˳����ʽӿ�
*	��ע�⡿������Ƚϴ󣬲�����Ҫ�������ң�������map��ţ�ȡ��˳����ʽӿ�
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

	// �������е�����
	void LoadAllConfigs();

	// �ͷ����е�����
	void FreeAllConfigs();
// ------------------------------------------------------
private:
	// �ӵ�����
	void LoadBulletConfigs();
	void FreeBulletConfigs();

	// ��������
	void LoadWeaponConfigs();
	void FreeWeaponConfigs();

	// ����������
	void LoadAircraftConfigs();
	void FreeAircraftConfigs();

	// ս���ؿ�����
	void LoadBattleConfigs();
	void FreeBattleConfigs();

// ս���ؿ�����
	void LoadFlyBoxConfigs();
	void FreeFlyBoxConfigs();
public:
	// �ӵ�����
	size_t GetBulletConfigNum();
	cgBulletConfig * GetBulletConfigByIndex(size_t index);
	cgBulletConfig * FindBulletConfigByID(int nID);

// ------------------------------------------------------

	// ��������

	size_t GetWeaponConfigNum();
	cgWeaponConfig * GetWeaponConfigByIndex(size_t index);
	cgWeaponConfig * FindWeaponConfig(int nID, int nLvl);

// ------------------------------------------------------
	
	// ����������

	size_t GetAircraftConfigNum();
	cgAircraftConfig * GetAircraftConfigByIndex(size_t index);
	cgAircraftConfig * FindAircraftConfigByID(int nID);

// ------------------------------------------------------
	// �ؿ�����
	size_t GetBattleConfigNum();
	cgBattleConfig * GetBattleConfigByIndex(size_t index);
	cgBattleConfig * FindBattleConfigByID(int nID);
// ------------------------------------------------------
	// ��������
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
