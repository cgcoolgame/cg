#include "StdAfx.h"
#include "cgGdiplusUITest.h"
#include <cgUIManager.h>


cgGdiplusUITest::cgGdiplusUITest(void)
{
}


cgGdiplusUITest::~cgGdiplusUITest(void)
{
}

bool cgGdiplusUITest::DoInitialize()
{
	cgUIManager::Get()->SetUILoader(&m_kLoader);
	cgUIManager::Get()->AddUIEventListener(&m_kLoader);

	cgUIManager::Get()->GotoScreen("game");

	return true;
}
