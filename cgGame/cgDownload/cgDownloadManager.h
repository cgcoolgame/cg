#ifndef CGDownloadManager_h__
#define CGDownloadManager_h__
#include <vector>
#include "cgDownloadTask.h"

typedef std::vector<cgDownloadTask*> cgDownloadTaskList;

class cgDownloadListener
{
public:
	virtual bool OnDownloadProcess(const cgDownloadTask * pkDownloader) = NULL;
	virtual bool OnDownloadFinished(const cgDownloadTask * pkDownloader) = NULL;
	virtual bool OnDownloadFailed(const cgDownloadTask * pkDownloader) = NULL;
};

class cgDownloadManager
{
public:
	cgDownloadManager(void);
	~cgDownloadManager(void);
public:
	
	// 定时监测所有的下载任务
	void Update(float fTime);

	// nFlag：留用
	unsigned DownloadFile(LPCTSTR lpctUrl, LPCTSTR lpctDestPath, unsigned uID = 0);

	// 总共有多少个文件正在和等待被下载
	size_t GetDownloadNum()const;
	cgDownloadTask * GetFileDownloaderByIndex(size_t uIndex);

	// 设置当前的监听器
	// 可以考虑弄成一个数组，暂时没必要
	void SetDownloadListener(cgDownloadListener * pkListener);

	// 获取当前的下载速度
	DWORD GetTotalSpeed()const;

protected:

	// 当下载任务状态变化的时候出发
	void OnDownloadProcess(const cgDownloadTask * pkTask);
	void OnDownloadFinished(const cgDownloadTask * pkTask);
	void OnDownloadFaild(const cgDownloadTask * pkTask);

	// 记录下所有的下载历史
	void LogDownloadTaskOnEnd(const cgDownloadTask * pkTask);
protected:
	cgDownloadTaskList m_kDownloadList;
	cgDownloadListener * m_pkListener;

	// 统计信息
	DWORD m_dwTotalSpeed;
};

#endif // CGDownloadManager_h__

