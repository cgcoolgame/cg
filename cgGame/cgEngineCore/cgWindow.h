////////////////////////////////////////////////
//	FileName:		CGWindow.h
//	Author:			Master
//	Date:			2014.3.6
//	Description:	一个简单的窗口封装类
//	mark:			所有的事情都不能一蹴而就，不断演进也是一种乐趣
////////////////////////////////////////////////

#ifndef cgWindow_h__
#define cgWindow_h__

#include "cgDefine.h"

#define cgAPPWINNAME TEXT("cgAppWin")

class cgWindow
{
public:
	cgWindow();

	~cgWindow(void);
public:

	// 初始化，并且创建一个指定大小的窗口
	virtual bool Initialize(int nWidth, int nHeight, int nStyle, int nStyleEx, WNDPROC wndProc);

	// 获取主窗口
	cgHwnd GetHandle();

	// 设置窗口大小
	void SetSize(int nWidth, int nHeight);

	// 宽和高
	int GetWidth();
	int GetHeight();

	// 设置标题
	void SetTitle(LPCTSTR lpctTitle);

	// 显示
	void Show(bool bShow);

	// 移动
	void SetPos(int x, int y);
	// 
	//************************************
	// Method:    SetIcon
	// FullName:  CCGWindow::SetIcon
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: HICON hIcon
	// Parameter: int nIconType ICON_BIG ICON_SMALL
	//************************************
	void SetIcon(HICON hIcon, int nIconType);
protected:

	ATOM MyRegisterClass( WNDPROC wndProc);
	bool MyCreateWindow(int nStyle, int nStyleEx);

protected:
	cgHwnd m_hWnd;
};

#endif // CGWin_h__
