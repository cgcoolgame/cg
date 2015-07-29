#include "StdAfx.h"
#include "cgNetworkString.h"

//---------------------------------------------------------------------
// �����unicode,txt�ļ���UTF-8���룬ConvertTxtStringҲ���ǰ�UTF-8����ת��unicode
LPCTSTR UTF8ToUnicode(const char* str)
{
#ifdef UNICODE
	// ��ȫ�־�̬��������
	static TCHAR* pcBuffer = NULL;
	static int nBufferLen = 0;

	int nLen = strlen(str) + 1;
	if (nBufferLen < nLen)
	{
		// ����һ�εĳ��ȹ����������������·���
		if (pcBuffer)
			delete[] pcBuffer;
		pcBuffer = new TCHAR[nLen];
		nBufferLen = nLen;
	}

	MultiByteToWideChar(CP_UTF8, 0, str, nLen, pcBuffer, nLen);
	return pcBuffer;
#else
	return str;
#endif
}

const char* Unicode2UTF8(LPCTSTR str)
{
#ifdef UNICODE
	// ��ȫ�־�̬��������
	static char* pcBuffer = NULL;
	static int nBufferLen = 0;

	int nLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);;
	if (nBufferLen < nLen)
	{
		// ����һ�εĳ��ȹ����������������·���
		if (pcBuffer)
			delete[] pcBuffer;
		pcBuffer = new char[nLen];
		nBufferLen = nLen;
	}

	WideCharToMultiByte(CP_UTF8, 0, str, -1, pcBuffer, nLen, NULL, NULL);
	return pcBuffer;
#else
	return str;
#endif
}
