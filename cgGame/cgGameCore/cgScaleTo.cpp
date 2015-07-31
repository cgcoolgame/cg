#include "StdAfx.h"
#include "cgScaleTo.h"
#include "cgGameObject.h"
#include <cgMath.h>

cgScaleTo::cgScaleTo(void)
{
	m_strName = "cgScaleTo";
	m_fScaleTime = cgMath::FLOAT_MIN;
}

cgScaleTo::cgScaleTo( const cgVector & destScale, float scaleTime )
{
	m_strName = "cgScaleTo";
	m_fScaleTime = max(scaleTime, cgMath::FLOAT_MIN);;
	m_kDestScale = destScale;
}

cgScaleTo::cgScaleTo( float destScaleX, float destScaleY, float scaleTime )
{
	m_strName = "cgScaleTo";
	m_fScaleTime = max(scaleTime, cgMath::FLOAT_MIN);;
	m_kDestScale.x = destScaleX;
	m_kDestScale.y = destScaleY;
}

void cgScaleTo::DoStart()
{
	m_kScaleSpeed = (m_kDestScale-m_pkObject->GetLocalScale())/m_fScaleTime;
}

void cgScaleTo::DoUpdate( float fDeltaTime )
{
	cgVector deltaScale = m_kScaleSpeed*fDeltaTime;

	if (cgVector::Dot(m_kDestScale - m_pkObject->GetLocalScale() -deltaScale, deltaScale) > 0)
	{
		m_pkObject->LocalScale(deltaScale);
	}else
	{
		m_pkObject->SetLocalScale(m_kDestScale);
		Stop();
	}
}

