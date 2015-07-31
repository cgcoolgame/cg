#include "StdAfx.h"
#include "cgGameTask.h"
#include "CGGameApp.h"
#include "cgGameCommandManager.h"


cgGameTask::cgGameTask(void)
{
	m_bIsTaskOver = false;
}


cgGameTask::~cgGameTask(void)
{
}

void cgGameTask::Start()
{
	m_bIsTaskOver = false;
	OnStarted();
}

void cgGameTask::Update( float fDeltaTime )
{
}

void cgGameTask::OnStarted()
{
	if (m_spStartedCmd)
		cgGameCommandManager::Get()->AddGameCommand(m_spStartedCmd);
}


void cgGameTask::OnEnd()
{
	if (m_spEndedCmd)
		cgGameCommandManager::Get()->AddGameCommand(m_spEndedCmd);
}

bool cgGameTask::IsTaskOver()
{
	return m_bIsTaskOver;
}

void cgGameTask::SetCommandOnStarted( cgGameCommandPtr spCommand )
{
	m_spStartedCmd = spCommand;
}


void cgGameTask::SetCommandOnEnded( cgGameCommandPtr spCommand )
{
	m_spEndedCmd = spCommand;
}
