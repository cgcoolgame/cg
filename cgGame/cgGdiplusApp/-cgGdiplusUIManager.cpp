#include "StdAfx.h"
#include "cgGdiplusUIManager.h"
#include "cgUIComponent.h"
#include "cgGdiplusRender.h"
#include "cgUIButton.h"
#include "cgUICheck.h"
#include "cgUIProgressBar.h"


cgGdiplusUIManager::cgGdiplusUIManager(void)
{
}


cgGdiplusUIManager::~cgGdiplusUIManager(void)
{
}

cgUIRender * cgGdiplusUIManager::DoCreateUIRender()
{
	return new cgGdiplusRender;
}
