#include "StdAfx.h"
#include "cgGameCommandManager.h"



cgGameCommandManager::cgGameCommandManager()
{

}

cgGameCommandManager::~cgGameCommandManager()
{
	m_kUndoCommandList.clear();
	m_kRedoCommandList.clear();
}

bool cgGameCommandManager::Initialize()
{
	return true;
}


void cgGameCommandManager::AddGameCommand( cgGameCommandPtr spCommand )
{
	if (!spCommand)
		return ;

	spCommand->Execute();
	m_kUndoCommandList.push_back(spCommand);

	// �����µ������ʱ��redo����Ч��,���֮
	m_kRedoCommandList.clear();
}


bool cgGameCommandManager::Undo()
{
	if (m_kUndoCommandList.empty())
		return false;

	cgGameCommandPtr spCommand = m_kUndoCommandList.back();
	m_kUndoCommandList.pop_back();

	if (!spCommand)
		return false;

	spCommand->Unexecute();
	m_kRedoCommandList.push_back(spCommand);
	return true;
}

bool cgGameCommandManager::Redo()
{
	if (m_kRedoCommandList.empty())
		return false;

	cgGameCommandPtr spCommand = m_kRedoCommandList.back();
	m_kRedoCommandList.pop_back();

	if (spCommand)
		return false;

	spCommand->Execute();
	m_kUndoCommandList.push_back(spCommand);

	return true;
}


