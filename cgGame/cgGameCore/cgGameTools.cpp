#include "StdAfx.h"
#include "cgGameTools.h"
#include "cgGameTaskUtility.h"
#include "cgGameCommandManager.h"
#include "cgGameMessageListenerManager.h"
#include "cgGameTaskManager.h"


cgGameTools::cgGameTools(void)
{
}


cgGameTools::~cgGameTools(void)
{
}

void cgGameTools::PostGameCommand( cgGameCommandPtr spCommand, float fTimeDelay /*= -1.0f*/ )
{
	if (fTimeDelay <= 0.0f)
	{
		cgGameCommandManager::Get()->AddGameCommand(spCommand);
	}else
	{
		cgGameTaskPtr ptrTask = new cgGameTask_SimpleWait(fTimeDelay);
		ptrTask->SetCommandOnEnded(spCommand);
		cgGameTaskManager::Get()->AddGameTask(ptrTask);;
	}
}

bool cgGameTools::PostGameMessage( cgGameMessage msg, void * pData /*= NULL*/, int nDataLen /*= 0*/ )
{
	return cgGameMessageListenerManager::Get()->DispatchGameMessage(msg, pData, nDataLen);
}
