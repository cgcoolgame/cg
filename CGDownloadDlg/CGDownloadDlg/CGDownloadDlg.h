
// CGDownloadDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCGDownloadDlgApp:
// �йش����ʵ�֣������ CGDownloadDlg.cpp
//

class CCGDownloadDlgApp : public CWinApp
{
public:
	CCGDownloadDlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCGDownloadDlgApp theApp;