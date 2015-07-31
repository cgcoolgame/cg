#include "StdAfx.h"
#include "CGDownloadManager.h"
#include <assert.h>
#include <time.h>
#include <tchar.h>


cgDownloadManager::cgDownloadManager(void)
{
	m_pkListener = NULL;
	m_dwTotalSpeed = 0;
}


cgDownloadManager::~cgDownloadManager(void)
{
	cgDownloadTaskList::iterator it = m_kDownloadList.begin();
	for (; it != m_kDownloadList.end(); ++it)
	{
		delete * it;
	}
}

// --------------------------------------------------------------

size_t cgDownloadManager::GetDownloadNum()const
{
	return m_kDownloadList.size();
}

cgDownloadTask * cgDownloadManager::GetFileDownloaderByIndex(size_t uIndex)
{
	if (uIndex > -1 && uIndex < m_kDownloadList.size() )
	{
		return m_kDownloadList[uIndex];
	}

	return NULL;
}

// ------------------------------------
DWORD cgDownloadManager::GetTotalSpeed() const
{
	return m_dwTotalSpeed;
}

void cgDownloadManager::Update( float fTime )
{
	m_dwTotalSpeed = 0;

	// 一个临时列表
	cgDownloadTaskList kTempList;

	cgDownloadTaskList::iterator it = m_kDownloadList.begin();
	while ( it != m_kDownloadList.end())
	{
		cgDownloadTask * pkTask = *it;

		pkTask->Update(fTime);
		m_dwTotalSpeed += pkTask->GetSpeed();
		kTempList.push_back(pkTask);

		if (pkTask->IsFinished())
		{
			// 当下载完成或者下载失败，都从下载列表中删除
			// 但是不从内存中删除，删除的任务交给templist
			it = m_kDownloadList.erase(it);
		}else
		{
			++it;
		}
	}

	// 这里才是真正通知监听器的地方
	// 也是已经死亡的下载器删除的地方
	it = kTempList.begin();
	for (; it != kTempList.end(); ++it)
	{
		cgDownloadTask * pkTask = *it;

		OnDownloadProcess(pkTask);

		if (pkTask->IsFinished() )
		{
			if (pkTask->GetDownloadResult() == CG_DOWNLOAD_RESULT_SUC)
			{
				OnDownloadFinished(pkTask);
			}
			else if (pkTask->GetDownloadResult() == CG_DOWNLOAD_RESULT_FAILED)
			{
				OnDownloadFaild(pkTask);
			}
			delete pkTask;
		}
	}
}

unsigned cgDownloadManager::DownloadFile( LPCTSTR lpctUrl, LPCTSTR lpctDestPath, unsigned uID /*= 0*/ )
{
	cgDownloadTask * pkDownloader = new cgDownloadTask(uID, lpctUrl, lpctDestPath);
	m_kDownloadList.push_back(pkDownloader);
	pkDownloader->Start();

	return uID;
}

void cgDownloadManager::SetDownloadListener( cgDownloadListener * pkListener )
{
	assert(pkListener);
	m_pkListener = pkListener;
}
// -------------------------------------------------------------------------------------------------

void cgDownloadManager::OnDownloadProcess( const cgDownloadTask * pkTask )
{
	if (m_pkListener)
		m_pkListener->OnDownloadProcess(pkTask);
}

void cgDownloadManager::OnDownloadFinished( const cgDownloadTask * pkTask )
{
	if (m_pkListener)
		m_pkListener->OnDownloadFinished(pkTask);

	LogDownloadTaskOnEnd(pkTask);
}

void cgDownloadManager::OnDownloadFaild( const cgDownloadTask * pkTask )
{
	if (m_pkListener)
		m_pkListener->OnDownloadFailed(pkTask);

	LogDownloadTaskOnEnd(pkTask);
}

// ------------------------------------------------------------------------------------------
void cgDownloadManager::LogDownloadTaskOnEnd( const cgDownloadTask * pkTask )
{
	/*const int LONG_TEXT_BUFF = 1024;
	TCHAR szLogText[LONG_TEXT_BUFF];
	cgSprintf(szLogText, LONG_TEXT_BUFF, 
		TEXT("Src File Url : %s/%s\nSave Path : %s\nEnd Type : %s\
			 \nTotal Size : %u\nDownload Size : %u\nTotal Time : %0.2f s\
			 \nLastest Speed : %u k/s\nAverage Speed : %u k/s"),
			 pkTask->GetUrl(),
			 pkTask->GetSavePath(), 
			 pkTask->GetState() == enmCGDownloadStateFinished?TEXT("Finished!"):TEXT("Failed"),
			 pkTask->GetTotalSize(),
			 pkTask->GetDownloadedSize(),
			 pkTask->GetSpeed()/1000,
			 (unsigned)(pkTask->GetDownloadedSize()/pkTask->GetTotalTime()/1000));

	time_t kTime = time(NULL);
	tm * pTm = localtime(&kTime);

	FILE * pkFile = fopen("download/log.txt", "a");

	if (pkFile)
	{
		char * pBuff = NULL;
		DWORD dwBuffLen = 0;

#if defined _UNICODE
		dwBuffLen = WideCharToMultiByte(CP_ACP, 0, szLogText, -1, NULL, 0, NULL, NULL)+1;
		pBuff = new char[dwBuffLen];
		WideCharToMultiByte(CP_ACP, 0, szLogText, -1, pBuff, dwBuffLen, NULL, NULL);
#else
		pBuff = szLogText;
		dwBuffLen = _tcslen(pBuff);
#endif

		fprintf_s(pkFile, "--------------------------------------------------------------------------------\n%s%s\n",
			asctime(pTm), pBuff );

		fclose(pkFile);
	}*/

}