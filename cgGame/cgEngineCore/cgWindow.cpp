#include "StdAfx.h"
#include "cgWindow.h"


LRESULT CALLBACK cgWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

// ----------------------------------------------------------------------------------

cgWindow::cgWindow()
{
	m_hWnd = NULL;
}

cgWindow::~cgWindow(void)
{
}

// ----------------------------------------------------------------------------------
bool cgWindow::Initialize( int nWidth, int nHeight, int nStyle, int nStyleEx, WNDPROC wndProc)
{
	MyRegisterClass(wndProc);

	if (!MyCreateWindow( nStyle, nStyleEx))
		return false;

	SetSize(nWidth, nHeight);

	return true;
}

// ----------------------------------------------------------------------



cgHwnd cgWindow::GetHandle()
{
	return m_hWnd;
}

// --------------------------------------------------------------------------
ATOM cgWindow::MyRegisterClass(WNDPROC wndProc)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
	wcex.lpfnWndProc	= wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= NULL;
	wcex.hIcon			= NULL/*LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLEWINGAME))*/;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_SIMPLEWINGAME);
	wcex.lpszClassName	= cgAPPWINNAME;
	wcex.hIconSm		= NULL/* LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL))*/;

	return RegisterClassEx(&wcex);
}

bool cgWindow::MyCreateWindow(int nStyle, int nStyleEx)
{
	m_hWnd = CreateWindowEx(nStyleEx, cgAPPWINNAME, cgAPPWINNAME,nStyle,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
		NULL, NULL, NULL, NULL);

	return m_hWnd != NULL;
}

void cgWindow::Show(bool bShow)
{
	ShowWindow(m_hWnd, bShow?SW_SHOWNORMAL:SW_HIDE);
	UpdateWindow(m_hWnd);
}


// -----------------------------------------------------------------------

void cgWindow::SetSize( int nWidth, int nHeight )
{
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);

	RECT rect;
	::SetRect(&rect, 0, 0, nWidth, nHeight);
	::AdjustWindowRect(&rect, dwStyle, FALSE);

	RECT rtContainer   =   {0};  
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)&rtContainer,0);

	::MoveWindow(m_hWnd, (rtContainer.right-rect.right+rect.left)/ 2, 
		(rtContainer.bottom -rect.bottom+rect.top)/2, 
		rect.right-rect.left, rect.bottom-rect.top, TRUE);
}

void cgWindow::SetTitle( LPCTSTR lpctTitle )
{
	::SetWindowText(m_hWnd, lpctTitle);
}

// ------------------------------------------------------------------
int cgWindow::GetWidth()
{
	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	return rect.right-rect.left;
}

int cgWindow::GetHeight()
{
	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	return rect.bottom-rect.top;
}

void cgWindow::SetIcon( HICON hIcon, int nIconType)
{
	SendMessage(m_hWnd, WM_SETICON, nIconType, (LPARAM)hIcon);
}

void cgWindow::SetPos( int x, int y )
{
	RECT rect;
	::GetWindowRect(m_hWnd, &rect);
	::MoveWindow(m_hWnd, x, y, rect.right-rect.left, rect.bottom-rect.top, TRUE);
}
