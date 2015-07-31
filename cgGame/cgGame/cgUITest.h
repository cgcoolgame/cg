
#ifndef cgUITest_h__
#define cgUITest_h__

#include "cggameapp.h"
#include "cgSingleton.h"
#include "cgUIWidget.h"
#include "cgImage.h"
#include "cgtestUIloader.h"

class cgUITest :
	public cgGameApp, 
	public cgSingleton<cgUITest>
{
public:
	cgUITest(void);
	virtual ~cgUITest(void);
public:
	// override
	bool DoInitGame();
	
protected:
	virtual bool DoProcessRawMessage(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoUpdateGame(float fTime);
	virtual void DoRenderGame();

private:
	cgTestUILoader m_kLoader;
};

#endif // cgUITest_h__
