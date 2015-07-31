#include "StdAfx.h"
#include "cgUITest.h"
#include "cgGameUIRender.h"
#include "cgSrcImageManager.h"
#include "cgUIProgress.h"
#include "cgUIManager.h"
#include "cgGameUIRender.h"

cgUITest::cgUITest(void)
{
}


cgUITest::~cgUITest(void)
{
	cgUIManager::Destroy();
}

bool cgUITest::DoInitGame( )
{

//----------------------------------------------------------------------------------------
	if (!cgGameUIRender::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight()))
		return false;

	// 初始化UI系统，注意：gameapp默认不包含cgUIManager
	if (!cgUIManager::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight()))
		return false;

//----------------------------------------------------------------------------------------
	cgUIManager::Get()->SetUILoader(&m_kLoader);
	cgUIManager::Get()->AddUIEventListener(&m_kLoader);

	cgUIManager::Get()->GotoScreen("game");

	return true;
}

bool cgUITest::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (!cgUIManager::Get())
		return false;

	return cgUIManager::Get()->OnMessage(message, wParam, lParam);
}

//----------------------------------------------------------------------------------------


void cgUITest::DoUpdateGame( float fTime )
{
//--------------------------------------
	cgUIManager::Get()->Update(GetFrameBeginTime());
}

void cgUITest::DoRenderGame()
{	
	cgUIManager::Get()->Render();
}

