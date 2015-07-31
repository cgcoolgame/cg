////////////////////////////////////////////////
//	FileName:		cgSimpleThread.h
//	Author:			Master
//	Date:			2014.8.23
//	Description:	���̷߳�װ��ʹ��win32 api
//	mark:			������ʵ���Ǻ��ʺ�д����ģ����������е��ȣ�
//					�����е��ң�����̫�ã������е㳳֮��
////////////////////////////////////////////////

#ifndef cgSimpleThread_h__
#define cgSimpleThread_h__
#include <Windows.h>

/*
 *	һ���򵥵��̷߳�װ����ʱ�뵽����ͨ���̳У�������Run()�������ﵽ��չ��Ŀ�ģ�
 *	���þ����ˣ��Ȳ���������Ե����⣬���þ��У�
 */
class cgSimpleThread
{
public:
	cgSimpleThread(void);
	virtual ~cgSimpleThread(void);

	// ����һ���߳�
	virtual bool Start();

	// ֹͣһ���̣߳��������������ֹͣ��ֻ�ǰѴ˹����̵߳�״̬�ĳ�ֹͣ
	void Stop();

	// �ȴ�
	void Join();

	// ����һ���̵߳ľ��
	HANDLE GetThreadHandle();

	/* 
	 *	�ж��Ƿ���ɣ���Ҫѭ����ѯ����IsFinished()����true֮ǰ��
	 *	������ò�Ҫ����������߳���ȡ���ݡ� 
	*/
	virtual bool IsFinished();

protected:

	/* ʵ�ʵĹ����������������������֮ǰ����������̵߳�һֱ����δ���״̬��
	������IsFinished()����ѯ��ǰ�����Ƿ���ɣ������������Ҫʱ�̿��Ƕ��̻߳������� */
	virtual unsigned Run();

protected:

	/* �߳���ں���������һ�����ӣ������Ĺ������ǵ���Run()���������ȴ��䷵�أ�
	 Ȼ�������������߳� */
	static unsigned _stdcall MyThreadProc(void * pParam);

protected:
	HANDLE m_hThread;
	bool m_bIsFinished;
	bool m_bIsStopped;
};

#endif // cgSimpleThread_h__
