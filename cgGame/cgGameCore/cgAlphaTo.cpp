#include "StdAfx.h"
#include "cgAlphaTo.h"
#include "cgGameObject.h"

cgAlphaTo::cgAlphaTo(void)
{
	m_strName = "cgAlphaTo";
	m_fAlphaTo = 0.0f;
}

cgAlphaTo::cgAlphaTo( float alphaTo, float alphaTime )
{
	m_strName = "cgAlphaTo";
	m_fAlphaTo = alphaTo;
	m_fAlphaTime = alphaTime;
}

void cgAlphaTo::DoStart()
{
	m_fAlphaBy = m_fAlphaTo - m_pkObject->GetAlpha();
	m_fLeftAlphaBy = m_fAlphaBy;
	m_fAlphaSpeed = m_fAlphaBy/m_fAlphaTime;
}
