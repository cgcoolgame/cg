#ifndef cgGdiplusUIManager_h__
#define cgGdiplusUIManager_h__
#include "cgUIManager.h"
#include "cgSingleton.h"


class cgGdiplusUIManager:
	public cgUIManager, 
	public cgSingleton<cgGdiplusUIManager>
{
public:
	cgGdiplusUIManager(void);
	~cgGdiplusUIManager(void);

protected:
	virtual cgUIRender * DoCreateUIRender();
};

#endif // cgGdiplusUIManager_h__
