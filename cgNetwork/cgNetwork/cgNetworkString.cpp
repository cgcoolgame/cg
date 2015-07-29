#include "StdAfx.h"
#include "cgNetworkString.h"

//---------------------------------------------------------------------
// 如果用unicode,txt文件用UTF-8编码，ConvertTxtString也就是把UTF-8编码转换unicode
LPCTSTR UTF8ToUnicode(const char* str)
{
#ifdef UNICODE
	// 用全局静态变量来存
	static TCHAR* pcBuffer = NULL;
	static int nBufferLen = 0;

	int nLen = strlen(str) + 1;
	if (nBufferLen < nLen)
	{
		// 看上一次的长度够不够，不够就重新分配
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
	// 用全局静态变量来存
	static char* pcBuffer = NULL;
	static int nBufferLen = 0;

	int nLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);;
	if (nBufferLen < nLen)
	{
		// 看上一次的长度够不够，不够就重新分配
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
