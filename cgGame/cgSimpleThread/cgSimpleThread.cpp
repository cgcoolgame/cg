#include "StdAfx.h"
#include "cgSimpleThread.h"
#include <process.h>

cgSimpleThread::cgSimpleThread(void)
{
	m_hThread = NULL;
	m_bIsFinished = false;
	m_bIsStopped = false;
}

cgSimpleThread::~cgSimpleThread(void)
{
	if (m_hThread)
	{
		if (WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT)
		{
			// 如果线程还没结束，则设置结束标记，子类的实现见到结束标记后，尽快让线程函数返回
			// 如果设置了结束标记，线程函数还不返回，只会导致线程永远不能结束，子类实现者一定要切记！
			Stop();
			WaitForSingleObject(m_hThread, INFINITE);
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

bool cgSimpleThread::Start()
{
	m_bIsFinished = false;

	m_hThread = (HANDLE)_beginthreadex(0, 0, &cgSimpleThread::MyThreadProc, this, 0, 0);

	return m_hThread != NULL;
}

void cgSimpleThread::Stop()
{
	m_bIsStopped = true;
}

void cgSimpleThread::Join()
{
	if (m_hThread)
		WaitForSingleObject(m_hThread, INFINITE);
}


HANDLE cgSimpleThread::GetThreadHandle()
{
	return m_hThread;
}

bool cgSimpleThread::IsFinished()
{
	return m_bIsFinished;
}

unsigned cgSimpleThread::Run()
{
	return 0;
}

unsigned _stdcall cgSimpleThread::MyThreadProc( void * pParam )
{
	cgSimpleThread * pkThread = (cgSimpleThread*)pParam;

	int nRet = pkThread->Run();

	pkThread->m_bIsFinished = true;

	_endthreadex(nRet);

	return nRet;
}

