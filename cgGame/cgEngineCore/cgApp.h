//////////////////////////////////////////////////////////////////////////
// app���������ܣ���ʵûɶ��
// ���Ƿ���������Լ��������������
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
