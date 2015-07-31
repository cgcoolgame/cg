#include "StdAfx.h"
#include "cgActionBundle.h"


cgActionBundle::cgActionBundle(void)
{
	m_strName = "cgActionBundle";
}

void cgActionBundle::Add( cgAction * pkAction )
{
	if (pkAction)
		m_kActionList.push_back(pkAction);
}

size_t cgActionBundle::GetSize()
{
	return m_kActionList.size();
}

void cgActionBundle::DoStart()
{
	cgActionPtrList::iterator it = m_kActionList.begin();
	for (; it != m_kActionList.end(); ++it)
	{
		cgActionPtr spAction = *it;
		spAction->SetObject(m_pkObject);
		spAction->Start();
	}
}

void cgActionBundle::DoUpdate( float fDeltaTime )
{
	cgActionPtrList::iterator it = m_kActionList.begin();
	while (it != m_kActionList.end())
	{
		cgActionPtr spAction = *it;
		spAction->Update(fDeltaTime);
		if (spAction->IsStopped())
		{
			it = m_kActionList.erase(it);
		}else
		{
			++it;
		}
	}

	if (m_kActionList.empty())
	{
		Stop();
	}
}

