//////////////////////////////////////////////////////////////////////////
// app的最基本框架，其实没啥用
// 就是放这里告诉自己，框架是这样的
//////////////////////////////////////////////////////////////////////////
#ifndef cgApp_h__
#define cgApp_h__

class cgApp
{
public:
	cgApp(void);
	virtual ~cgApp(void);

public:
	virtual bool Initialize() = NULL;
	virtual void Run() = NULL;
	virtual void Stop() = NULL;
};

#endif // cgApp_h__
