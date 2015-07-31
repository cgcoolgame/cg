#include "StdAfx.h"
#include "cgILSConfigManager.h"
#include "cgTxtDataReader.h"


cgILSConfigManager::cgILSConfigManager(void)
{
}


cgILSConfigManager::~cgILSConfigManager(void)
{
	FreeAllConfigs();
}


bool cgILSConfigManager::Initialize()
{
	LoadAllConfigs();
	return true;
}

void cgILSConfigManager::LoadAllConfigs()
{
	LoadBulletConfigs();
	LoadWeaponConfigs();
	LoadAircraftConfigs();
	LoadBattleConfigs();
	LoadFlyBoxConfigs();
}

void cgILSConfigManager::FreeAllConfigs()
{
	FreeFlyBoxConfigs();
	FreeBattleConfigs();
	FreeAircraftConfigs();
	FreeWeaponConfigs();
	FreeBulletConfigs();
}

// ------------------------------------------------------

void cgILSConfigManager::LoadBulletConfigs()
{
	cgTxtDataReader kReader;

	if (!kReader.Open("./config/bullet.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgBulletConfig * pkConfig = new cgBulletConfig;
		int nIndex = 0;
		pkConfig->nID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nAttack = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nSpeed = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nHitSoundID = atoi(pkRecord->GetField(nIndex++));

		pkConfig->nBoundW = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nBoundH = atoi(pkRecord->GetField(nIndex++));

		pkConfig->strName = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strModel = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strDesc = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->nAreaFlag = atoi(pkRecord->GetField(nIndex++));

		m_kBulletConfigList.push_back(pkConfig);
	}

}

void cgILSConfigManager::FreeBulletConfigs()
{
	cgBulletConfigList::iterator it = m_kBulletConfigList.begin();
	for (;it != m_kBulletConfigList.end(); ++it)
	{
		delete *it;
	}
	m_kBulletConfigList.clear();
}

size_t cgILSConfigManager::GetBulletConfigNum()
{
	return m_kBulletConfigList.size();
}

cgBulletConfig * cgILSConfigManager::GetBulletConfigByIndex( size_t index )
{
	if (index < m_kBulletConfigList.size())
		return m_kBulletConfigList[index];

	return NULL;
}

cgBulletConfig * cgILSConfigManager::FindBulletConfigByID( int nID )
{
	cgBulletConfigList::iterator it = m_kBulletConfigList.begin();
	for (;it != m_kBulletConfigList.end(); ++it)
	{
		cgBulletConfig * pkConfig = *it;
		if (pkConfig && pkConfig->nID == nID)
			return pkConfig;
	}

	return NULL;
}

// ------------------------------------------------------
void cgILSConfigManager::LoadWeaponConfigs()
{
	cgTxtDataReader kReader;

	if (!kReader.Open("./config/weapon.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgWeaponConfig * pkConfig = new cgWeaponConfig;
		pkConfig->nLauncherNum = 0;

		int nIndex = 0;
		pkConfig->nID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nLvl = atoi(pkRecord->GetField(nIndex++));
		pkConfig->fFireCD = atoi(pkRecord->GetField(nIndex++))/1000.0f;
		pkConfig->nMaxLvl = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nFireSoundID = atoi(pkRecord->GetField(nIndex++));

		// 加载发射器信息
		for (int i = 0; i < MAX_AIRCRAFT_WEAPON_LUANCER_NUM; ++i)
		{
			cgWeaponLauncher& kLauncher = pkConfig->kLauncherList[pkConfig->nLauncherNum];
			kLauncher.nBulletID = atoi(pkRecord->GetField(nIndex++));
			kLauncher.nXOff = atoi(pkRecord->GetField(nIndex++));
			kLauncher.nYOff = atoi(pkRecord->GetField(nIndex++));
			kLauncher.nXDir = atoi(pkRecord->GetField(nIndex++));
			kLauncher.nYDir = atoi(pkRecord->GetField(nIndex++));

			// 子弹id大于0才有效
			if (kLauncher.nBulletID > 0)
				++pkConfig->nLauncherNum;
		}

		pkConfig->strName = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strModel = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strDesc = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));

		m_kWeaponConfigList.push_back(pkConfig);
	}
}

void cgILSConfigManager::FreeWeaponConfigs()
{
	cgWeaponConfigList::iterator it = m_kWeaponConfigList.begin();
	for (;it != m_kWeaponConfigList.end(); ++it)
	{
		delete *it;
	}
	m_kWeaponConfigList.clear();
}

size_t cgILSConfigManager::GetWeaponConfigNum()
{
	return m_kWeaponConfigList.size();
}

cgWeaponConfig * cgILSConfigManager::GetWeaponConfigByIndex( size_t index )
{
	if (index < m_kWeaponConfigList.size())
		return m_kWeaponConfigList[index];

	return NULL;
}

cgWeaponConfig * cgILSConfigManager::FindWeaponConfig( int nID, int nLvl )
{
	cgWeaponConfigList::iterator it = m_kWeaponConfigList.begin();
	for (; it != m_kWeaponConfigList.end(); ++it)
	{
		cgWeaponConfig * pkConfig = *it;
		if (pkConfig && pkConfig->nID == nID && pkConfig->nLvl == nLvl)
			return pkConfig;
	}

	return NULL;
}


// ------------------------------------------------------

void cgILSConfigManager::LoadAircraftConfigs()
{

	cgTxtDataReader kReader;

	if (!kReader.Open("./config/aircraft.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgAircraftConfig * pkConfig = new cgAircraftConfig;
		int nIndex = 0;
		pkConfig->nID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nBasicSpeed = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nBoundWidth = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nBoundHeight = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nBasicMaxHp = atoi(pkRecord->GetField(nIndex++));

		pkConfig->nMainWeaponID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nMainWeaponLvl = atoi(pkRecord->GetField(nIndex++));

		pkConfig->strName = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strModel = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strDesc = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));

		m_kAircraftConfigList.push_back(pkConfig);
	}
}

void cgILSConfigManager::FreeAircraftConfigs()
{
	cgAircraftConfigList::iterator it = m_kAircraftConfigList.begin();
	for (; it != m_kAircraftConfigList.end(); ++it)
	{
		delete *it;
	}
	m_kAircraftConfigList.clear();
}

size_t cgILSConfigManager::GetAircraftConfigNum()
{
	return m_kAircraftConfigList.size();
}

cgAircraftConfig * cgILSConfigManager::GetAircraftConfigByIndex( size_t index )
{
	if (index < m_kAircraftConfigList.size())
		return m_kAircraftConfigList[index];

	return NULL;
}

cgAircraftConfig * cgILSConfigManager::FindAircraftConfigByID( int nID )
{
	cgAircraftConfigList::iterator it = m_kAircraftConfigList.begin();
	for (; it != m_kAircraftConfigList.end(); ++it)
	{
		cgAircraftConfig * pkConfig = *it;
		if (pkConfig && pkConfig->nID == nID)
			return pkConfig;
	}

	return NULL;
}

// ------------------------------------------------------

void cgILSConfigManager::LoadBattleConfigs()
{
	cgTxtDataReader kReader;

	if (!kReader.Open("./config/battles.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgBattleConfig * pkConfig = new cgBattleConfig;
		int nIndex = 0;
		pkConfig->nID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nNextBattle = atoi(pkRecord->GetField(nIndex++));

		pkConfig->strName = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strBkImage = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strDesc = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));
		pkConfig->strCraftConfig = pkRecord->GetField(nIndex++);
		pkConfig->nBossID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nScrollSpeed = atoi(pkRecord->GetField(nIndex++));

		m_kBattleConfigList.push_back(pkConfig);
	}
}

void cgILSConfigManager::FreeBattleConfigs()
{
	cgBattleConfigList::iterator it = m_kBattleConfigList.begin();
	for (; it != m_kBattleConfigList.end(); ++it)
	{
		delete *it;
	}
	m_kBattleConfigList.clear();
}

size_t cgILSConfigManager::GetBattleConfigNum()
{
	return m_kBattleConfigList.size();
}

cgBattleConfig * cgILSConfigManager::GetBattleConfigByIndex( size_t index )
{
	if (index < m_kBattleConfigList.size())
		return m_kBattleConfigList[index];

	return NULL;
}

cgBattleConfig * cgILSConfigManager::FindBattleConfigByID( int nID )
{
	cgBattleConfigList::iterator it = m_kBattleConfigList.begin();
	for (; it != m_kBattleConfigList.end(); ++it)
	{
		cgBattleConfig * pkConfig = *it;
		if (pkConfig && pkConfig->nID == nID)
			return pkConfig;
	}

	return NULL;
}

// ------------------------------------------------------

void cgILSConfigManager::LoadFlyBoxConfigs()
{
	cgTxtDataReader kReader;

	if (!kReader.Open("./config/flybox.txt"))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgFlyBoxConfig * pkConfig = new cgFlyBoxConfig;
		int nIndex = 0;
		pkConfig->nID = atoi(pkRecord->GetField(nIndex++));
		pkConfig->enmType = static_cast<cgFlyBoxType>(atoi(pkRecord->GetField(nIndex++)));
		pkConfig->nParam1 = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nParam2 = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nParam3 = atoi(pkRecord->GetField(nIndex++));
		pkConfig->nParam4 = atoi(pkRecord->GetField(nIndex++));

		pkConfig->strModel = cgXConfigStr2CgTxt(pkRecord->GetField(nIndex++));

		m_kFlyBoxConfigList.push_back(pkConfig);
	}
}

void cgILSConfigManager::FreeFlyBoxConfigs()
{
	cgFlyBoxConfigList::iterator it = m_kFlyBoxConfigList.begin();
	for (; it != m_kFlyBoxConfigList.end(); ++it)
	{
		delete *it;
	}
	m_kFlyBoxConfigList.clear();
}

size_t cgILSConfigManager::GetFlyBoxConfigNum()
{
	return m_kFlyBoxConfigList.size();
}

cgFlyBoxConfig * cgILSConfigManager::GetFlyBoxConfigByIndex( size_t index )
{
	if (index < m_kFlyBoxConfigList.size())
		return m_kFlyBoxConfigList[index];

	return NULL;
}

cgFlyBoxConfig * cgILSConfigManager::FindFlyBoxConfigByID( int nID )
{
	cgFlyBoxConfigList::iterator it = m_kFlyBoxConfigList.begin();
	for (; it != m_kFlyBoxConfigList.end(); ++it)
	{
		cgFlyBoxConfig * pkConfig = *it;
		if (pkConfig && pkConfig->nID == nID)
			return pkConfig;
	}

	return NULL;
}
