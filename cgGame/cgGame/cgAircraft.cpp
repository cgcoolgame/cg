#include "StdAfx.h"
#include "cgAircraft.h"
#include "cgILSConfigManager.h"
#include "cgRender.h"
#include "cgGameTools.h"
#include "cgAnimationUtility.h"
#include <cgSrcImageManager.h>
#include <cgSoundManager.h>
#include <cgMath.h>
#include <cgGameText.h>
#include <cgActionSequence.h>
#include <cgScaleTo.h>
#include <cgActionBundle.h>
#include <cgRotate.h>
#include <cgMoveBy.h>
#include <cgBlink.h>


cgAircraft::cgAircraft()
{
	m_nID = 0;
	m_nCurHp = 0;
	m_nMaxHp = 1;
	m_enmCamp = cgFlyObjectCamp_None;
	m_bInvalid = false;
	m_bAlive = true;
	m_pkConfig = NULL;
	m_enmState = cgAircraftState_Normal;
	m_fAliveTime = 0.0f;
	m_fDeadTime = 0.0f;

	m_spText = new cgGameText(TEXT(""), 2, 0xff008f00);
	m_spText->SetSize(200, 100);
	m_spText->Move(0.0f, -70.0f);
	AttachChild(&m_spText);
}


cgAircraft::~cgAircraft(void)
{
	DetachChild(&m_spActor);
}

void cgAircraft::UpdateCraft( float fDeltaTime )
{
	if (IsAlive())
	{
		m_fAliveTime += fDeltaTime;
		if (m_spMainWeapon)
			m_spMainWeapon->Update(fDeltaTime);
	}else
	{
		m_fDeadTime += fDeltaTime;
		if (m_fDeadTime > 0.5f)
		{
			SetInvalid(true);
		}
	}
}


void cgAircraft::SetID( int id )
{
	m_nID = id;
}


int cgAircraft::GetID()
{
	return m_nID;
}

int cgAircraft::GetCurHp()
{
	return m_nCurHp;
}


void cgAircraft::SetCurHp(int hp)
{
	m_nCurHp = hp;

	TCHAR szText[CG_SHORT_TEXT_BUFF_LEN];
	cgSprintf(szText, CG_SHORT_TEXT_BUFF_LEN, TEXT("%d/%d"), m_nCurHp, m_nMaxHp);
	m_spText->SetText(szText);
}

void cgAircraft::SetMaxHp( int maxHp )
{
	m_nMaxHp = maxHp;
}

int cgAircraft::GetMaxHp()
{
	return m_nMaxHp;
}


void cgAircraft::OnRecover( int nHp )
{
	SetCurHp(m_nCurHp+nHp);
}


void cgAircraft::OnHurt( int nHp )
{
	SetCurHp(m_nCurHp-nHp);

	StartAction(new cgBlink(10.0f, 0.2f));
//	StartAction(new cgAircraftEffectAction(TEXT("./res/effect/BeiJi_01.png"), 0.5f, 0, 0));
	if (m_nCurHp <= 0)
	{
		SetAlive(false);
	}
}


cgAircraftPtr cgAircraft::CreateAircraft( int nConfigId, int nEntityID )
{
	cgAircraftConfig * pkConfig = cgILSConfigManager::Get()->FindAircraftConfigByID(nConfigId);
	if (!pkConfig)
		return NULL;

	cgAircraftPtr spAircraft = new cgAircraft;

	spAircraft->SetConfig(pkConfig);
	spAircraft->SetID(nEntityID);
	spAircraft->SetMaxHp(pkConfig->nBasicMaxHp);
	spAircraft->SetCurHp(pkConfig->nBasicMaxHp);
	spAircraft->SetModel(pkConfig->strModel.c_str());
	spAircraft->SetSize(pkConfig->nBoundWidth, pkConfig->nBoundHeight);

	// ¼ÓÔØÎäÆ÷£¬to do£¡
	cgAircraftWeaponPtr spWeapon = new cgAircraftWeapon(pkConfig->nMainWeaponID, pkConfig->nMainWeaponLvl);
	spAircraft->SetMainWeapon(spWeapon);

	return spAircraft;
}

void cgAircraft::SetModel( const cgString & path )
{
	cgImagePtr spImage = cgSrcImageManager::Get()->LoadImage(path.c_str());
	if (spImage)
	{
		m_spActor = new cgGameSprite(spImage);
		AttachChild(&m_spActor);
	}
}


bool cgAircraft::IsInvalid()
{
	return m_bInvalid;
}

void cgAircraft::SetInvalid( bool bInvalid )
{
	m_bInvalid = bInvalid;
}


bool cgAircraft::IsAlive()
{
	return m_bAlive;
}

void cgAircraft::SetAlive( bool bAlive )
{
	m_bAlive = bAlive;
	if (!m_bAlive)
	{
		cgGameTools::PostGameMessage(cgGameMessage_AircraftBeKilled, this);

		cgActionSequence * pkSequence = new cgActionSequence;
		pkSequence->Add(new cgScaleTo(3.0f, 3.0f, 0.05f));
		pkSequence->Add(new cgScaleTo(1.0f, 1.0f, 0.05f));

		cgActionBundle * pkBondle = new cgActionBundle;
		
		pkBondle->Add(new cgRotate(cgMath::PI*5.0f));
		pkBondle->Add(new cgMoveBy(0.0f, 200.0f, 0.5f));
		pkBondle->Add(new cgScaleTo(0.1f, 0.1f, 0.5f));

		pkSequence->Add(pkBondle);

		StartAction(pkSequence);

		cgSoundManager::Get()->PlaySound(8);
	}
}

void cgAircraft::SetCamp( cgFlyObjectCamp enmCamp )
{
	m_enmCamp = enmCamp;
}

cgFlyObjectCamp cgAircraft::GetCamp()
{
	return m_enmCamp;
}

void cgAircraft::SetMainWeapon( cgAircraftWeaponPtr spWeapon )
{
	
	if (spWeapon)
	{ 
		m_spMainWeapon = spWeapon;
		m_spMainWeapon->SetAircaft(this);
	}
}

cgAircraftWeaponPtr cgAircraft::GetMainWeapon()
{
	return m_spMainWeapon;
}

cgAircraftConfig * cgAircraft::GetConfig()
{
	return m_pkConfig;
}

void cgAircraft::SetConfig( cgAircraftConfig * pkConfig )
{
	m_pkConfig = pkConfig;
}

void cgAircraft::SetState( cgAircraftState enmState )
{
	m_enmState = enmState;
}

cgAircraftState cgAircraft::GetState()
{
	return m_enmState;
}

// ----------------------------------------------------------------------------------------------
//
//cgAircraftEffectAction::cgAircraftEffectAction( const cgString & path, float fTime, float xOff, float yOff )
//{
//	m_strPath = path;
//	m_fTime = fTime;
//	m_fXOff = xOff;
//	m_fYOff = yOff;
//}
//
//bool cgAircraftEffectAction::Start( cgSpirit * pkSpirit )
//{
//	if (!cgSpiritAction::Start(pkSpirit))
//		return false;
//
//	cgImagePtr spImage = cgSrcImageManager::Get()->LoadImage(m_strPath.c_str());
//	if (spImage)
//	{
//		m_spSequence = cgXLoadSequenceFromImage(spImage, 0.1f, 5, 0, 0, 512/5, 128);
//	}
//
//	if (m_spSequence)
//	{
//		m_spSequence->SetLocalPosition(m_fXOff, m_fYOff);
//		pkSpirit->AttachChild(&m_spSequence);
//	}
//
//	return true;
//}
//
//void cgAircraftEffectAction::Update( float fDeltaTime )
//{
//	m_fTime -= fDeltaTime;
//	if (m_fTime < 0)
//	{
//		m_bIsFinished = true;
//		m_pkSpirit->DetachChild(&m_spSequence);
//	}
//}
