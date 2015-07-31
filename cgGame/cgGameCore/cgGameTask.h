#ifndef cgGameTask_h__
#define cgGameTask_h__
#include <list>
#include "cgGameCommand.h"
#include "cgRefObject.h"

// ��Ϸ���񣬹��ܺ�command���ƣ��������в�ͬ
// �������һ����ʱ�ޡ��п�ʼ���н������������Ч�Ķ���


class cgGameTask:
	public cgRefObject
{
public:
	cgGameTask(void);
	virtual ~cgGameTask(void);

	// ��ʼ
	virtual void Start();

	// ���ϸ���
	virtual void Update(float fDeltaTime);

	// �Ƿ���Ա�������
	virtual bool IsTaskOver();

	// ����ָ��
	void SetCommandOnStarted(cgGameCommandPtr spCommand);
	void SetCommandOnEnded(cgGameCommandPtr spCommand);

protected:
	// ��ʼ��ʱ�򴥷�һЩ����
	virtual void OnStarted();

	// ������ʱ�򴥷�һЩ����
	virtual void OnEnd();

protected:
	cgGameCommandPtr m_spStartedCmd;
	cgGameCommandPtr m_spEndedCmd;
	bool m_bIsTaskOver;
};

typedef cgSmartPointer<cgGameTask> cgGameTaskPtr;

typedef std::list<cgGameTaskPtr> cgGameTaskPtrList;

#endif // cgGameTask_h__
