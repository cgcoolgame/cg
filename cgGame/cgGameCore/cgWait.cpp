#include "StdAfx.h"
#include "cgWait.h"


cgWait::cgWait(void)
{
	m_strName = "cgWait";
	m_fWaitTime = 0.0f;
}

cgWait::cgWait( float waitTime )
{
	m_strName = "cgWait";
	m_fWaitTime = waitTime;
}

void cgWait::DoUpdate( float fDeltaTime )
{
	if (GetActionTime() >= m_fWaitTime)
	{
		Stop();
	}
}
