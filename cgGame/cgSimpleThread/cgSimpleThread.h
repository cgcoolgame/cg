////////////////////////////////////////////////
//	FileName:		cgSimpleThread.h
//	Author:			Master
//	Date:			2014.8.23
//	Description:	简单线程封装，使用win32 api
//	mark:			今天其实还是很适合写代码的，除了天气有点热，
//					房间有点乱，精神不太好，风扇有点吵之外
////////////////////////////////////////////////

#ifndef cgSimpleThread_h__
#define cgSimpleThread_h__
#include <Windows.h>

/*
 *	一个简单的线程封装，暂时想到的是通过继承，并重载Run()函数来达到扩展的目的，
 *	够用就行了，先不考虑灵活性的问题，够用就行！
 */
class cgSimpleThread
{
public:
	cgSimpleThread(void);
	virtual ~cgSimpleThread(void);

	// 启动一个线程
	virtual bool Start();

	// 停止一个线程，并不是真的立刻停止，只是把此工作线程的状态改成停止
	void Stop();

	// 等待
	void Join();

	// 返回一个线程的句柄
	HANDLE GetThreadHandle();

	/* 
	 *	判断是否完成，需要循环查询，在IsFinished()返回true之前，
	 *	我们最好不要从这个工作线程中取数据。 
	*/
	virtual bool IsFinished();

protected:

	/* 实际的工作函数，在这个函数返回之前，这个工作线程的一直处于未完成状态，
	可以用IsFinished()来查询当前工作是否完成，在这个函数中要时刻考虑多线程互斥问题 */
	virtual unsigned Run();

protected:

	/* 线程入口函数，算是一个壳子，所做的工作就是调用Run()函数，并等待其返回，
	 然后主动结束本线程 */
	static unsigned _stdcall MyThreadProc(void * pParam);

protected:
	HANDLE m_hThread;
	bool m_bIsFinished;
	bool m_bIsStopped;
};

#endif // cgSimpleThread_h__
