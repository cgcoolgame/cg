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

// 这个函数是重载的线程工作函数，所以要考虑线程安全性
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
		// 如果前面有http，则跳过
		lpctUrl += _tcslen(TEXT("http://"));
	}

	LPTSTR lpctSub = _tcschr(lpctUrl, TEXT('/'));
	if (!lpctSub)
		return false;

	// url和object
	_tcscpy_s(szObject, uObjectLen, lpctSub+1);
	_tcsncpy_s(szWeb, uWebLen, lpctUrl, lpctSub-lpctUrl);

	// 分离website和port
	lpctSub = _tcsrchr(szWeb, TEXT(':'));
	if (lpctSub)
	{
		// 找到port
		dwPort = _ttoi(lpctSub+1);
		*lpctSub = NULL;
	}

	return true;
}


// 如果必要，这里还需要考虑断点续传的问题
bool cgDownloadThread::DonwloadData( HINTERNET hRequest )
{
	// 打开文件
	HANDLE hFile = CreateFile(m_szSavePath, GENERIC_WRITE, 0, NULL, 
		OPEN_ALWAYS, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 下面尝试断点续传
	DWORD dwSize = SetFilePointer(hFile, 0, 0, FILE_END);

	if (dwSize > 0 && InternetSetFilePointer(hRequest, dwSize, 0, FILE_BEGIN, NULL) == INVALID_SET_FILE_POINTER)
	{
		// 断点续传失败
		SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	}else
	{
		m_uDownloadSize = dwSize;
	}

	// 创建下载缓冲
	char szCacheBuffer[CG_DOWNLOAD_DATA_READ_BUFFER_LEN];

	// 读取数据
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

		// 实际长度小于请求的长度，说明下载结束了
		if (dwReadLen <= 0)
			break;
	}
	
	// todo：当该工作线程自然结束前，异常终止的时候，这里还是可能有内存泄露的。
	// 暂时放这里

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
	// 下载开始，置为不确定状态
	m_nDownloadResult = CG_DOWNLOAD_RESULT_UNDEFINED;
	// 只要没有坚持走完，都是失败了
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

		// 解析url
		if (!ParseUrl(szWebsite, CG_LONG_PATH_LEN,
			szSrcObject, CG_LONG_PATH_LEN, nPort))
		{
			break;
		}

		// 开启网络
		hSession = InternetOpen(TEXT("cgDownloadThread"), 
			INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (!hSession)
			break;

		// 连接网站
		hConnect = InternetConnect(hSession,szWebsite, nPort, NULL,
			NULL, INTERNET_SERVICE_HTTP, NULL, NULL);
		if (!hConnect)
			break;

		// 打开文件
		PCTSTR rgpszAcceptTypes[] = {_T("*/*"), NULL};
		hRequest = HttpOpenRequest(hConnect, TEXT("GET"), szSrcObject,
			TEXT("HTTP/1.1"), NULL, rgpszAcceptTypes, 
			/*INTERNET_FLAG_RELOAD*/0, 0);
		if (!hRequest)
			break;

		// 请求打开文件
		if (!HttpSendRequest(hRequest, NULL, NULL, NULL, NULL))
			break;

		// 请求查看修改时间，以此来判断文件是否存在，这一步可以省略
		DWORD dwReadLen = MAX_PATH;
		TCHAR szReadBuff[MAX_PATH];
		if (!HttpQueryInfo(hRequest, HTTP_QUERY_LAST_MODIFIED, 
			szReadBuff, &dwReadLen, NULL))
			break;

		// 查询文件总大小
		memset(szReadBuff, 0, sizeof(szReadBuff));
		dwReadLen = MAX_PATH;
		if (!HttpQueryInfo(hRequest,HTTP_QUERY_CONTENT_LENGTH, 
			szReadBuff, &dwReadLen, NULL))
			break;

		// 设置总长度
		m_uTotalSize = _ttoi(szReadBuff);

		// 读取数据
		if (!DonwloadData(hRequest))
			break;

		// 所有的东西都结束了，才置为成功
		nFinalResult = CG_DOWNLOAD_RESULT_SUC;

	} while (false);

	// 保存最终下载结果
	m_nDownloadResult = nFinalResult;

	if (hRequest)
		InternetCloseHandle(hRequest);
	if (hConnect)
		InternetCloseHandle(hConnect);
	if (hSession)
		InternetCloseHandle(hSession);

	return 0;
}
