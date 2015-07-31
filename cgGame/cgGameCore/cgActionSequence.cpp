#include "StdAfx.h"
#include "cgActionSequence.h"


cgActionSequence::cgActionSequence(void)
{
	m_strName = "cgActionSequence";
}

void cgActionSequence::Add( cgAction * pkAction )
{
	if (pkAction)
		m_kActionList.push_back(pkAction);
}

size_t cgActionSequence::GetSize()
{
	return m_kActionList.size();
}


void cgActionSequence::DoUpdate( float fDeltaTime )
{
	m_spCurAction->Update(fDeltaTime);

	if (m_spCurAction->IsStopped())
		Next();
}

void cgActionSequence::DoStart()
{
	Next();
}

void cgActionSequence::Next()
{
	m_spCurAction = NULL;
	if (!m_kActionList.empty())
	{
		m_spCurAction = m_kActionList.front();
		m_kActionList.pop_front();

		m_spCurAction->SetObject(m_pkObject);
		m_spCurAction->Start();
	}else
	{
		Stop();
	}
}

