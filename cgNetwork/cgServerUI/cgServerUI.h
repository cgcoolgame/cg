
// cgServerUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcgServerUIApp:
// �йش����ʵ�֣������ cgServerUI.cpp
//

class CcgServerUIApp : public CWinApp
{
public:
	CcgServerUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcgServerUIApp theApp;