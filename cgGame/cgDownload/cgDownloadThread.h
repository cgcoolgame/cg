/********************************************************************
	created:	2014/08/24
	created:	24:8:2014   0:46
	filename: 	cgDownloadThread.h
	author:		Master
	
	purpose:	一个单独的下载线程
*********************************************************************/
#ifndef cgDownloadThread_h__
#define cgDownloadThread_h__
#include <Windows.h>
#include "cgSimpleThread.h"
#include <wininet.h>

// 所有用到的Url字符串长度
#define CG_LONG_PATH_LEN 512

// 默认下载的数据缓存的大小
//#define CG_DEFAULT_DOWNLOAD_BUFFER_LEN 1024*512

// 默认读取网络数据的缓存大小
#define CG_DOWNLOAD_DATA_READ_BUFFER_LEN 64*1024

#define CG_DOWNLOAD_RESULT_UNDEFINED	-1 // 结果不确定，说明未开始下载，或者还没下载完毕
#define CG_DOWNLOAD_RESULT_SUC 0		// 下载成功
#define CG_DOWNLOAD_RESULT_FAILED 1		// 下载失败

/*
 *	每一个Url对应一个下载线程，
 *	可以选择下载到内存还是下载到文件
 *	可以自定义缓存大小
 */
class cgDownloadThread:
	public cgSimpleThread
{
public:
	cgDownloadThread(LPCTSTR lpctSrcUrl, LPCTSTR lpctSavePath);

	virtual ~cgDownloadThread(void);

	LPCTSTR GetSrcUrl();
	LPCTSTR GetSavePath();

	// 在IsFinished返回true之前，下面的返回值仅作参考，
	unsigned GetTotalSize();
	unsigned GetDownloadSize();
	unsigned GetDownloadSpeed();

	// 返回下载结果,在IsFinished返回true之前，结果都是无效的。
	int GetDownloadResult();

protected:
	// 工作函数
	virtual unsigned Run();

private:

	// 下载
	unsigned DoDownload();

	// 解析url
	bool ParseUrl(TCHAR * szWeb, unsigned uWebLen,
		TCHAR * szObject, unsigned uObjectLen,
		WORD & dwPort);

	// 从网络上下载数据
	bool DonwloadData(HINTERNET hRequest);

	// 读取一定量的数据时……
	bool OnReadData(void * pData, unsigned uDataSize);

private:
	TCHAR m_szUrl[CG_LONG_PATH_LEN];
	TCHAR m_szSavePath[CG_LONG_PATH_LEN];

	unsigned m_uTotalSize;
	unsigned m_uDownloadSize;

	DWORD m_dwLastTime;
	unsigned m_uDownloadSpeed;

	int m_nDownloadResult;
};

#endif // cgDownloadThread_h__
