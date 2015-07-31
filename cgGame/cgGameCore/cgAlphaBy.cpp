#include "StdAfx.h"
#include "cgAlphaBy.h"
#include "cgGameObject.h"

cgAlphaBy::cgAlphaBy(void)
{
	m_strName = "cgAlphaBy";
	m_fAlphaBy = 0;
	m_fLeftAlphaBy = m_fAlphaBy;
	m_fAlphaTime = 0;
	m_fAlphaSpeed = 0;
}

cgAlphaBy::cgAlphaBy( float alphaBy, float alphaTime )
{
	m_strName = "cgAlphaBy";
	m_fAlphaBy = alphaBy;
	m_fLeftAlphaBy = m_fAlphaBy;
	m_fAlphaTime = alphaTime;
	m_fAlphaSpeed = m_fLeftAlphaBy/m_fAlphaTime;
}

void cgAlphaBy::DoUpdate( float fDeltaTime )
{
	float deltaAlpha = fDeltaTime*m_fAlphaSpeed;
	if (abs(m_fLeftAlphaBy) > abs(deltaAlpha))
	{
		m_pkObject->Alpha(fDeltaTime*m_fAlphaSpeed);
		m_fLeftAlphaBy -= deltaAlpha;
	}else
	{
		m_pkObject->Alpha(m_fLeftAlphaBy);
		Stop();
	}
}
