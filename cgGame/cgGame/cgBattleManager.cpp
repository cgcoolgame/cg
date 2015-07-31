#include "StdAfx.h"
#include "cgBattleManager.h"
#include "cgTxtDataReader.h"
#include "cgAircraft.h"
#include "cgILSConfigManager.h"
#include "cgFlyObjectManager.h"
#include <cgMath.h>
#include <cgMove.h>
#include <cgActionBundle.h>
#include <cgRotate.h>


cgBattleManager::cgBattleManager(void)
{
	m_nCurBattleID = 0;
	m_fBattleTime = 0.0f;
	m_fScrolledMiles = 0.0f;
	m_pkConfig = NULL;

}


cgBattleManager::~cgBattleManager(void)
{
}

bool cgBattleManager::Initialize()
{
	return true;
}


void cgBattleManager::SetCurBattle( int nBattleID )
{
	m_fBattleTime = 0.0f;
	m_fScrolledMiles = 0.0f;
	m_nCurBattleID = nBattleID;
	LoadBattle();
	StartBattle();
}

void cgBattleManager::Update( float fDeltaTime )
{
	if (m_pkConfig)
	{
		m_fBattleTime += fDeltaTime;
		m_fScrolledMiles = m_fBattleTime*m_pkConfig->nScrollSpeed;

		for (; m_iterCraft != m_kCraftUnityList.end(); ++m_iterCraft)
		{
			cgAircraftUnity& kUnity = *m_iterCraft;
			if (m_fScrolledMiles >= kUnity.nPosY )
			{
				AddCraft(kUnity);
			}else
			{
				break;
			}
		}
	}
	
}

void cgBattleManager::LoadBattle()
{
	m_pkConfig = cgILSConfigManager::Get()->FindBattleConfigByID(m_nCurBattleID);
	if (!m_pkConfig)
		return ;
	
	LoadCrafts();
}

void cgBattleManager::LoadCrafts()
{
	m_kDropList.clear();
	m_kCraftUnityList.clear();

	cgTxtDataReader kReader;

	if (!kReader.Open(m_pkConfig->strCraftConfig.c_str()))
		return ;

	kReader.Next();
	const cgTxtRecord * pkRecord = NULL;
	while (pkRecord = kReader.Next())
	{
		cgAircraftUnity kConfig;
		int nIndex = 0;
		kConfig.nPosY = atoi(pkRecord->GetField(nIndex++));
		kConfig.nPosX = atoi(pkRecord->GetField(nIndex++));

		kConfig.nTypeID = atoi(pkRecord->GetField(nIndex++));
		kConfig.nBornID = atoi(pkRecord->GetField(nIndex++));

		kConfig.nBornHp = atoi(pkRecord->GetField(nIndex++));
		kConfig.nBornSpeed = atoi(pkRecord->GetField(nIndex++));
		kConfig.nDropID = atoi(pkRecord->GetField(nIndex++));

		m_kCraftUnityList.push_back(kConfig);
		m_kDropList[kConfig.nBornID] = kConfig.nDropID;
	}
}

void cgBattleManager::StartBattle()
{
	m_iterCraft = m_kCraftUnityList.begin();
}

void cgBattleManager::AddCraft( cgAircraftUnity& kUnity )
{
	cgAircraftPtr spCraft = cgAircraft::CreateAircraft(kUnity.nTypeID, kUnity.nBornID);
	if (spCraft)
	{
		spCraft->SetLocalPosition(kUnity.nPosX, -400);
		spCraft->SetLocalRotation(cgMath::PI);
		spCraft->SetCamp(cgFlyObjectCamp_Enemy);
		
		spCraft->SetMaxHp(kUnity.nBornHp);
		spCraft->SetCurHp(kUnity.nBornHp);

		if (kUnity.nBornSpeed >= 0)
			spCraft->StartAction(new cgMove(0, m_pkConfig->nScrollSpeed+kUnity.nBornSpeed));

		cgFlyObjectManager::Get()->AddAircraft(spCraft);
	}
}

bool cgBattleManager::OnGameMessage( cgGameMessage msg, void * pData, int nLen )
{
	switch (msg)
	{
	case cgGameMessage_AircraftBeKilled:
		{
			cgAircraft * pkCraft = (cgAircraft*)pData;
			int nDropID = m_kDropList[pkCraft->GetID()];
			if ( nDropID != 0)
			{
				cgFlyBoxPtr spBox = cgFlyBox::CreateFlyBox(nDropID);
				if (spBox)
				{
					spBox->SetLocalPosition(pkCraft->GetWorldPosition());

					cgActionBundle * pkBunch = new cgActionBundle;
					pkBunch->Add(new cgRotate(cgMath::PI));
					pkBunch->Add(new cgMove(0.0f, pkCraft->GetConfig()->nBasicSpeed));
					spBox->StartAction(pkBunch);
					cgFlyObjectManager::Get()->AddFlyBox(spBox);
				}
			}

			if (pkCraft->GetID() == m_pkConfig->nBossID)
			{
				SetCurBattle(m_pkConfig->nNextBattle);
			}
		}break;
	}

	return false;
}

cgBattleConfig* cgBattleManager::GetCurBattleConfig()
{
	return m_pkConfig;
}
