#include "StdAfx.h"
#include "cgGameUIManager.h"
#include "cgGameUIRender.h"

#include "cgUIButton.h"
#include "cgUICheck.h"
#include "cgUIProgressBar.h"

cgGameUIManager::cgGameUIManager(void)
{
}


cgGameUIManager::~cgGameUIManager(void)
{
}

cgUIRender * cgGameUIManager::DoCreateUIRender()
{
	return new cgGameUIRender;
}
