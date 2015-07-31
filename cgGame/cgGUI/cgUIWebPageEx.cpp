#include "StdAfx.h"
#include "cgUIWebPageEx.h"
#include "cgUIManager.h"
#include "cgEngineTools.h"
#include "cgUIRender.h"
#include <windows.h>

cgUIWebPageEx::cgUIWebPageEx(void)
{
	m_pkBrower = NULL;
	m_nLeftOffset = 0;
	m_nRightOffset = 0;
	m_nTopOffset = 0;
	m_nBottomOffset = 0;
}


cgUIWebPageEx::~cgUIWebPageEx(void)
{
	if (m_pkBrower)
		m_pkBrower->Release();
}

bool cgUIWebPageEx::Initialize( cgHwnd hMainWnd, int x, int y, int w, int h )
{
	SetLocalRect(x, y, w, h);

	int nWebX = x;
	int nWebY = y;
	cgUIManager::Get()->UIPointToScreen(nWebX, nWebY);

	RECT webRect = {0, 0, w, h};
	LPOLESTR pszName=OLESTR("shell.Explorer.2");  

	m_kContainer.Create((HWND)hMainWnd, webRect, 0,WS_POPUP);
	m_kContainer.CreateControl(pszName);
	m_kContainer.QueryControl(__uuidof(IWebBrowser2),(void**)&m_pkBrower);
	m_kContainer.MoveWindow(nWebX, nWebY, w, h, TRUE);
	m_kContainer.ShowWindow(SW_SHOW);

	return true;
}


void cgUIWebPageEx::SetWebpageOffset( int leftOffset, int rightOffset, 
	int topOffset, int bottomOffset )
{
	m_nLeftOffset = leftOffset;
	m_nRightOffset = rightOffset;
	m_nTopOffset = topOffset;
	m_nBottomOffset = bottomOffset;

	AdjustWebRect();
}


bool cgUIWebPageEx::Navigate( LPCTSTR url, bool bForceRefresh  )
{
	m_strUrl = url;

	VARIANT varMyURL;  
	VariantInit(&varMyURL);  
	varMyURL.vt = VT_BSTR;   
	varMyURL.bstrVal = SysAllocString(url);  
	m_pkBrower-> Navigate2(&varMyURL,0,0,0,0);
	VariantClear(&varMyURL);

	if (bForceRefresh)
		return Refresh();

	return true;
}


const cgString& cgUIWebPageEx::GetCurUrl()
{
	return m_strUrl;
}



bool cgUIWebPageEx::Refresh()
{
	VARIANT varFlag;
	VariantInit(&varFlag);
	varFlag.vt = VT_I4;
	varFlag.intVal = REFRESH_COMPLETELY;
	m_pkBrower->Refresh2(&varFlag);
	VariantClear(&varFlag);
	ReportDirty();

	return true;
}

// --------------------------------------------------------------------------------------------

void cgUIWebPageEx::SetVisible( bool bVisible )
{
	cgUIWidget::SetVisible(bVisible);
	m_kContainer.ShowWindow(bVisible?SW_SHOW:SW_HIDE);
}


bool cgUIWebPageEx::OnMessage( cgUIMsg msg, unsigned wparam, unsigned lparam )
{
	if (msg == WM_MOVING || msg == WM_MOVE )
	{
		AdjustWebRect();
	}

	return cgUIWidget::OnMessage(msg, wparam, lparam);
}

void cgUIWebPageEx::AdjustWebRect()
{
	int nWebX = GetX();
	int nWebY = GetY();
	cgUIManager::Get()->UIPointToScreen(nWebX, nWebY);

	if (m_kContainer)
	{
		m_kContainer.MoveWindow(nWebX+m_nLeftOffset, 
		nWebY+m_nRightOffset,
		GetWidth()-m_nLeftOffset-m_nRightOffset, 
		GetHeight()-m_nTopOffset-m_nBottomOffset,
		TRUE);
	}
}

void cgUIWebPageEx::OnPositionChanged()
{
	AdjustWebRect();
}

void cgUIWebPageEx::OnSizeChanged()
{
	AdjustWebRect();
}
