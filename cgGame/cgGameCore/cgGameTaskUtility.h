#ifndef cgGameTaskUtility_h__
#define cgGameTaskUtility_h__
#include "cgGameTask.h"

// 一些预定义的gametask


// ---------------------------------------------------------------------------
// 简单的时间等待任务，可以通过配合command来完成一些稍微复杂的任务
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
