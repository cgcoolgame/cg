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
	// ���ڷ������½�
	RECT rtContainer   =   {0};  
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)&rtContainer,0);
	m_pkWindow->SetPos(rtContainer.right-GetWidth()-10, rtContainer.bottom-GetHeight());

	// �󶨼��������¼�������
	cgUIManager::Get()->SetUILoader(this);
	cgUIManager::Get()->AddUIEventListener(this);

	// ��ת��UI�������LoadScreen
	cgUIManager::Get()->GotoScreen("web_game");

	return true;
}

cgUIWidgetPtr cgWebGame::LoadScreen( const char * pcScreen )
{
	// ����Ԥ���õ�����������screen
	if (strcmp(pcScreen, "web_game") != 0)
		return NULL;

	// �������UI��һ��С���
	cgUIWidget * pkScreen = new cgUIWidget;
	pkScreen->SetName(pcScreen);
	pkScreen->SetLocalRect(0, 0, GetWidth(), GetHeight());
	pkScreen->SetStatic(true);

	// �رհ�ť
	cgUIButton * pkBtn = new cgUIButton;
	pkBtn->SetName("close");
	pkBtn->SetText(TEXT("X"));
	pkBtn->SetLocalRect(GetWidth()-20, 5, 20, 20);
	pkBtn->SetButtonColor(0x01000000, 0x01000000, 0x01000000, 0x01000000);
	pkBtn->SetDrawBackColor(true);
	pkScreen->AddChild(pkBtn);

	// web�ؼ�
	cgUIWebPageEx * pkWeb = new cgUIWebPageEx;
	pkWeb->SetName("web");
	pkWeb->Initialize(GetHwnd(), 0, 20, 320, 220);
	pkWeb->Navigate(TEXT("http://cb.6hgame.com/uninstall/v1/"));
	pkScreen->AddChild(pkWeb);

	return pkScreen;
}

cgUIWidgetPtr cgWebGame::LoadDynamic( const char * pcID )
{
	// �ò��Ŷ�̬�������
	return NULL;
}

// ����ֻ��Ҫ����һ����Ϣ���رհ�ť�ĵ���¼�
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
