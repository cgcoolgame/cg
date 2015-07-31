#include "StdAfx.h"
#include "cgAircraftWeapon.h"
#include "cgILSConfigManager.h"
#include "cgFlyObjectManager.h"
#include "cgBullet.h"
#include "cgAircraft.h"
#include "cgSoundManager.h"
#include <cgMove.h>



cgAircraftWeapon::cgAircraftWeapon( int nWeaponID, int nWeaponLvl )
{
	m_fCD = 0.0f;
	m_pkAircraft = NULL;
	m_nConfigID = nWeaponID;
	m_nLvl = nWeaponLvl;
	m_pkConfig = cgILSConfigManager::Get()->FindWeaponConfig(nWeaponID, nWeaponLvl);

}


cgAircraftWeapon::~cgAircraftWeapon(void)
{
}

bool cgAircraftWeapon::CanLevelup()
{
	if (m_pkConfig)
		return m_nLvl < m_pkConfig->nMaxLvl;

	return false;
}

bool cgAircraftWeapon::Levelup()
{
	if (CanLevelup())
	{
		++m_nLvl;
		m_pkConfig = cgILSConfigManager::Get()->FindWeaponConfig(m_nConfigID, m_nLvl);

		return true;
	}

	return false;
}

bool cgAircraftWeapon::LevelDown()
{
	if (m_nLvl > 1)
	{
		--m_nLvl;
		m_pkConfig = cgILSConfigManager::Get()->FindWeaponConfig(m_nConfigID, m_nLvl);
	}
	
	return true;
}


bool cgAircraftWeapon::Fire()
{
	if (!m_pkConfig || !m_pkAircraft)
	return 0;

	for (int i = 0; i < m_pkConfig->nLauncherNum; ++i)
	{
		cgWeaponLauncher & kLauncher = m_pkConfig->kLauncherList[i];

		cgBulletPtr spNewBullet = cgBullet::CreateBullet(kLauncher.nBulletID);

		spNewBullet->SetLocalPosition(m_pkAircraft->GetWorldPosition().x+kLauncher.nXOff, 
			m_pkAircraft->GetWorldPosition().y+kLauncher.nYOff);

		cgVector v(kLauncher.nXDir, kLauncher.nYDir);
		v.Normalize();
		v *= spNewBullet->GetSpeed();
		spNewBullet->StartAction(new cgMove(v.x, v.y));
		spNewBullet->SetCamp(m_pkAircraft->GetCamp());
	//	spNewBullet->SetScale(0.5f, 0.5f);
		
		spNewBullet->SetLocalRotation(m_pkAircraft->GetWorldRotation()-atan(v.x/v.y));
		cgFlyObjectManager::Get()->AddBullet(spNewBullet);
	}

	//if (m_pkConfig->nFireSoundID > -1)
	//cgSoundManager::Get()->PlaySound(m_pkConfig->nFireSoundID);

	return true;
}

int cgAircraftWeapon::GetWeaponID()
{
	return m_nConfigID;
}

int cgAircraftWeapon::GetWeaponLvl()
{
	return m_nLvl;
}

void cgAircraftWeapon::Update( float fDeltaTime )
{
	if (!m_pkConfig)
		return ;

	m_fCD += fDeltaTime;
	if (m_fCD >= m_pkConfig->fFireCD)
	{
		m_fCD -= m_pkConfig->fFireCD;
		Fire();
	}
}

void cgAircraftWeapon::SetAircaft( cgAircraft* pkAircraft )
{
	m_pkAircraft = pkAircraft;
}

cgAircraftPtr cgAircraftWeapon::GetAircraft()
{
	return m_pkAircraft;
}
