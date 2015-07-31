#ifndef cgGameTask_h__
#define cgGameTask_h__
#include <list>
#include "cgGameCommand.h"
#include "cgRefObject.h"

// 游戏任务，功能和command类似，但是又有不同
// 任务就是一个有时限、有开始、有结束，会持续生效的东东


class cgGameTask:
	public cgRefObject
{
public:
	cgGameTask(void);
	virtual ~cgGameTask(void);

	// 开始
	virtual void Start();

	// 不断更新
	virtual void Update(float fDeltaTime);

	// 是否可以被清理了
	virtual bool IsTaskOver();

	// 设置指令
	void SetCommandOnStarted(cgGameCommandPtr spCommand);
	void SetCommandOnEnded(cgGameCommandPtr spCommand);

protected:
	// 开始的时候触发一些东西
	virtual void OnStarted();

	// 结束的时候触发一些事情
	virtual void OnEnd();

protected:
	cgGameCommandPtr m_spStartedCmd;
	cgGameCommandPtr m_spEndedCmd;
	bool m_bIsTaskOver;
};

typedef cgSmartPointer<cgGameTask> cgGameTaskPtr;

typedef std::list<cgGameTaskPtr> cgGameTaskPtrList;

#endif // cgGameTask_h__
