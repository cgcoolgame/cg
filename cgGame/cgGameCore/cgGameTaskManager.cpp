#include "StdAfx.h"
#include "cgGameTaskManager.h"


cgGameTaskManager::cgGameTaskManager(void)
{
}


cgGameTaskManager::~cgGameTaskManager(void)
{
	m_kTaskPtrList.clear();
}


bool cgGameTaskManager::Initialize()
{
	return true;
}


void cgGameTaskManager::AddGameTask( cgGameTaskPtr spTask )
{
	if (spTask)
	{
		spTask->Start();
		m_kTaskPtrList.push_back(spTask);
	}
}

void cgGameTaskManager::Update( float fDeltaTime )
{
	UpdateTasks(fDeltaTime);
	CleanUp();
}

void cgGameTaskManager::UpdateTasks( float fDeltaTime )
{
	cgGameTaskPtrList::iterator it = m_kTaskPtrList.begin();
	for (; it != m_kTaskPtrList.end(); ++it)
	{
		cgGameTaskPtr spTask = *it;
		if (spTask)
			spTask->Update(fDeltaTime);
	}
}

void cgGameTaskManager::CleanUp()
{
	cgGameTaskPtrList::iterator it = m_kTaskPtrList.begin();
	while (it != m_kTaskPtrList.end())
	{
		cgGameTaskPtr spTask = *it;
		if (!spTask || spTask->IsTaskOver())
		{
			it = m_kTaskPtrList.erase(it);
		}else
		{
			++it;
		}
	}
}
