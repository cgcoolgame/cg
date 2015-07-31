#include "StdAfx.h"
#include "cgTestUILoader.h"
#include <cgWinApp.h>
#include <cgUIButton.h>
#include <cgUIProgress.h>
#include <cgUIManager.h>
#include <cgUIWebPageEx.h>
#include <cgUILineEdit.h>
#include <cgUICheck.h>
#include <cgUIWebPage.h>
#include <cgUIRichText.h>


cgTestUILoader::cgTestUILoader(void)
{
}


cgTestUILoader::~cgTestUILoader(void)
{
}

cgUIWidgetPtr cgTestUILoader::LoadScreen( const char * pcScreen )
{
	cgUIWidget * pkScreen = new cgUIWidget;
	pkScreen->SetName(pcScreen);
	pkScreen->SetLocalRect(0, 0, GetAppWidth(), GetAppHeight());
	pkScreen->SetBackPic(TEXT("./res/back.jpg"));
//	pkScreen->SetBackPic(TEXT("./res\\s5_p.png"));
	pkScreen->SetStatic(true);
	pkScreen->SetDrawBorder(true);
//	pkScreen->SetBackColor(0x8f008fff);
	pkScreen->SetBackColor(0xff8f8f8f);
	pkScreen->SetDrawBackColor(true);

	if (false)
	{
		{
			cgUIButton * pkBtn = new cgUIButton;
			//pkBtn->SetButtonPic(TEXT("./res/btn/1.png"),
			//	TEXT("./res/btn/2.png"),
			//	TEXT("./res/btn/3.png"),
			//	TEXT("./res/btn/4.png"));
			pkBtn->SetDrawBackColor(true);
			pkBtn->SetDrawBorder(true);
			pkBtn->SetLocalRect(100, 100, 100, 50);
			pkBtn->SetText(TEXT("增加"));
			pkBtn->SetName("inc");
			pkScreen->AddChild(pkBtn);
		}

		{
			cgUIButton * pkBtn = new cgUIButton;
			//pkBtn->SetButtonPic(TEXT("./res/btn/1.png"),
			//	TEXT("./res/btn/2.png"),
			//	TEXT("./res/btn/3.png"),
			//	TEXT("./res/btn/4.png"));
			pkBtn->SetDrawBackColor(true);
			pkBtn->SetDrawBorder(true);
			pkBtn->SetLocalRect(300, 100, 100, 50);
			pkBtn->SetText(TEXT("减少"));
			pkBtn->SetName("dec");
			pkScreen->AddChild(pkBtn);
		}

		{
			cgUIButton * pkBtn = new cgUIButton;
			//pkBtn->SetButtonPic(TEXT("./res/btn/1.png"),
			//	TEXT("./res/btn/2.png"),
			//	TEXT("./res/btn/3.png"),
			//	TEXT("./res/btn/4.png"));
			pkBtn->SetDrawBackColor(true);
			pkBtn->SetDrawBorder(true);
			pkBtn->SetLocalRect(500, 100, 100, 50);
			pkBtn->SetText(TEXT("加满"));
			pkBtn->SetName("full");
			pkScreen->AddChild(pkBtn);
		}

		{
			cgUIButton * pkBtn = new cgUIButton;
			//pkBtn->SetButtonPic(TEXT("./res/btn/1.png"),
			//	TEXT("./res/btn/2.png"),
			//	TEXT("./res/btn/3.png"),
			//	TEXT("./res/btn/4.png"));
			pkBtn->SetDrawBackColor(true);
			pkBtn->SetDrawBorder(true);
			pkBtn->SetLocalRect(700, 100, 100, 50);
			pkBtn->SetText(TEXT("清空"));
			pkBtn->SetName("clr");
			pkScreen->AddChild(pkBtn);
		}

	


		cgUIProgress * pkBar = new cgUIProgress;
		pkBar->SetName("progress");
		pkBar->SetLocalRect(200, 200, 500, 20);
		pkBar->SetDrawBackColor(true);
		//	pkBar->SetBackColor(0xffffff00);
		//	pkBar->SetLayerColor(0xffffff00);
		//	pkBar->SetCoverColor(0xff008f00);
		//	pkBar->SetBorderColor(0xff00008f);
		pkBar->SetFont(2);
		//	pkBar->SetTextColor(0xff008f00);
		pkBar->SetDrawBorder(true);
		pkBar->SetProgress(10, true);
		pkBar->SetClipSelf(true);
		pkBar->SetStyle(cgUIStyle_XMove);
		pkScreen->AddChild(pkBar);
	}
	

//	cgUIWidget * pkPanel = new cgUIWidget("TestPanel");
//	pkPanel->SetLocalRect(100,100, 450, 600);
//	pkPanel->SetDrawBackColor(true);
//	pkPanel->SetDrawBorder(true);
//	pkPanel->SetMovable(true);
//	pkPanel->SetClipChildren(true);
////	pkPanel->SetClipSelf(true);
//	pkScreen->AddChild(pkPanel);
//	pkPanel->SetDepth(1);
//
//	cgUIButton * pkPanelBtn = new cgUIButton("test1");
//	pkPanelBtn->SetText(L"白日依山尽！白日依山尽！白日依山尽！白日依山尽！白日依山尽！");
//	pkPanelBtn->SetLocalRect(-50, -50, 200, 200);
//	pkPanelBtn->SetDrawBackColor(true);
//	pkPanelBtn->SetDrawBorder(true);
//	pkPanel->AddChild(pkPanelBtn);

	//
	if (true)
	{
		cgUIButton * pkBtn = new cgUIButton;
		//pkBtn->SetButtonPic(TEXT("./res/btn/1.png"),
		//	TEXT("./res/btn/2.png"),
		//	TEXT("./res/btn/3.png"),
		//	TEXT("./res/btn/4.png"));
		//	pkBtn->SetDrawBackColor(true);
		pkBtn->SetDrawBorder(true);
		pkBtn->SetLocalRect(GetAppWidth()-25, 5, 15, 15);
		pkBtn->SetText(TEXT("X"));
		pkBtn->SetName("quit");
		//	pkBtn->SetStatic(true);
		pkScreen->AddChild(pkBtn);


		cgUILineEdit * pkEdit = new cgUILineEdit("edit");
		pkEdit->SetLocalRect(10, 25, GetAppWidth()-20, 20);
		pkEdit->SetBackColor(0xdfffffff);
		//	pkEdit->SetBorderColor(0xffafafaf);
		//	pkEdit->SetTextColor(0xff000000);
		pkEdit->SetDrawBackColor(true);
		pkEdit->SetDrawBorder(true);
		pkEdit->SetClipSelf(true);
		//	pkEdit->SetMovable(true);
		pkScreen->AddChild(pkEdit);

		cgUIRichText * pkLabel = new cgUIRichText("text");
		pkLabel->SetLocalRect(10, 50, GetAppWidth()-20, 500);
		pkLabel->SetDrawBackColor(true);
		pkLabel->SetBackColor(0x8f000000);
		pkLabel->SetDrawBorder(true);
		pkLabel->SetTextStyle(DT_LEFT);
	//	pkLabel->SetFont(2);
		pkScreen->AddChild(pkLabel);

		//cgUIWebPageEx * pkWeb = new cgUIWebPageEx;
		//pkWeb->Initialize(GetAppHwnd(), 10, 150, GetAppWidth()-20, GetAppHeight()-160);
		//pkWeb->Navigate(TEXT("http://cb.6hgame.com/uninstall/v1/"));
		////	pkWeb->SetFreshTimeSpace(0.1f);
		////	pkWeb->SetWebpageOffset(100, 100, 100, 100);
		////	pkWeb->SetMovable(true);
		//pkWeb->SetName("web");
		//pkWeb->SetDrawBorder(true);
		//pkScreen->AddChild(pkWeb);
	}
//

	//for (int i = 0; i < 4; ++i)
	//{
	//	cgUICheck * pkCheck = new cgUICheck;
	//	pkCheck->SetLocalRect(200, 400+i*40, 20, 20);
	//	pkCheck->SetDrawBorder(true);
	//	pkCheck->SetDrawBackColor(true);
	//	pkScreen->AddChild(pkCheck);

	//	cgUIWidget * pkLabel = new cgUIWidget("text");
	//	pkLabel->SetLocalRect(200+24, 400+i*40, 200, 20);
	//	pkLabel->SetText(TEXT("白日依山尽！"));
	//	pkLabel->SetDrawBorder(true);
	//	pkLabel->SetDrawBackColor(true);
	//	pkScreen->AddChild(pkLabel);
	//}

	return pkScreen;
}

cgUIWidgetPtr cgTestUILoader::LoadDynamic( const char * pcID )
{
	return NULL;
}

bool cgTestUILoader::OnUIEvent( cgUIWidgetPtr spComponent, 
	cgUIEvent enmEvent, unsigned wparam, unsigned lparam )
{
	if (enmEvent == cgUIEvent_OnClick)
	{
		if (spComponent->GetName() == "inc")
		{
			ChangeProgress(10);
		}else if (spComponent->GetName() == "dec")
		{
			ChangeProgress(-10);
		}else if (spComponent->GetName() == "full")
		{
			ChangeProgress(100);
		}
		else if (spComponent->GetName() == "clr")
		{
			ChangeProgress(-100);
		}else if (spComponent->GetName() == "quit")
		{
			cgWinApp::GetApp()->Stop();
		}
	}else if (enmEvent == cgUIEvent_OnEnter)
	{
		if (spComponent->GetName() == "edit")
		{
			//ChangeWeb();
			ParseRichText();
		}
	}

	return true;
}

void cgTestUILoader::ChangeProgress(int change)
{
	cgUIProgress * pkBar = (cgUIProgress*)&cgUIManager::Get()->FindComponent("root.game.progress");
	if (pkBar)
	{
		static TCHAR szText[CG_LONG_TEXT_BUFF_LEN];

		pkBar->SetProgress(pkBar->GetProgress()+change);
		cgSprintf(szText, CG_LONG_TEXT_BUFF_LEN, TEXT("%d%%"), pkBar->GetProgress());
		pkBar->SetText(szText);
	}
}

void cgTestUILoader::ChangeWeb()
{
	cgUILineEdit * pkEdit = (cgUILineEdit*)&cgUIManager::Get()->FindComponent("root.game.edit");
	if (!pkEdit)
		return;

	cgUIWebPageEx * pkWeb = (cgUIWebPageEx*)&cgUIManager::Get()->FindComponent("root.game.web");
	if (!pkWeb)
		return ;

	pkWeb->Navigate(pkEdit->GetText());
}

void cgTestUILoader::ParseRichText()
{
	cgUILineEdit * pkEdit = (cgUILineEdit*)&cgUIManager::Get()->FindComponent("root.game.edit");
	if (!pkEdit)
		return;

	cgUIRichText * pkLabel = (cgUIRichText*)&cgUIManager::Get()->FindComponent("root.game.text");
	if (!pkLabel)
		return;

	pkLabel->SetText(pkEdit->GetText());
}

