#include "StdAfx.h"
#include "cgILoveShooting.h"
#include "cgILoveShootingGame.h"
#include "cgRender.h"
#include "cgGameMessageListenerManager.h"
#include "cgGameTaskManager.h"
#include "cgGameUIRender.h"


cgILoveShooting::cgILoveShooting(void)
{
}


cgILoveShooting::~cgILoveShooting(void)
{
	// ## 框架：反序销毁
	cgILoveShootingGame::Destroy();
	cgUIManager::Destroy();
}

bool cgILoveShooting::DoInitGame( )
{
	if (!cgGameUIRender::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight()))
		return false;

	// 使用UI
	if (!cgUIManager::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight()))
		return false;

	SetTitle(TEXT("我爱打飞机！"));

	//ShowFPS(false);
	cgGameMessageListenerManager::Get()->AddListener(this);

	cgGameMessageListenerManager::Get()->DispatchGameMessage(cgGameMessage_GameAppInitialized);

	return true;
}

void cgILoveShooting::DoUpdateGame( float fDeltaTime )
{
	cgUIManager::Get()->Update(GetFrameBeginTime());

	if (cgILoveShootingGame::Get())
		cgILoveShootingGame::Get()->Update(fDeltaTime);
}

bool cgILoveShooting::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	// 先让UI处理消息
	if (cgUIManager::Get() 
		&& cgUIManager::Get()->OnMessage(message, wParam, lParam))
		return true;

	// 逻辑处理消息
	if (cgILoveShootingGame::Get()
		&& cgILoveShootingGame::Get()->OnMessage(message, wParam, lParam))
		return true;

	// 框架：最后把消息交给框架，可选
	return false;
}

void cgILoveShooting::DoRenderGame()
{
	if (cgILoveShootingGame::Get() )
		cgILoveShootingGame::Get()->Render();

	// ## 框架：UI在上层，所以最后绘制
	if (cgUIManager::Get())
		cgUIManager::Get()->Render();

#ifdef _DEBUG

	TCHAR szText[CG_SHORT_TEXT_BUFF_LEN];
	cgSprintf(szText, TEXT("TimeAccelarate: x %.2f\n AppTime:%.1f"), GetTimeScale(), GetFrameBeginTime());
	cgRender::Get()->RenderString(szText, cgStrLen(szText), 200, 0, 2, 0xff00ff00);
	
#endif
}

// 消息处理
bool cgILoveShooting::OnGameMessage( cgGameMessage msg, void * pData, int nLen )
{
	switch (msg)
	{
	case cgGameMessage_GameAppInitialized:
		//{
		//	cgGameTaskManager::Get()->AddGameTask(new cgGameLogoTask);
		//}break;
	case cgGameMessage_LogoFinished:
		{
			cgILoveShootingGame::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight());

		}break;
	}

	return true;
}
