#ifndef cgGameTaskManager_h__
#define cgGameTaskManager_h__

#include "cgSingleton.h"
#include "cgGameTask.h"


class cgGameTaskManager:
	public cgSingleton<cgGameTaskManager>
{
public:
	cgGameTaskManager(void);
	virtual ~cgGameTaskManager(void);

	bool Initialize();

	void AddGameTask(cgGameTaskPtr spTask);
	void Update(float fDeltaTime);

private:
	void UpdateTasks(float fDeltaTime);
	void CleanUp();

private:
	cgGameTaskPtrList m_kTaskPtrList;
};

#endif // cgGameTaskManager_h__
