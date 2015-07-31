#include <windows.h>

#ifndef CGFileDownloader_h__
#define CGFileDownloader_h__

#define CG_DOWNLOAD_MAX_FILE_PATH_LEN 512

enum enmCGDownloadState
{
	enmCGDownloadStateUnstart = 0,		// 未启动状态
	enmCGDownloadStateDownloading = 1,	// 下载中
	enmCGDownloadStateFinished = 2,		// 已经完成
	enmCGDownloadStateFailed = 3,		// 下载失败
	// --------------------------------------
	// 暂时用到上面几个，下面的留作备用
	enmCGDownloadStatePaused = 4,
	enmCGDownloadStateStopped = 5,
};

class CCGFileDownloader
{
public:
	CCGFileDownloader(void);
	~CCGFileDownloader(void);

public:

	// 比如完整 url = www.onlinedown.net/newhuagg/newhua012.jpg
	// 保存目录 destdir = d:/download, 那么：
	// website = www.onlinedown.net
	// 相对 url = newhuagg/newhua012.jpg
	// filename = newhua012.jpg
	// destpath = d:/download/newhua012.jpg
	// 反正是要解析，不如放到外面

	// 每次设置三个太复杂了，弄一个集合参数的函数
	void Download(LPCTSTR lpctWeb, LPCTSTR lpctSrcUrl, LPCTSTR lpctDestPath);

	// 获取下载细节
	void GetDownloadDetail(enmCGDownloadState& enmState, DWORD& dwTotalSize, DWORD& dwDownloadSize);

	// 停止
	void Stop();

protected:
	// 下载线程
	static  DWORD WINAPI DoDownload(void * pParam);

	// 设置当前文件总大小
	void SetTotalSize(DWORD dwSize);

	// 获取已下载的大小
	void SetDownloadedSize(DWORD dwSize);

	// 设置下载状态
	void SetState(enmCGDownloadState enmState);

	// 设置网站，这里隐含了一个端口的分析
	void SetWebSite(LPCTSTR lpctWebsite);

protected:
	enmCGDownloadState m_enmDownloadState;
	DWORD m_dwTotalFileSize;
	DWORD m_dwDownloadedSize;
	// 上面三个都是两个线程都要访问的

	// 下面的东西不存在线程安全问题。
	TCHAR m_szWebSite[CG_DOWNLOAD_MAX_FILE_PATH_LEN];
	TCHAR m_szSrcUrl[CG_DOWNLOAD_MAX_FILE_PATH_LEN];
	TCHAR m_szDestFilePath[CG_DOWNLOAD_MAX_FILE_PATH_LEN];
	WORD m_iPort;

	// 线程信息只有自己可以访问
	HANDLE m_hDownloadThread;

};
#endif // CGFileDownloader_h__

