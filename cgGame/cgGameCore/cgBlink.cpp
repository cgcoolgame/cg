#include "StdAfx.h"
#include "cgBlink.h"
#include "cgGameObject.h"
#include <cgMath.h>

cgBlink::cgBlink(void)
{
	m_strName = "cgBlink";
	m_fBlinkFreq = 0.0f;
	m_fBlinkTime = 0.0f;
	m_fBlinkTimeSpace = 0.0f;
	m_fBlinkDeltaTime = 0.0f;
}

cgBlink::cgBlink( float blinkFreq, float binkTime )
{
	m_strName = "cgBlink";
	m_fBlinkFreq = max(blinkFreq, cgMath::FLOAT_MIN);
	m_fBlinkTime = max(binkTime, cgMath::FLOAT_MIN);
	m_fBlinkTimeSpace = 0.5f/m_fBlinkFreq;
	m_fBlinkDeltaTime = 0.0f;
}



void cgBlink::DoUpdate( float fDeltaTime )
{
	if (m_fBlinkTime > GetActionTime())
	{
		m_fBlinkDeltaTime += fDeltaTime;
		if (m_fBlinkDeltaTime >= m_fBlinkTimeSpace)
		{
			m_fBlinkDeltaTime -= m_fBlinkTimeSpace;
			m_pkObject->SetVisible(!m_pkObject->IsVisible());
		}
	}else
	{
		m_pkObject->SetVisible(true);
		Stop();
	}
}
