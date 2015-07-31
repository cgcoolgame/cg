#include "StdAfx.h"
#include "CGFileDownloader.h"
#include <tchar.h>
#include <wininet.h>
#include <assert.h>
#include <shlwapi.h>

#pragma comment(lib, "wininet.lib") 

#define CG_DOWNLOAD_BUFF_LEN (128*1024)


CCGFileDownloader::CCGFileDownloader(void)
{
	m_enmDownloadState = enmCGDownloadStateUnstart;
	m_dwTotalFileSize = 0;
	m_dwDownloadedSize = 0;

	m_szWebSite[0] = NULL;
	m_szDestFilePath[0] = NULL;
	m_szSrcUrl[0] = NULL;
	m_iPort = INTERNET_DEFAULT_HTTP_PORT;

	m_hDownloadThread = NULL;
}


CCGFileDownloader::~CCGFileDownloader(void)
{
	if (m_hDownloadThread)
	{
		Stop();
		WaitForSingleObject(m_hDownloadThread, 1000);
		CloseHandle(m_hDownloadThread);
		m_hDownloadThread = NULL;
	}
}

// -----------------------------------------------------------------------
void CCGFileDownloader::Download( LPCTSTR lpctWeb, LPCTSTR lpctSrcUrl, LPCTSTR lpctDestPath )
{
	SetWebSite(lpctWeb);
	_tcscpy_s(m_szSrcUrl, CG_DOWNLOAD_MAX_FILE_PATH_LEN, lpctSrcUrl);
	_tcscpy_s(m_szDestFilePath, CG_DOWNLOAD_MAX_FILE_PATH_LEN, lpctDestPath);

	m_enmDownloadState = enmCGDownloadStateDownloading;

	m_hDownloadThread = CreateThread(NULL, 
		NULL, &CCGFileDownloader::DoDownload, this, 0, NULL);

	if (!m_hDownloadThread )
		m_enmDownloadState = enmCGDownloadStateFailed;
}

void CCGFileDownloader::SetWebSite( LPCTSTR lpctWebsite )
{
	LPCTSTR lpctSub = wcsrchr(lpctWebsite, TEXT(':'));
	if (lpctSub)
	{
		m_iPort = _ttoi(lpctSub+1);
		_tcsncpy_s(m_szWebSite, CG_DOWNLOAD_MAX_FILE_PATH_LEN, lpctWebsite, lpctSub-lpctWebsite);
	}else
	{
		_tcscpy_s(m_szWebSite, CG_DOWNLOAD_MAX_FILE_PATH_LEN, lpctWebsite);
	}
}

void CCGFileDownloader::SetState( enmCGDownloadState enmState )
{
	m_enmDownloadState = enmState;
}

void CCGFileDownloader::SetTotalSize(DWORD dwSize)
{
	m_dwTotalFileSize = dwSize;
}


void CCGFileDownloader::SetDownloadedSize(DWORD dwSize)
{
	m_dwDownloadedSize = dwSize;
}

void CCGFileDownloader::Stop()
{
	m_enmDownloadState = enmCGDownloadStateStopped;
}

void CCGFileDownloader::GetDownloadDetail( enmCGDownloadState& enmState, DWORD& dwTotalSize, DWORD& dwDownloadSize )
{
	enmState = m_enmDownloadState;
	dwTotalSize = m_dwTotalFileSize;
	dwDownloadSize = m_dwDownloadedSize;
}

// ------------------------------------------------------------------------------------

DWORD WINAPI CCGFileDownloader::DoDownload( void * pParam )
{
	CCGFileDownloader * pkDownloader = (CCGFileDownloader*)pParam;
	if (!pkDownloader)
	{
		return -1;
	}
	// 开启网络
	HINTERNET hSession = InternetOpen(TEXT("CGDownload"), 
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hSession)
	{
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}

	// 连接网站
	HINTERNET hConnect = InternetConnect(hSession,
		pkDownloader->m_szWebSite, pkDownloader->m_iPort, NULL,
		NULL, INTERNET_SERVICE_HTTP, NULL, NULL);
	if (!hConnect)
	{
		InternetCloseHandle(hSession);
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}

	PCTSTR rgpszAcceptTypes[] = {_T("*/*"), NULL};
	// 打开文件
	HINTERNET hRequest = HttpOpenRequest(hConnect, TEXT("GET"), pkDownloader->m_szSrcUrl,
		TEXT("HTTP/1.1"), NULL, rgpszAcceptTypes, INTERNET_FLAG_RELOAD|INTERNET_FLAG_KEEP_CONNECTION, 0);
	if (!hRequest)
	{
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hSession);
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}

	// 请求打开文件
	BOOL bRequestRet = HttpSendRequest(hRequest, NULL, NULL, NULL, NULL);
	if (!bRequestRet)
	{
		DWORD dwErr = GetLastError();
		InternetCloseHandle( hConnect );
		InternetCloseHandle(hSession);
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}

	DWORD dwBufLen = CG_DOWNLOAD_BUFF_LEN;
	TCHAR szBuff[CG_DOWNLOAD_BUFF_LEN];
	memset(szBuff, 0, sizeof(szBuff));
	BOOL bQueryVerify = HttpQueryInfo(hRequest, HTTP_QUERY_LAST_MODIFIED, szBuff, &dwBufLen, NULL);
	if (!bQueryVerify)
	{
		// 如果查询修改信息失败的话，说明文件不存在
		InternetCloseHandle( hRequest );
		InternetCloseHandle( hConnect );
		InternetCloseHandle(hSession);
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}

	memset(szBuff, 0, sizeof(szBuff));
	dwBufLen = CG_DOWNLOAD_BUFF_LEN;
	BOOL bQueryLenRet = HttpQueryInfo(hRequest,HTTP_QUERY_CONTENT_LENGTH,szBuff, &dwBufLen, NULL);
	if (!bQueryLenRet)
	{
		InternetCloseHandle( hRequest );
		InternetCloseHandle( hConnect );
		InternetCloseHandle(hSession);
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}
	pkDownloader->SetTotalSize(_wtoi(szBuff));

	DWORD dwRequest = CG_DOWNLOAD_BUFF_LEN; // 请求下载的字节数
	DWORD dwRead = 0; // 实际读出的字节数
	DWORD dwWrite = 0;

	HANDLE hFile = CreateFile(pkDownloader->m_szDestFilePath, GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, NULL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		InternetCloseHandle( hRequest );
		InternetCloseHandle( hConnect );
		InternetCloseHandle(hSession);
		pkDownloader->SetState(enmCGDownloadStateFailed);
		return -1;
	}
	while (enmCGDownloadStateDownloading == pkDownloader->m_enmDownloadState)
	{
		BOOL bRet = InternetReadFile(hRequest, szBuff, dwRequest, &dwRead);
		if (!bRet || !dwRead )
			break;

		WriteFile(hFile, szBuff, dwRead, &dwWrite, NULL);
		pkDownloader->m_dwDownloadedSize += dwRead;
	}
	CloseHandle(hFile);

	InternetCloseHandle( hRequest );
	InternetCloseHandle( hConnect );
	InternetCloseHandle( hSession );

	pkDownloader->SetState(enmCGDownloadStateFinished);

	return 0;
}






