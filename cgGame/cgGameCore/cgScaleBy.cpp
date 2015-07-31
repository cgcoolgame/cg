#include "StdAfx.h"
#include "cgScaleBy.h"
#include "cgGameObject.h"
#include <cgMath.h>

cgScaleBy::cgScaleBy(void)
{
	m_strName = "cgScaleBy";
	m_fScaleTime = 1.0f;
}

cgScaleBy::cgScaleBy( float scaleX, float scaleY, float scaleTime )
{
	m_strName = "cgScaleBy";
	m_kScaleBy.x = scaleX;
	m_kScaleBy.y = scaleY;
	m_fScaleTime = max(scaleTime, cgMath::FLOAT_MIN);
	m_kLeftScale = m_kScaleBy;
	m_kScaleSpeed = m_kScaleBy/scaleTime;
}

cgScaleBy::cgScaleBy( const cgVector& scale, float scaleTime )
{
	m_strName = "cgScaleBy";
	m_kScaleBy = scale;
	m_fScaleTime = max(scaleTime, cgMath::FLOAT_MIN);;
	m_kLeftScale = m_kScaleBy;
	m_kScaleSpeed = m_kScaleBy/scaleTime;
}

//void cgScaleBy::DoUpdate( float fDeltaTime )
//{
//	float x = cgMath::Lerp(m_fLeftScale.x, m_fScaleBy.x, fDeltaTime*10);
//	float y = cgMath::Lerp(m_fLeftScale.y, m_fScaleBy.y, fDeltaTime*10);
//
//	cgVector deltaScale(x-m_fLeftScale.x, y-m_fLeftScale.y);
//	
//	if (m_fLeftScale.Length() < m_fScaleBy.Length())
//	{
//		m_pkObject->WorldScale(deltaScale);
//		m_fLeftScale += deltaScale;
//
//	}else
//	{
//		m_pkObject->WorldScale(m_fLeftScale);
//		Stop();
//	}
//}
//
void cgScaleBy::DoUpdate( float fDeltaTime )
{
	cgVector deltaScale = m_kScaleSpeed*fDeltaTime;

	if (m_kLeftScale.Length() > deltaScale.Length())
	{
		m_pkObject->LocalScale(deltaScale);
		m_kLeftScale -= deltaScale;
	}else
	{
		m_pkObject->LocalScale(m_kLeftScale);
		Stop();
	}
}


