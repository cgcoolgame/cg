#ifndef cgGameTaskUtility_h__
#define cgGameTaskUtility_h__
#include "cgGameTask.h"

// һЩԤ�����gametask


// ---------------------------------------------------------------------------
// �򵥵�ʱ��ȴ����񣬿���ͨ�����command�����һЩ��΢���ӵ�����
// 
class cgGameTask_SimpleWait:
	public cgGameTask
{
public:
	cgGameTask_SimpleWait(float fWaitTime);

	virtual void Update(float fDeltaTime);

	virtual bool IsTaskOver();

private:
	float m_fWaitTime;
};



#endif // cgGameTaskUtility_h__
