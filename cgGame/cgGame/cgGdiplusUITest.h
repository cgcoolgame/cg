#ifndef cgGdiplusUITest_h__
#define cgGdiplusUITest_h__
#include <cgGdiplusApp.h>
#include <cgSingleton.h>
#include "cgTestUILoader.h"


class cgGdiplusUITest:
	public cgGdiplusApp,
	public cgSingleton<cgGdiplusUITest>
{
public:
	cgGdiplusUITest(void);
	~cgGdiplusUITest(void);

protected:
	virtual bool DoInitialize();

protected:
	cgTestUILoader m_kLoader;
};

#endif // cgGdiplusUITest_h__
