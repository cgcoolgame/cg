#ifndef cgGameUIManager_h__
#define cgGameUIManager_h__
#include "cgUIManager.h"
#include "cgSingleton.h"


class cgGameUIManager :
	public cgUIManager, public cgSingleton<cgGameUIManager>
{
public:
	cgGameUIManager(void);
	virtual ~cgGameUIManager(void);

protected:
	virtual cgUIRender * DoCreateUIRender();
};

#endif // cgGameUIManager_h__
