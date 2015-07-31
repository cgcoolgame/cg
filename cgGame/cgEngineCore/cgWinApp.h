////////////////////////////////////////////////
//	FileName:		cgWinApp.h
//	Author:			Master
//	Date:			2013.09.18
//	Description:	һ���򵥵ĳ�����
//	mark:			���е����鶼����һ����ͣ������ݽ�Ҳ��һ����Ȥ
////////////////////////////////////////////////

// ����ļ�ͷ [9/19/2013 Master]

#ifndef cgWinApp_h__
#define cgWinApp_h__

#include "cgPlatform.h"
#include "cgStringTable.h"
#include "cgWindow.h"
#include "cgTime.h"
#include "cgMath.h"

// APP���ڵĿ��
class cgWinApp
{
public:
	cgWinApp();
	virtual ~cgWinApp(void);

public:
	// ��ʼ�������Ҵ���һ��ָ����С�Ĵ��ڣ�ͬʱ�ƶ�style��ex_style
	virtual bool Initialize(int nWidth, int nHeight, int nStyle, int nStyleEx);

	// ��ѭ��
	virtual int Run();

	// ֹͣ����������ֹͣ�����ڱ�֡������ֹͣ
	virtual void Stop();

	// ��Ϣ������
	virtual bool OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam);

	// ��ȡ��ǰ����
	cgWindow * GetWindow();
	cgHwnd GetHwnd();

	// ��ȡ���ڵĴ�С
	int GetWidth();
	int GetHeight();

	void SetTitle(LPCTSTR title);

public:
	static cgWinApp * GetApp();

	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
protected:
	// ����ʱ����������
	virtual void OnIdle();
	virtual bool OnSizeChanged();

protected:
	cgWindow * m_pkWindow;
	bool m_bIsRunning;
private:
	static cgWinApp * ms_pkApp;
};

// ������һЩ���ߺ��������ٴ��볤��
cgWinApp * GetApp();
int GetAppWidth();
int GetAppHeight();
cgHwnd GetAppHwnd();
cgWindow * GetAppWindow();

#endif // GameApp_h__
