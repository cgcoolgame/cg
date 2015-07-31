#include "cgDownloadThread.h"
// 一个下载任务，是对下载线程的一次封装下载线程的功能应该尽量单一
// 所以各种统计数据都放到了下载任务里面，这个类还负责保存下载信息快照

#ifndef CGDownloadTask_h__
#define CGDownloadTask_h__

struct cgDownloadProgress
{
	unsigned uTotalSize;
	unsigned uDownloadSize;
	unsigned uSpeed;
	int nState;
	int nDownloadResult;
};

class cgDownloadTask
{
public:
	cgDownloadTask(unsigned uDownloadID, LPCTSTR lpctUrl, LPCTSTR lpctDestPath);
	~cgDownloadTask(void);

	// 开始下载
	void Start();

	// 更新快照
	void Update(float fTime);

	// 是否完成
	bool IsFinished();

	// 下载结果
	int GetDownloadResult();

	// 速度相关
	DWORD GetSpeed()const;

	// 当前总大小快照
	DWORD GetTotalSize()const;

	// 已下载大小快照
	DWORD GetDownloadedSize()const;

	unsigned GetID()const;

	// 源文件相对路径
	LPCTSTR GetUrl() const;

	// 目标文件路径
	LPCTSTR GetSavePath() const;
protected:
	cgDownloadThread* m_pkDownloadThread; // 所属下载器

	unsigned m_uID;
	TCHAR m_szUrl[CG_LONG_PATH_LEN];
	TCHAR m_szSavePath[CG_LONG_PATH_LEN];

	// 下载快照
	DWORD m_dwTotalFileSize;
	DWORD m_dwDownloadedSize;
	DWORD m_dwSpeed;

	bool m_bIsFinished;
	int m_nDownloadResult;
};
#endif // CGDownloadTask_h__

