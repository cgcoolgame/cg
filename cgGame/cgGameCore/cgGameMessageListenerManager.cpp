#include "StdAfx.h"
#include "cgGameMessageListenerManager.h"


cgGameMessageListenerManager::cgGameMessageListenerManager(void)
{
}


cgGameMessageListenerManager::~cgGameMessageListenerManager(void)
{
}

bool cgGameMessageListenerManager::Initialize()
{
	return true;
}


void cgGameMessageListenerManager::Update( float fTime )
{
	// do nothing
}

void cgGameMessageListenerManager::AddListener( cgGameMessageListener * pkListener )
{
	m_kListenerList.push_back(pkListener);
}

void cgGameMessageListenerManager::DelListener( cgGameMessageListener * pkListener )
{
	cgGameMessageListenerList::iterator it = m_kListenerList.begin();
	while ( it != m_kListenerList.end() )
	{
		cgGameMessageListener * pkFind = *it;
		if (pkFind == pkListener)
		{
			it = m_kListenerList.erase(it);
		}else
		{
			++it;
		}
	}
}

bool cgGameMessageListenerManager::DispatchGameMessage( cgGameMessage msg, void * pData, int nLen )
{
	cgGameMessageListenerList::iterator it = m_kListenerList.begin();
	for (; it != m_kListenerList.end(); ++it)
	{
		cgGameMessageListener * pkListener = *it;
		if (pkListener)
			pkListener->OnGameMessage(msg, pData, nLen);
	}

	return true;
}

