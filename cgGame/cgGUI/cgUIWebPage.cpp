#include "StdAfx.h"
#include "cgUIWebPage.h"
#include "cgUIManager.h"
#include "cgEngineTools.h"
#include "cgUIRender.h"
#include <windows.h>

cgUIWebPage::cgUIWebPage(void)
{
	m_pkBrower = NULL;
	m_pkRenderSurface = NULL;

	m_fFreshTimeSpace = 0.01f;
	m_fLastUpdateTime = 0.0f;
}


cgUIWebPage::~cgUIWebPage(void)
{
	if (m_pkBrower)
		m_pkBrower->Release();

	delete m_pkRenderSurface;
}

bool cgUIWebPage::Initialize( cgHwnd hMainWnd, int x, int y, int w, int h )
{
	SetLocalRect(x, y, w, h);

	int nWebX = x;
	int nWebY = y;
	cgUIManager::Get()->UIPointToClient(nWebX, nWebY);

	RECT webRect = {nWebX, nWebY, nWebX+w, nWebY+h};
	LPOLESTR pszName=OLESTR("shell.Explorer.2");  

	m_kContainer.Create(hMainWnd, webRect, 0,WS_CHILD |WS_VISIBLE);  
	m_kContainer.CreateControl(pszName);  
	m_kContainer.QueryControl(__uuidof(IWebBrowser2),(void**)&m_pkBrower);

	m_pkRenderSurface = cgUIRender::GetRender()->CreateUISurface(w, h);

	return true;
}

bool cgUIWebPage::Navigate( LPCTSTR url , bool bForceRefresh)
{
	VARIANT varMyURL;  
	VariantInit(&varMyURL);  
	varMyURL.vt = VT_BSTR;   
	varMyURL.bstrVal = SysAllocString(url);  
	m_pkBrower-> Navigate2(&varMyURL,0,0,0,0);
	VariantClear(&varMyURL);
	ReportDirty();

	if (bForceRefresh)
		return Refresh();

	return true;
}

bool cgUIWebPage::Refresh()
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


void cgUIWebPage::SetSize( int w, int h )
{
	cgUIWidget::SetSize(w, h);

	AdjustWebRect();
}

void cgUIWebPage::Move( int x, int y )
{
	cgUIWidget::Move(x, y);

	AdjustWebRect();

}

void cgUIWebPage::SetFreshTimeSpace( float fTimeSpace )
{
	m_fFreshTimeSpace = fTimeSpace;
}

float cgUIWebPage::GetFreshTimeSpace()
{
	return m_fFreshTimeSpace;
}

void cgUIWebPage::Update( float fTime )
{
	cgUIWidget::Update(fTime);

	if (fTime - m_fLastUpdateTime > m_fFreshTimeSpace)
	{
		m_fLastUpdateTime = fTime;

		ReportDirty();
	}
}

void cgUIWebPage::DrawBackPic( const cgRectF& clipRect )
{
	cgUIWidget::DrawBackPic(clipRect);

	// 等于则全部刷新，否则只绘制已经保存好的局部
	if (cgXCompareRect(clipRect, m_kRect) == cgRectCmpResult_Equal)
	{
		if (!m_pkBrower || !m_pkRenderSurface)
			return ;

		RECT kRect;
		::SetRect(&kRect, 0, 0, m_kRect.w, m_kRect.h);

		HDC hdc = (HDC)m_pkRenderSurface->GetContent();
		::OleDraw(m_pkBrower, DVASPECT_CONTENT, hdc, &kRect);
		m_pkRenderSurface->ReleaseContent((void*)hdc);
	}

	cgUIRender::GetRender()->PresentUISurface(m_pkRenderSurface, 
		cgRectF(clipRect.x-m_kRect.x, clipRect.y-m_kRect.y, clipRect.w, clipRect.h),
		clipRect);
}

void cgUIWebPage::AdjustWebRect()
{
	int nWebX = GetX();
	int nWebY = GetY();

	cgUIManager::Get()->UIPointToClient(nWebX, nWebY);

	if (m_kContainer)
		m_kContainer.MoveWindow(nWebX, nWebY, GetWidth(), GetHeight(), TRUE);
}

