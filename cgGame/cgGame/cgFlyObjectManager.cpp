#include "StdAfx.h"
#include "cgFlyObjectManager.h"
#include "cgEngineTools.h"
#include "cgILoveShootingGame.h"
#include "cgGameTools.h"
#include "cgSoundManager.h"
#include <cgMath.h>
#include <cgSceneManager.h>


cgFlyObjectManager::cgFlyObjectManager(void)
{
}


cgFlyObjectManager::~cgFlyObjectManager(void)
{
	ClearAll();
}


bool cgFlyObjectManager::Initialize()
{
	cgSoundManager::Get()->SetSoundChannelGroupVolume(2, 0.3f);
	return true;
}

void cgFlyObjectManager::Update( float fDeltaTime )
{
	for (cgAircraftList::iterator it = m_kAircraftList.begin(); 
		it != m_kAircraftList.end(); ++it)
	{
		cgAircraftPtr spCraft= *it;
		spCraft->UpdateCraft(fDeltaTime);
	}

	CheckPosition();
	CheckCollision();
	CleanupInvalidObjects();

	if (false && GetAircraftCount() < 50)
	{
		/*	cgAircraftPtr spNew = cgAircraft::CreateAircraft(rand()%3+2, 0);
		spNew->SetCamp(cgFlyObjectCamp_Enemy);
		int x = rand()%cgILoveShootingGame::Get()->GetWidth()-cgILoveShootingGame::Get()->GetWidth()/2;
		int y = (cgILoveShootingGame::Get()->GetHeight()/2);
		spNew->SetCenter(x, -y);
		spNew->SetRotation(cgMath::PI);
		AddAircraft(&spNew);

		spNew->StartAction(new cgSpiritAction_Move(0, spNew->GetConfig()->nBasicSpeed));*/
	}
}


void cgFlyObjectManager::AddAircraft( cgAircraftPtr spAircraft )
{
	if (spAircraft)
	{
		m_kAircraftList.push_back(spAircraft);
		cgSceneManager::Get()->GetSceneRoot()->AttachChild(&spAircraft);
	}
}


size_t cgFlyObjectManager::GetAircraftCount()
{
	return m_kAircraftList.size();
}


void cgFlyObjectManager::AddBullet( cgBulletPtr spBullet )
{
	if (spBullet)
	{
		m_kBulletList.push_back(spBullet);
		cgSceneManager::Get()->GetSceneRoot()->AttachChild(&spBullet);
	}
}

size_t cgFlyObjectManager::GetBulletCount()
{
	return m_kBulletList.size();
}

void cgFlyObjectManager::AddFlyBox( cgFlyBoxPtr spBox )
{
	if (spBox)
	{
		m_kFlyBoxList.push_back(spBox);
		cgSceneManager::Get()->GetSceneRoot()->AttachChild(&spBox);
	}
}

size_t cgFlyObjectManager::GetFlyBoxCount()
{
	return m_kFlyBoxList.size();
}

void cgFlyObjectManager::ClearAll()
{
	for (cgAircraftList::iterator it = m_kAircraftList.begin(); 
		it != m_kAircraftList.end(); ++it)
	{
		cgAircraftPtr spCraft= *it;
		spCraft->Destroy();
	}
	m_kAircraftList.clear();

	for (cgBulletList::iterator it = m_kBulletList.begin();
		it != m_kBulletList.end(); ++it)
	{
		cgBulletPtr spBullet = *it;
		spBullet->Destroy();
	}
	m_kBulletList.clear();

	for (cgFlyBoxList::iterator it = m_kFlyBoxList.begin(); 
		it != m_kFlyBoxList.end(); ++it)
	{
		cgFlyBoxPtr spBox = *it;
		spBox->Destroy();
	}
}


// -----------------------------------------------------------------------------------


void cgFlyObjectManager::CheckCollision()
{
	{
		cgBulletList::iterator it = m_kBulletList.begin();
		for (; it != m_kBulletList.end(); ++it)
		{
			cgBulletPtr spBullet = *it;
			TryBulletHitAircrafts(spBullet);
		}
	}
	
	{
		cgAircraftList::iterator it = m_kAircraftList.begin();
		for (; it != m_kAircraftList.end(); ++it)
		{
			cgAircraftPtr spAircraft = *it;
			TryAircraftHitAircrafts(spAircraft);
		}
	}
	{
		for (cgFlyBoxList::iterator it = m_kFlyBoxList.begin();
			it != m_kFlyBoxList.end(); ++it)
		{
			cgFlyBoxPtr spBox = *it;
			TryFlyBoxAffectAircrafts(spBox);
		}
	}
}

void cgFlyObjectManager::CleanupInvalidObjects()
{
	{
		cgAircraftList::iterator it = m_kAircraftList.begin();
		while (it != m_kAircraftList.end())
		{
			cgAircraftPtr spCraft = *it;

			if (!spCraft || spCraft->IsInvalid())
			{
				spCraft->Destroy();
				it = m_kAircraftList.erase(it);
			}else
			{
				++it;
			}
		}
	}
	{
		cgBulletList::iterator it = m_kBulletList.begin();
		while (it != m_kBulletList.end())
		{
			cgBulletPtr spBullet = *it;

			if (!spBullet || spBullet->IsInvalid())
			{
				spBullet->Destroy();
				it = m_kBulletList.erase(it);
			}else
			{
				++it;
			}
		}
	}
	{
		cgFlyBoxList::iterator it = m_kFlyBoxList.begin();
		while (it != m_kFlyBoxList.end())
		{
			cgFlyBoxPtr spBox = *it;
			if (!spBox || spBox->IsInvalid())
			{
				spBox->Destroy();
				it = m_kFlyBoxList.erase(it);
			}else
			{
				++it;
			}
		}
	}
}


bool cgFlyObjectManager::TryBulletHitAircrafts( cgBulletPtr spBullet )
{
	if (!spBullet)
		return 0;

	cgRectF bulletBound;
	spBullet->GetBound(bulletBound);

	cgRectF craftBound;

	bool bHit = false;
	cgAircraftList::iterator it = m_kAircraftList.begin();
	for (; it != m_kAircraftList.end(); ++it)
	{
		cgAircraftPtr spCraft = *it;

		// 不存在或者未激活，跳过
		if (!spCraft || !spCraft->IsAlive() )
			continue;

		// 阵营不是对立的，跳过
		if (!cgXFlyObjectCanAttack(spBullet->GetCamp(), spCraft->GetCamp()))
			continue;

		spCraft->GetBound(craftBound);
		if (cgXIsRectIntersect(bulletBound, craftBound))
		{
			DoBulletHitAircraft(spBullet, spCraft);
			bHit = true;

			// 全屏子弹可以攻击多个目标
			if (spBullet->GetConfig()->nAreaFlag != 1)
				break;
		}
	}

	if (bHit)
		spBullet->SetInvalid(true);


	return bHit;
}

void cgFlyObjectManager::DoBulletHitAircraft( cgBulletPtr spBullet, cgAircraftPtr spAircraft )
{
	if (!spBullet || !spAircraft)
		return ;

	spAircraft->OnHurt(spBullet->GetAttack());

	// todo 播放击中的声音
//	cgSoundManager::Get()->PlaySound(spBullet->GetConfig()->nHitSoundID);
}

bool cgFlyObjectManager::TryAircraftHitAircrafts( cgAircraftPtr spAttacker )
{
	// 死掉的就不撞了
	if (!spAttacker || !spAttacker->IsAlive())
		return 0;

	cgRectF attackerBound;
	spAttacker->GetBound(attackerBound);

	cgRectF attackeeBound;

	bool bHit = false;
	cgAircraftList::iterator it = m_kAircraftList.begin();
	for (; it != m_kAircraftList.end(); ++it)
	{
		cgAircraftPtr spCraft = *it;

		// 不存在或者未激活，跳过
		if (!spCraft || !spCraft->IsAlive() )
			continue;

		// 阵营不是对立的，跳过
		if (!cgXFlyObjectCanAttack(spAttacker->GetCamp(), spCraft->GetCamp()))
			continue;

		spCraft->GetBound(attackeeBound);
		if (cgXIsRectIntersect(attackerBound, attackeeBound))
		{
			DoAircraftHitAircraft(spAttacker, spCraft);
			bHit = true;
			break;
		}
	}

	return bHit;
}

void cgFlyObjectManager::DoAircraftHitAircraft( cgAircraftPtr spAttacker, cgAircraftPtr spAttackee )
{
	int nEffect = spAttacker->GetCurHp()-spAttackee->GetCurHp();
	// 每次撞击，必定挂掉一个，谁血少谁死
	spAttackee->OnHurt(spAttacker->GetMaxHp());
	spAttacker->OnHurt(spAttackee->GetMaxHp());

}

bool cgFlyObjectManager::TryFlyBoxAffectAircrafts( cgFlyBoxPtr spBox )
{
	if (!spBox)
		return false;

	cgRectF boxBound;
	spBox->GetBound(boxBound);

	cgRectF craftBound;

	bool bHit = false;
	cgAircraftList::iterator it = m_kAircraftList.begin();
	for (; it != m_kAircraftList.end(); ++it)
	{
		cgAircraftPtr spCraft = *it;

		// 不存在或者未激活，跳过
		if (!spCraft || !spCraft->IsAlive() )
			continue;

		// 阵营不是对立的，跳过
		if ( spCraft->GetCamp() != cgFlyObjectCamp_Self)
			continue;

		spCraft->GetBound(craftBound);
		if (cgXIsRectIntersect(boxBound, craftBound))
		{
			DoFlyBoxAffectAircraft(spBox, spCraft);
			bHit = true;
			break;
		}
	}

	if (bHit)
		spBox->SetInvalid(true);

	return bHit;
}

void cgFlyObjectManager::DoFlyBoxAffectAircraft( cgFlyBoxPtr spBox, cgAircraftPtr spCraft )
{
	spBox->Affect(spCraft);
}


void cgFlyObjectManager::CheckPosition()
{
	CheckBulletPosition();
	CheckAircraftPosition();
	CheckFlyBoxPosision();
}

void cgFlyObjectManager::CheckBulletPosition()
{
	cgRectF screenRect(-300, -cgILoveShootingGame::Get()->GetHeight()/2, 
		600, cgILoveShootingGame::Get()->GetHeight());

	cgRectF bulletRect;
	cgBulletList::iterator it = m_kBulletList.begin();
	for (; it != m_kBulletList.end(); ++it)
	{
		cgBulletPtr spBullet = *it;

		if (!spBullet || spBullet->IsInvalid())
			continue;
	
		spBullet->GetBound(bulletRect);

		if (!cgXIsRectIntersect(bulletRect, screenRect))
			spBullet->SetInvalid(true);
	}

}

void cgFlyObjectManager::CheckAircraftPosition()
{
	cgRectF screenRect(-300, -cgILoveShootingGame::Get()->GetHeight()/2, 
		600, cgILoveShootingGame::Get()->GetHeight());

	cgRectF craftRect;
	cgAircraftList::iterator it = m_kAircraftList.begin();
	for (;it != m_kAircraftList.end(); ++it)
	{
		cgAircraftPtr spAircraft = *it;

		if (!spAircraft || spAircraft->IsInvalid())
			continue;

		spAircraft->GetBound(craftRect);

		if (spAircraft != cgILoveShootingGame::Get()->GetMainCraft())
		{
			if (!cgXIsRectIntersect(craftRect, screenRect))
				spAircraft->SetInvalid(true);

		}else
		{
			int nWidth = screenRect.w;
			int nHeight = screenRect.h;
			cgVector pos = spAircraft->GetWorldPosition();

			if (pos.x < -(nWidth/2-craftRect.w/2))
			{
				spAircraft->SetWorldPosition( -(nWidth/2-craftRect.w/2), pos.y);
			}else if (pos.x >  (nWidth/2-craftRect.w/2))
			{
				spAircraft->SetWorldPosition( nWidth/2-craftRect.w/2, pos.y);
			}

			if (pos.y < -(nHeight/2-craftRect.h/2))
			{
				spAircraft->SetWorldPosition(pos.x, -(nHeight/2-craftRect.h/2));
			}else if (pos.y > (nHeight/2-craftRect.h/2))
			{
				spAircraft->SetWorldPosition(pos.x,(nHeight/2-craftRect.h/2));
			}
		}

	}
}


void cgFlyObjectManager::CheckFlyBoxPosision()
{
	cgRectF screenRect(-300, -cgILoveShootingGame::Get()->GetHeight()/2, 
		600, cgILoveShootingGame::Get()->GetHeight());

	cgRectF boxRect;
	cgFlyBoxList::iterator it = m_kFlyBoxList.begin();
	for (; it != m_kFlyBoxList.end(); ++it)
	{
		cgFlyBoxPtr spBox = *it;

		if (!spBox || spBox->IsInvalid())
			continue;

		spBox->GetBound(boxRect);

		if (!cgXIsRectIntersect(boxRect, screenRect))
			spBox->SetInvalid(true);
	}
}


// -------------------------------------------------------------------------------------------
bool cgXFlyObjectCanAttack( cgFlyObjectCamp enmRed, cgFlyObjectCamp enmBlue )
{
	// 毁灭者攻击一切，也可以被一切攻击
	if (enmRed == cgFlyObjectCamp_Destroyer || enmBlue == cgFlyObjectCamp_Destroyer)
		return true;

	// 玩家和电脑互相敌对
	if (enmRed == cgFlyObjectCamp_Self && enmBlue == cgFlyObjectCamp_Enemy)
		return true;

	if (enmRed == cgFlyObjectCamp_Enemy && enmBlue == cgFlyObjectCamp_Self)
		return true;

	return false;
}
