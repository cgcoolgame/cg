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
	
	// ��ʱ������е���������
	void Update(float fTime);

	// nFlag������
	unsigned DownloadFile(LPCTSTR lpctUrl, LPCTSTR lpctDestPath, unsigned uID = 0);

	// �ܹ��ж��ٸ��ļ����ں͵ȴ�������
	size_t GetDownloadNum()const;
	cgDownloadTask * GetFileDownloaderByIndex(size_t uIndex);

	// ���õ�ǰ�ļ�����
	// ���Կ���Ū��һ�����飬��ʱû��Ҫ
	void SetDownloadListener(cgDownloadListener * pkListener);

	// ��ȡ��ǰ�������ٶ�
	DWORD GetTotalSpeed()const;

protected:

	// ����������״̬�仯��ʱ�����
	void OnDownloadProcess(const cgDownloadTask * pkTask);
	void OnDownloadFinished(const cgDownloadTask * pkTask);
	void OnDownloadFaild(const cgDownloadTask * pkTask);

	// ��¼�����е�������ʷ
	void LogDownloadTaskOnEnd(const cgDownloadTask * pkTask);
protected:
	cgDownloadTaskList m_kDownloadList;
	cgDownloadListener * m_pkListener;

	// ͳ����Ϣ
	DWORD m_dwTotalSpeed;
};

#endif // CGDownloadManager_h__

