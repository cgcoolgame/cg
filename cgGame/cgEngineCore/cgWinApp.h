////////////////////////////////////////////////
//	FileName:		cgWinApp.h
//	Author:			Master
//	Date:			2013.09.18
//	Description:	一个简单的程序框架
//	mark:			所有的事情都不能一蹴而就，不断演进也是一种乐趣
////////////////////////////////////////////////

// 添加文件头 [9/19/2013 Master]

#ifndef cgWinApp_h__
#define cgWinApp_h__

#include "cgPlatform.h"
#include "cgStringTable.h"
#include "cgWindow.h"
#include "cgTime.h"
#include "cgMath.h"

// APP窗口的框架
class cgWinApp
{
public:
	cgWinApp();
	virtual ~cgWinApp(void);

public:
	// 初始化，并且创建一个指定大小的窗口，同时制定style和ex_style
	virtual bool Initialize(int nWidth, int nHeight, int nStyle, int nStyleEx);

	// 主循环
	virtual int Run();

	// 停止，不会立刻停止而是在本帧结束后停止
	virtual void Stop();

	// 消息处理函数
	virtual bool OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// 获取当前窗口
	cgWindow * GetWindow();
	cgHwnd GetHwnd();

	// 获取窗口的大小
	int GetWidth();
	int GetHeight();

	void SetTitle(LPCTSTR title);

public:
	static cgWinApp * GetApp();

	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
protected:
	// 空闲时刻做的事情
	virtual void OnIdle();
	virtual bool OnSizeChanged();

protected:
	cgWindow * m_pkWindow;
	bool m_bIsRunning;
private:
	static cgWinApp * ms_pkApp;
};

// 下面是一些工具函数，减少代码长度
cgWinApp * GetApp();
int GetAppWidth();
int GetAppHeight();
cgHwnd GetAppHwnd();
cgWindow * GetAppWindow();

#endif // GameApp_h__
