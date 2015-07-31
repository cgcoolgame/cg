#include "StdAfx.h"
#include "cgDownloadThread.h"
#include <tchar.h>

#include <wininet.h>
#include <assert.h>
#include <shlwapi.h>

#pragma comment(lib, "wininet.lib") 

cgDownloadThread::cgDownloadThread( LPCTSTR lpctSrcUrl, LPCTSTR lpctSavePath)
{
	_tcscpy_s(m_szUrl, CG_LONG_PATH_LEN, lpctSrcUrl);
	_tcscpy_s(m_szSavePath, CG_LONG_PATH_LEN, lpctSavePath);

	m_dwLastTime = 0;

	m_uTotalSize = 0;
	m_uDownloadSize = 0;
	m_uDownloadSpeed = 0;

	m_nDownloadResult = CG_DOWNLOAD_RESULT_SUC;
}


cgDownloadThread::~cgDownloadThread(void)
{
}

// ������������ص��̹߳�������������Ҫ�����̰߳�ȫ��
unsigned cgDownloadThread::Run()
{
	return DoDownload();
}

LPCTSTR cgDownloadThread::GetSrcUrl()
{
	return m_szUrl;
}

LPCTSTR cgDownloadThread::GetSavePath()
{
	return m_szSavePath;
}

unsigned cgDownloadThread::GetTotalSize()
{
	return m_uTotalSize;
}

unsigned cgDownloadThread::GetDownloadSize()
{
	return m_uDownloadSize;
}


unsigned cgDownloadThread::GetDownloadSpeed()
{
	return m_uDownloadSpeed;
}


int cgDownloadThread::GetDownloadResult()
{
	return m_nDownloadResult;
}


bool cgDownloadThread::ParseUrl( TCHAR * szWeb, unsigned uWebLen,
	TCHAR * szObject, unsigned uObjectLen, 
	WORD & dwPort )
{
	
	LPTSTR lpctUrl = m_szUrl;
	if (_tcsncmp(lpctUrl, TEXT("http://"), _tcslen(TEXT("http://")) ) == 0 )
	{
		// ���ǰ����http��������
		lpctUrl += _tcslen(TEXT("http://"));
	}

	LPTSTR lpctSub = _tcschr(lpctUrl, TEXT('/'));
	if (!lpctSub)
		return false;

	// url��object
	_tcscpy_s(szObject, uObjectLen, lpctSub+1);
	_tcsncpy_s(szWeb, uWebLen, lpctUrl, lpctSub-lpctUrl);

	// ����website��port
	lpctSub = _tcsrchr(szWeb, TEXT(':'));
	if (lpctSub)
	{
		// �ҵ�port
		dwPort = _ttoi(lpctSub+1);
		*lpctSub = NULL;
	}

	return true;
}


// �����Ҫ�����ﻹ��Ҫ���Ƕϵ�����������
bool cgDownloadThread::DonwloadData( HINTERNET hRequest )
{
	// ���ļ�
	HANDLE hFile = CreateFile(m_szSavePath, GENERIC_WRITE, 0, NULL, 
		OPEN_ALWAYS, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// ���波�Զϵ�����
	DWORD dwSize = SetFilePointer(hFile, 0, 0, FILE_END);

	if (dwSize > 0 && InternetSetFilePointer(hRequest, dwSize, 0, FILE_BEGIN, NULL) == INVALID_SET_FILE_POINTER)
	{
		// �ϵ�����ʧ��
		SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	}else
	{
		m_uDownloadSize = dwSize;
	}

	// �������ػ���
	char szCacheBuffer[CG_DOWNLOAD_DATA_READ_BUFFER_LEN];

	// ��ȡ����
	DWORD dwReadLen = 0;
	DWORD dwWriteLen = 0;

	while (!m_bIsStopped && m_uDownloadSize < m_uTotalSize)
	{
		if (!InternetReadFile(hRequest, szCacheBuffer, 
			CG_DOWNLOAD_DATA_READ_BUFFER_LEN, &dwReadLen) || dwReadLen == 0)
			break;

		if (!WriteFile(hFile, szCacheBuffer, dwReadLen, &dwWriteLen, NULL))
			break;

		if (!OnReadData(szCacheBuffer, dwReadLen))
			break;

		// ʵ�ʳ���С������ĳ��ȣ�˵�����ؽ�����
		if (dwReadLen <= 0)
			break;
	}
	
	// todo�����ù����߳���Ȼ����ǰ���쳣��ֹ��ʱ�����ﻹ�ǿ������ڴ�й¶�ġ�
	// ��ʱ������

	CloseHandle(hFile);
	hFile = NULL;

	return true;
}


bool cgDownloadThread::OnReadData( void * pData, unsigned uDataSize )
{
	m_uDownloadSize += uDataSize;

	DWORD dwTime = ::GetTickCount();
	if (dwTime > m_dwLastTime)
	{
		float fDeltaTime = (dwTime-m_dwLastTime)/1000.0f;
		m_uDownloadSpeed = static_cast<unsigned>(uDataSize/fDeltaTime);
		m_dwLastTime = dwTime;
	}

	return true;
}



unsigned cgDownloadThread::DoDownload()
{
	m_uTotalSize = 0;
	m_uDownloadSize = 0;
	m_dwLastTime = ::GetTickCount();
	// ���ؿ�ʼ����Ϊ��ȷ��״̬
	m_nDownloadResult = CG_DOWNLOAD_RESULT_UNDEFINED;
	// ֻҪû�м�����꣬����ʧ����
	int nFinalResult = CG_DOWNLOAD_RESULT_FAILED;

//	DeleteUrlCacheEntry(m_szUrl);

	HINTERNET hSession = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;

	do 
	{
		TCHAR szWebsite[CG_LONG_PATH_LEN];
		TCHAR szSrcObject[CG_LONG_PATH_LEN];
		WORD nPort = 80;

		// ����url
		if (!ParseUrl(szWebsite, CG_LONG_PATH_LEN,
			szSrcObject, CG_LONG_PATH_LEN, nPort))
		{
			break;
		}

		// ��������
		hSession = InternetOpen(TEXT("cgDownloadThread"), 
			INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (!hSession)
			break;

		// ������վ
		hConnect = InternetConnect(hSession,szWebsite, nPort, NULL,
			NULL, INTERNET_SERVICE_HTTP, NULL, NULL);
		if (!hConnect)
			break;

		// ���ļ�
		PCTSTR rgpszAcceptTypes[] = {_T("*/*"), NULL};
		hRequest = HttpOpenRequest(hConnect, TEXT("GET"), szSrcObject,
			TEXT("HTTP/1.1"), NULL, rgpszAcceptTypes, 
			/*INTERNET_FLAG_RELOAD*/0, 0);
		if (!hRequest)
			break;

		// ������ļ�
		if (!HttpSendRequest(hRequest, NULL, NULL, NULL, NULL))
			break;

		// ����鿴�޸�ʱ�䣬�Դ����ж��ļ��Ƿ���ڣ���һ������ʡ��
		DWORD dwReadLen = MAX_PATH;
		TCHAR szReadBuff[MAX_PATH];
		if (!HttpQueryInfo(hRequest, HTTP_QUERY_LAST_MODIFIED, 
			szReadBuff, &dwReadLen, NULL))
			break;

		// ��ѯ�ļ��ܴ�С
		memset(szReadBuff, 0, sizeof(szReadBuff));
		dwReadLen = MAX_PATH;
		if (!HttpQueryInfo(hRequest,HTTP_QUERY_CONTENT_LENGTH, 
			szReadBuff, &dwReadLen, NULL))
			break;

		// �����ܳ���
		m_uTotalSize = _ttoi(szReadBuff);

		// ��ȡ����
		if (!DonwloadData(hRequest))
			break;

		// ���еĶ����������ˣ�����Ϊ�ɹ�
		nFinalResult = CG_DOWNLOAD_RESULT_SUC;

	} while (false);

	// �����������ؽ��
	m_nDownloadResult = nFinalResult;

	if (hRequest)
		InternetCloseHandle(hRequest);
	if (hConnect)
		InternetCloseHandle(hConnect);
	if (hSession)
		InternetCloseHandle(hSession);

	return 0;
}
