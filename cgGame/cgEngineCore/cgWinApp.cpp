#include "StdAfx.h"
#include "cgWinApp.h"

// --------------------------------------------------------------
#ifdef _DEBUG
#define _DEBUG_LOG_WIN_APP_
#include <iostream>
using namespace  std;
#endif

// ------------------------------------------------------------------------------------------

cgWinApp * cgWinApp::ms_pkApp = NULL;

cgWinApp * cgWinApp::GetApp()
{
	return ms_pkApp;
}

// ------------------------------------------------------------------------------------------


LRESULT CALLBACK cgWinApp::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (GetApp()->OnRawMessage(message, wParam, lParam))
		return 0;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// ------------------------------------------------------------------------------------------

cgWinApp::cgWinApp(void)
{
	m_bIsRunning = true;
	ms_pkApp = this;
}

cgWinApp::~cgWinApp(void)
{
	cgStringTable::Destroy();
	delete m_pkWindow;
}

// ----------------------------------------------------------------------------------
bool cgWinApp::Initialize( int nWidth, int nHeight, int nStyle, int nStyleEx)
{
	m_pkWindow = cgPlatform::Instance()->CreateAppWindow();
	
	if (!m_pkWindow->Initialize(nWidth, nHeight, nStyle, nStyleEx, WndProc))
		return false;

	// ×Ö·û´®Ïà¹Ø
	if (!cgStringTable::Create()->Initialize())
		return false;

	if (!cgTime::Initialize())
		return false;

	return true;
}


int cgWinApp::Run()
{
	m_pkWindow->Show(true);

	MSG msg;
	while (m_bIsRunning)
	{
#ifdef _DEBUG_LOG_WIN_APP_
	//	cout<<"<cgWinApp>:"<<"Frame Begin! Time:"<<cgTime::GetTime()<<endl;
#endif
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break ;

			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}else
		{
			OnIdle();
		}

#ifdef _DEBUG_LOG_WIN_APP_
	//	cout<<"<cgWinApp>:"<<"Frame End! Time:"<<cgTime::GetTime()<<endl;
#endif
	}

	return true;
}


void cgWinApp::Stop()
{
	m_bIsRunning = false;
}

bool cgWinApp::OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		SetFocus(GetHwnd());
		break;
	case WM_SIZE:
		{
			OnSizeChanged();
		}break;
	default:
		break;
	}
	return false;
}

cgWindow * cgWinApp::GetWindow()
{
	return m_pkWindow;
}

cgHwnd cgWinApp::GetHwnd()
{
	return m_pkWindow->GetHandle();
}

// -----------------------------------------------------------------------------
void cgWinApp::OnIdle()
{
}

int cgWinApp::GetWidth()
{
	return m_pkWindow->GetWidth();
}

int cgWinApp::GetHeight()
{
	return m_pkWindow->GetHeight();
}

void cgWinApp::SetTitle( LPCTSTR title )
{
	m_pkWindow->SetTitle(title);
}

bool cgWinApp::OnSizeChanged()
{
	return true;
}

// -----------------------------------------------------------------------------


cgWinApp * GetApp()
{
	return cgWinApp::GetApp();
}

int GetAppWidth()
{
	return GetApp()->GetWidth();
}

int GetAppHeight()
{
	return GetApp()->GetHeight();
}

cgHwnd GetAppHwnd()
{
	return GetApp()->GetHwnd();
}

cgWindow * GetAppWindow()
{
	return GetApp()->GetWindow();
}
