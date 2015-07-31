#include "StdAfx.h"
#include "CGDownloadTask.h"
#include <tchar.h>


cgDownloadTask::cgDownloadTask( unsigned uDownloadID, LPCTSTR lpctUrl, LPCTSTR lpctDestPath )
{
	m_pkDownloadThread = NULL;
	m_uID = uDownloadID;

	_tcscpy_s(m_szUrl, CG_LONG_PATH_LEN, lpctUrl);
	_tcscpy_s(m_szSavePath, CG_LONG_PATH_LEN, lpctDestPath);

	// ÏÂÔØ¿ìÕÕ
	m_dwTotalFileSize = 0;
	m_dwDownloadedSize = 0;
	m_dwSpeed = 0;

	m_bIsFinished = false;
	m_nDownloadResult = CG_DOWNLOAD_RESULT_UNDEFINED;
}


cgDownloadTask::~cgDownloadTask(void)
{
	if (m_pkDownloadThread)
		delete m_pkDownloadThread;
}

// -------------------------------------
void cgDownloadTask::Start( )
{
	m_pkDownloadThread = new cgDownloadThread(m_szUrl, m_szSavePath);
	m_pkDownloadThread->Start();
}

void cgDownloadTask::Update( float fTime )
{
	if (m_pkDownloadThread)
	{
		m_bIsFinished = m_pkDownloadThread->IsFinished();
		m_dwTotalFileSize = m_pkDownloadThread->GetTotalSize();
		m_dwDownloadedSize = m_pkDownloadThread->GetDownloadSize();
		m_dwSpeed = m_pkDownloadThread->GetDownloadSpeed();
		m_nDownloadResult = m_pkDownloadThread->GetDownloadResult();
	}
}


bool cgDownloadTask::IsFinished()
{
	return m_bIsFinished;
}


int cgDownloadTask::GetDownloadResult()
{
	return m_nDownloadResult;
}

DWORD cgDownloadTask::GetSpeed() const
{
	return m_dwSpeed;
}

unsigned cgDownloadTask::GetID()const
{
	return m_uID;
}


DWORD cgDownloadTask::GetTotalSize()const
{
	return m_dwTotalFileSize;
}

DWORD cgDownloadTask::GetDownloadedSize()const
{
	return m_dwDownloadedSize;
}


LPCTSTR cgDownloadTask::GetUrl() const
{
	return m_szUrl;
}

LPCTSTR cgDownloadTask::GetSavePath() const
{
	return m_szSavePath;
}
