#include "StdAfx.h"
#include "cgVisible.h"
#include "cgGameObject.h"

cgVisible::cgVisible(void)
{
	m_strName = "cgVisible";
	m_bVisible = true;
}

cgVisible::cgVisible( bool visible )
{
	m_strName = "cgVisible";
	m_bVisible = visible;
}

void cgVisible::DoStart()
{
	m_pkObject->SetVisible(m_bVisible);
	Stop();
}

