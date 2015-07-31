#include "StdAfx.h"
#include "cgWebGame.h"
#include <cgUIWebPageEx.h>
#include <cgUIButton.h>


cgWebGame::cgWebGame(void)
{
}


cgWebGame::~cgWebGame(void)
{
}

bool cgWebGame::DoInitialize()
{
	// 窗口放于右下角
	RECT rtContainer   =   {0};  
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)&rtContainer,0);
	m_pkWindow->SetPos(rtContainer.right-GetWidth()-10, rtContainer.bottom-GetHeight());

	// 绑定加载器和事件监听器
	cgUIManager::Get()->SetUILoader(this);
	cgUIManager::Get()->AddUIEventListener(this);

	// 跳转到UI，会调用LoadScreen
	cgUIManager::Get()->GotoScreen("web_game");

	return true;
}

cgUIWidgetPtr cgWebGame::LoadScreen( const char * pcScreen )
{
	// 根据预定好的名字来加载screen
	if (strcmp(pcScreen, "web_game") != 0)
		return NULL;

	// 存放所有UI的一个小面板
	cgUIWidget * pkScreen = new cgUIWidget;
	pkScreen->SetName(pcScreen);
	pkScreen->SetLocalRect(0, 0, GetWidth(), GetHeight());
	pkScreen->SetStatic(true);

	// 关闭按钮
	cgUIButton * pkBtn = new cgUIButton;
	pkBtn->SetName("close");
	pkBtn->SetText(TEXT("X"));
	pkBtn->SetLocalRect(GetWidth()-20, 5, 20, 20);
	pkBtn->SetButtonColor(0x01000000, 0x01000000, 0x01000000, 0x01000000);
	pkBtn->SetDrawBackColor(true);
	pkScreen->AddChild(pkBtn);

	// web控件
	cgUIWebPageEx * pkWeb = new cgUIWebPageEx;
	pkWeb->SetName("web");
	pkWeb->Initialize(GetHwnd(), 0, 20, 320, 220);
	pkWeb->Navigate(TEXT("http://cb.6hgame.com/uninstall/v1/"));
	pkScreen->AddChild(pkWeb);

	return pkScreen;
}

cgUIWidgetPtr cgWebGame::LoadDynamic( const char * pcID )
{
	// 用不着动态加载面板
	return NULL;
}

// 我们只需要监听一个消息：关闭按钮的点击事件
bool cgWebGame::OnUIEvent( cgUIWidgetPtr spComponent, 
	cgUIEvent enmEvent, unsigned wparam, unsigned lparam )
{
	if (enmEvent == cgUIEvent_OnClick)
	{
		if (spComponent->GetName() == "close")
		{
			Stop();
		}
	}
	return true;
}
