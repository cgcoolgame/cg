#include "StdAfx.h"
#include "cgGdiplusApp.h"
#include "cgGdiplusRender.h"
#include "cgUIManager.h"
#include "cgCursorManager.h"

#ifndef _GDIPLUS_APP_USE_CUSTOM_CURSOR_
#define _GDIPLUS_APP_USE_CUSTOM_CURSOR_
#endif

cgGdiplusApp::cgGdiplusApp(void)
{
	m_bIsInitialized = false;
}

cgGdiplusApp::~cgGdiplusApp(void)
{
	cgUIManager::Destroy();
	cgGdiplusRender::Destroy();
}

bool cgGdiplusApp::Initialize( int nWidth, int nHeight, int nStyle, int nStyleEx )
{
	if (!cgWinApp::Initialize(nWidth, nHeight, nStyle, nStyleEx))
		return false;

	if (!cgGdiplusRender::Create()->Initialize(GetHwnd(), nWidth, nHeight))
		return false;

	if (!cgUIManager::Create()->Initialize(GetHwnd(), nWidth, nHeight))
		return false;

#ifdef _GDIPLUS_APP_USE_CUSTOM_CURSOR_
	if (!cgCursorManager::Create()->Initialize())
		return false;
#endif

	if (!DoInitialize())
		return false;

	m_bIsInitialized = true;

	return m_bIsInitialized;
}

bool cgGdiplusApp::OnRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (!m_bIsInitialized)
		return false;

#ifdef _GDIPLUS_APP_USE_CUSTOM_CURSOR_
	if (cgCursorManager::Get()->OnMessage(message, wParam, lParam))
		return true;
#endif

	if (cgUIManager::Get()->OnMessage(message, wParam, lParam))
		return true;

	if (DoProcessRawMessage(message, wParam, lParam))
		return true;

	return cgWinApp::OnRawMessage(message, wParam, lParam);
}


bool cgGdiplusApp::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (message == WM_LBUTTONDOWN )
	{
		// 允许拖动
		PostMessage(GetHwnd(), WM_NCLBUTTONDOWN, HTCAPTION, wParam);
	}

	return false;
}


void cgGdiplusApp::OnIdle()
{
	float fTime = cgTime::GetTime();

	// 更新
	Update(fTime);

	// 渲染
	Render();

	// 50帧
	Sleep(20);
}

void cgGdiplusApp::Update(float fTime)
{
	cgUIManager::Get()->Update(fTime);
}

void cgGdiplusApp::Render()
{
	cgUIManager::Get()->Render(false);
}

bool cgGdiplusApp::DoInitialize()
{
	return true;
}
