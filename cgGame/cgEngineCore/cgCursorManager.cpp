#include "StdAfx.h"
#include "cgCursorManager.h"


cgCursorManager::cgCursorManager(void)
{
	m_hCurCursor = NULL;
	m_hDefaultCursor = NULL;
	m_bShowCursor = true;
}


cgCursorManager::~cgCursorManager(void)
{

}

bool cgCursorManager::Initialize()
{
	LoadCursor();
	SetDefaultCursor("IDC_ARROW");
	SetCursor("IDC_ARROW");

	return true;
}


void cgCursorManager::LoadCursor()
{
	m_kCursorMap["IDC_ARROW"] = ::LoadCursor(NULL, IDC_ARROW);
	m_kCursorMap["IDC_HAND"] = ::LoadCursor(NULL, IDC_HAND);
	m_kCursorMap["IDC_APPSTARTING"] = ::LoadCursor(NULL, IDC_APPSTARTING);
	m_kCursorMap["IDC_CROSS"] = ::LoadCursor(NULL, IDC_CROSS);
	m_kCursorMap["IDC_HELP"] = ::LoadCursor(NULL, IDC_HELP);
	m_kCursorMap["IDC_IBEAM"] = ::LoadCursor(NULL, IDC_IBEAM);
	m_kCursorMap["IDC_ICON"] = ::LoadCursor(NULL, IDC_ICON);
	m_kCursorMap["IDC_NO"] = ::LoadCursor(NULL, IDC_NO);
	m_kCursorMap["IDC_SIZE"] = ::LoadCursor(NULL, IDC_SIZE);
	m_kCursorMap["IDC_SIZEALL"] = ::LoadCursor(NULL, IDC_SIZEALL);
	m_kCursorMap["IDC_SIZENESW"] = ::LoadCursor(NULL, IDC_SIZENESW);
	m_kCursorMap["IDC_SIZENS"] = ::LoadCursor(NULL, IDC_SIZENS);
	m_kCursorMap["IDC_SIZENWSE"] = ::LoadCursor(NULL, IDC_SIZENWSE);
	m_kCursorMap["IDC_SIZEWE"] = ::LoadCursor(NULL, IDC_SIZEWE);
	m_kCursorMap["IDC_UPARROW"] = ::LoadCursor(NULL, IDC_UPARROW);
	m_kCursorMap["IDC_WAIT"] = ::LoadCursor(NULL, IDC_WAIT);

	const static char * szCursorName[]=
	{
		"default",
		"attack",
		"pick",
		"hand"
	};
	static int nCount = sizeof(szCursorName)/sizeof(char*);

	char szCursorPath[MAX_PATH];

	for (int i = 0; i < nCount; ++i)
	{
		sprintf_s(szCursorPath, MAX_PATH, "./cursor/%s.cur",  szCursorName[i]);
		HCURSOR h = ::LoadCursorFromFileA(szCursorPath);
		m_kCursorMap[szCursorName[i]] = h;
	}
}


void cgCursorManager::SetDefaultCursor( const string & cursor )
{
	m_hDefaultCursor = GetCursor(cursor);
}

void cgCursorManager::SetCursor( const string& cursor )
{
	m_hCurCursor = GetCursor(cursor);
}
void cgCursorManager::Reset()
{
	m_bShowCursor = true;
	m_hCurCursor = m_hDefaultCursor;
}

HCURSOR cgCursorManager::GetCursor( const string& cursor )
{
	cgCursorMap::iterator it = m_kCursorMap.find(cursor);
	if (it != m_kCursorMap.end())
	{
		return it->second;
	}

	return m_hDefaultCursor;
}

void cgCursorManager::ShowCursor( bool bShow )
{
	m_bShowCursor = bShow;
}

bool cgCursorManager::IsCursorShow()
{
	return m_bShowCursor;
}

bool cgCursorManager::OnMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_SETCURSOR)
	{
		::SetCursor(m_bShowCursor?m_hCurCursor:NULL);
		return true;
	}

	return false;
}

