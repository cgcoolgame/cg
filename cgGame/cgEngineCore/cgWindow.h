////////////////////////////////////////////////
//	FileName:		CGWindow.h
//	Author:			Master
//	Date:			2014.3.6
//	Description:	һ���򵥵Ĵ��ڷ�װ��
//	mark:			���е����鶼����һ����ͣ������ݽ�Ҳ��һ����Ȥ
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

	// ��ʼ�������Ҵ���һ��ָ����С�Ĵ���
	virtual bool Initialize(int nWidth, int nHeight, int nStyle, int nStyleEx, WNDPROC wndProc);

	// ��ȡ������
	cgHwnd GetHandle();

	// ���ô��ڴ�С
	void SetSize(int nWidth, int nHeight);

	// ��͸�
	int GetWidth();
	int GetHeight();

	// ���ñ���
	void SetTitle(LPCTSTR lpctTitle);

	// ��ʾ
	void Show(bool bShow);

	// �ƶ�
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
