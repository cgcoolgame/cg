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
	// ## ��ܣ���������
	cgILoveShootingGame::Destroy();
	cgUIManager::Destroy();
}

bool cgILoveShooting::DoInitGame( )
{
	if (!cgGameUIRender::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight()))
		return false;

	// ʹ��UI
	if (!cgUIManager::Create()->Initialize(GetHwnd(), GetWidth(), GetHeight()))
		return false;

	SetTitle(TEXT("�Ұ���ɻ���"));

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
	// ����UI������Ϣ
	if (cgUIManager::Get() 
		&& cgUIManager::Get()->OnMessage(message, wParam, lParam))
		return true;

	// �߼�������Ϣ
	if (cgILoveShootingGame::Get()
		&& cgILoveShootingGame::Get()->OnMessage(message, wParam, lParam))
		return true;

	// ��ܣ�������Ϣ������ܣ���ѡ
	return false;
}

void cgILoveShooting::DoRenderGame()
{
	if (cgILoveShootingGame::Get() )
		cgILoveShootingGame::Get()->Render();

	// ## ��ܣ�UI���ϲ㣬����������
	if (cgUIManager::Get())
		cgUIManager::Get()->Render();

#ifdef _DEBUG

	TCHAR szText[CG_SHORT_TEXT_BUFF_LEN];
	cgSprintf(szText, TEXT("TimeAccelarate: x %.2f\n AppTime:%.1f"), GetTimeScale(), GetFrameBeginTime());
	cgRender::Get()->RenderString(szText, cgStrLen(szText), 200, 0, 2, 0xff00ff00);
	
#endif
}

// ��Ϣ����
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
