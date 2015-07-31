#include "StdAfx.h"
#include "cgBullet.h"
#include "cgILSConfigManager.h"
#include "cgILoveShootingGame.h"
#include "..\cgGameCore\cgSrcImageManager.h"


cgBullet::cgBullet(  )
{
	m_pkConfig = NULL;
	m_nAttack = 0;
	m_nSpeed = 0;
	m_bInvalid = false;
	m_enmCamp = cgFlyObjectCamp_None;
}


cgBullet::~cgBullet(void)
{
	DetachChild(&m_spImage);
}


void cgBullet::SetAttack( int nAttack )
{
	m_nAttack = nAttack;
}

int cgBullet::GetAttack()
{
	return m_nAttack;
}

void cgBullet::SetConfig( cgBulletConfig * pkConfig )
{
	m_pkConfig = pkConfig;
}

cgBulletConfig * cgBullet::GetConfig()
{
	return m_pkConfig;
}

void cgBullet::SetModel( const cgString & strPath )
{
	cgImagePtr spImage = cgSrcImageManager::Get()->LoadImage(strPath.c_str());
	if (spImage)
	{
		m_spImage = new cgGameSprite(spImage);
		AttachChild(&m_spImage);
	}
	
}

cgBulletPtr cgBullet::CreateBullet( int nConfigID )
{
	cgBulletConfig * pkConfig = cgILSConfigManager::Get()->FindBulletConfigByID(nConfigID);
	if (!pkConfig)
		return NULL;

	cgBulletPtr spBullet = new cgBullet();
	spBullet->SetConfig(pkConfig);
	spBullet->SetModel(pkConfig->strModel);
	spBullet->SetAttack(pkConfig->nAttack);
	spBullet->SetSpeed(pkConfig->nSpeed);
	spBullet->SetSize(pkConfig->nBoundW, pkConfig->nBoundH);
	return spBullet;
}

void cgBullet::SetInvalid( bool bInvalid )
{
	m_bInvalid = bInvalid;
}

bool cgBullet::IsInvalid()
{
	return m_bInvalid;
}

void cgBullet::SetCamp( cgFlyObjectCamp enmCamp )
{
	m_enmCamp = enmCamp;
}

cgFlyObjectCamp cgBullet::GetCamp()
{
	return m_enmCamp;
}

void cgBullet::SetSpeed( int nSpeed )
{
	m_nSpeed = nSpeed;
}

int cgBullet::GetSpeed()
{
	return m_nSpeed;
}

