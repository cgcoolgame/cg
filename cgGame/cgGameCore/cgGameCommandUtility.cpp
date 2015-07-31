#include "StdAfx.h"
#include "cgGameCommandUtility.h"
#include "CGGameApp.h"


cgGameCommand_ChangeMaxFps::cgGameCommand_ChangeMaxFps( int nNewFps )
{
	m_nNewFps = nNewFps;
	m_nOldFps = -1;
}

cgGameCommand_ChangeMaxFps::~cgGameCommand_ChangeMaxFps()
{

}

bool cgGameCommand_ChangeMaxFps::Execute()
{
	m_nOldFps = cgGameApp::GetGameApp()->GetMaxFPS();
	cgGameApp::GetGameApp()->SetMaxFPS(m_nNewFps);

	return true;
}

bool cgGameCommand_ChangeMaxFps::Unexecute()
{
	cgGameApp::GetGameApp()->SetMaxFPS(m_nOldFps);

	return true;
}

// ------------------------------------------------------------------------
cgGameCommand_ShowFps::cgGameCommand_ShowFps( bool bShow )
{
	m_bShowFps = bShow;
}

bool cgGameCommand_ShowFps::Execute()
{
	m_bOriginShowFps = cgGameApp::GetGameApp()->IsShowFPS();
	cgGameApp::GetGameApp()->ShowFPS(m_bShowFps);

	return true;
}

bool cgGameCommand_ShowFps::Unexecute()
{
	cgGameApp::GetGameApp()->ShowFPS(m_bShowFps);
	return true;
}

// ----------------------------------------------------------------------------
bool cgGameCommand_ToggleFps::Execute()
{
	bool bShow = cgGameApp::GetGameApp()->IsShowFPS();
	cgGameApp::GetGameApp()->ShowFPS(!bShow);

	return true;
}

bool cgGameCommand_ToggleFps::Unexecute()
{
	return Execute();
}
