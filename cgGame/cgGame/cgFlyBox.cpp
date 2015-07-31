#include "StdAfx.h"
#include "cgFlyBox.h"
#include "cgSrcImageManager.h"
#include "cgILSConfigManager.h"



cgFlyBox::cgFlyBox( )
{
	m_nID = 0;
	m_pkConfig = NULL;
	m_bInvalid = false;
}


cgFlyBox::~cgFlyBox(void)
{
	DetachChild(&m_spModel);
}

void cgFlyBox::Affect( cgAircraftPtr spAircraft )
{
	switch (m_pkConfig->enmType)
	{
	case cgFlyBoxType_Weapon:
		{
			spAircraft->GetMainWeapon()->Levelup();
		}break;
	case cgFlyBoxType_Toolkit:
		{
			spAircraft->OnRecover(m_pkConfig->nParam1);
		}break;
	default:
		break;
	}
}

void cgFlyBox::SetID(int nID)
{
	m_nID = nID;
}

int cgFlyBox::GetID()
{
	return m_nID;
}

void cgFlyBox::SetConfig( cgFlyBoxConfig * pkConfig )
{
	m_pkConfig = pkConfig;
}

cgFlyBoxConfig* cgFlyBox::GetConfig()
{
	return m_pkConfig;
}

void cgFlyBox::SetModel( const cgString & strPath )
{
	cgImagePtr spImage = cgSrcImageManager::Get()->LoadImage(strPath.c_str());
	if (spImage)
	{
		m_spModel = new cgGameSprite(spImage);
		AttachChild(&m_spModel);

		SetSize(m_spModel->GetSize());
	}
}


cgFlyBoxPtr cgFlyBox::CreateFlyBox( int nID )
{
	cgFlyBoxConfig * pkConfig = cgILSConfigManager::Get()->FindFlyBoxConfigByID(nID);
	if (!pkConfig)
		return NULL;

	cgFlyBoxPtr spBox = new cgFlyBox;
	spBox->SetID(nID);
	spBox->SetConfig(pkConfig);
	spBox->SetModel(pkConfig->strModel);

	return spBox;
}


bool cgFlyBox::IsInvalid()
{
	return m_bInvalid;
}

void cgFlyBox::SetInvalid( bool bInvalid )
{
	m_bInvalid = bInvalid;
}

