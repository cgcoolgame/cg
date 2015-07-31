#include "StdAfx.h"
#include "cgGameTaskUtility.h"



cgGameTask_SimpleWait::cgGameTask_SimpleWait( float fWaitTime )
{
	m_fWaitTime = fWaitTime;
}

void cgGameTask_SimpleWait::Update( float fDeltaTime )
{
	m_fWaitTime -= fDeltaTime;

	if (m_fWaitTime <= 0.0f)
		OnEnd();
}

bool cgGameTask_SimpleWait::IsTaskOver()
{
	return m_fWaitTime <= 0.0f;
}
