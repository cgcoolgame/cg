#include "StdAfx.h"
#include "cgStringTable.h"


cgStringTable::cgStringTable(void)
{
	m_pCharBuffer = NULL;
	m_nCharBufferLen = 0;

	m_pWCharBuffer = NULL;
	m_nWCharBufferLen = 0;
}


cgStringTable::~cgStringTable(void)
{
	delete[] m_pCharBuffer;
	delete[] m_pWCharBuffer;
}


bool cgStringTable::Initialize()
{
	return true;
}


const char * cgStringTable::UnicodeToAcp( const wchar_t * str )
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);;
	if (m_nCharBufferLen < nLen)
	{
		m_nCharBufferLen = nLen;
		// 看上一次的长度够不够，不够就重新分配
		if (m_pCharBuffer)
			delete[] m_pCharBuffer;
		m_pCharBuffer = new char[m_nCharBufferLen];
	}

	WideCharToMultiByte(CP_ACP, 0, str, -1, m_pCharBuffer, m_nCharBufferLen, NULL, NULL);
	return m_pCharBuffer;
}

const wchar_t * cgStringTable::AcpToUnicode( const char * str )
{
	if (!str)
		return L"";

	int nLen = strlen(str) + 1;
	if (m_nWCharBufferLen < nLen)
	{
		m_nWCharBufferLen = nLen;
		// 看上一次的长度够不够，不够就重新分配
		if (m_pWCharBuffer)
			delete[] m_pWCharBuffer;
		m_pWCharBuffer = new wchar_t[m_nWCharBufferLen];
	}

	MultiByteToWideChar(CP_ACP, 0, str, nLen, m_pWCharBuffer, nLen);
	return m_pWCharBuffer;
}

const char * cgStringTable::UnicodeToUtf8( const wchar_t * str )
{
	int nLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);;
	if (m_nCharBufferLen < nLen)
	{
		m_nCharBufferLen = nLen;
		// 看上一次的长度够不够，不够就重新分配
		if (m_pCharBuffer)
			delete[] m_pCharBuffer;
		m_pCharBuffer = new char[m_nCharBufferLen];
	}

	WideCharToMultiByte(CP_UTF8, 0, str, -1, m_pCharBuffer, m_nCharBufferLen, NULL, NULL);
	return m_pCharBuffer;
}

const wchar_t * cgStringTable::Utf8ToUnicode( const char * str )
{
	if (!str)
		return L"";

	int nLen = strlen(str) + 1;
	if (m_nWCharBufferLen < nLen)
	{
		m_nWCharBufferLen = nLen;
		// 看上一次的长度够不够，不够就重新分配
		if (m_pWCharBuffer)
			delete[] m_pWCharBuffer;
		m_pWCharBuffer = new wchar_t[m_nWCharBufferLen];
	}

	MultiByteToWideChar(CP_UTF8, 0, str, nLen, m_pWCharBuffer, nLen);
	return m_pWCharBuffer;
}

// ------------------------------------------------

const TCHAR * cgXAcp2cgTxt( const char * str )
{
#ifdef _UNICODE
	return cgStringTable::Get()->AcpToUnicode(str);
#else
	return str;
#endif
}

const TCHAR * cgXUtf8TocgTxt( const char * str )
{
#ifdef _UNICODE
	return cgStringTable::Get()->Utf8ToUnicode(str);
#else
	return str;
#endif
}
