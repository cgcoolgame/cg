#include "StdAfx.h"
#include "cgSvrRoom.h"


cgSvrRoom::cgSvrRoom(void)
{
	m_enmGameStage = cgRoomGameStage_Waiting;
}


cgSvrRoom::~cgSvrRoom(void)
{
}

cgRoomGameStage cgSvrRoom::GetStage()
{
	return m_enmGameStage;
}

void cgSvrRoom::Update( int nTime )
{

}

void cgSvrRoom::Start()
{

}

void cgSvrRoom::AddPlayer( cgPlayerInfo * pkPlayer )
{

}
