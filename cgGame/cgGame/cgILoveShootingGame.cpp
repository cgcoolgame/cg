#include "StdAfx.h"
#include "cgILoveShootingGame.h"
#include "cgUIWidget.h"
#include "cgUIButton.h"
#include "cgILSConfigManager.h"
#include "cgFlyObjectManager.h"
#include "cgRender.h"
#include "cgSrcImageManager.h"
#include "cgWinApp.h"
#include "cgGameTools.h"
#include "cgGameCommandUtility.h"
#include "cgILoveShooting.h"
#include "cgStringTable.h"
#include "cgBattleManager.h"
#include "cgSoundManager.h"
#include "cgEngineTools.h"
#include <cgMove.h>

cgILoveShootingGame::cgILoveShootingGame(void)
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_nKillNum = 0;
	m_nBeKilledNum = 0;
	m_idBgm = CG_INVALID_ID;
	cgGameMessageListenerManager::Get()->AddListener(this);
}


cgILoveShootingGame::~cgILoveShootingGame(void)
{
	cgBattleManager::Destroy();
	cgFlyObjectManager::Destroy();
	cgILSConfigManager::Destroy();
	cgGameMessageListenerManager::Get()->DelListener(this);
	cgUIManager::Get()->DelUIEventListener(this);
}

bool cgILoveShootingGame::Initialize( cgHwnd hWnd, int w, int h )
{
	m_nWidth = w;
	m_nHeight = h;
	cgILSConfigManager::Create()->Initialize();

	if (cgUIManager::Get())
	{
		cgUIManager::Get()->AddUIEventListener(this);
		cgUIManager::Get()->SetUILoader(this);

		cgUIManager::Get()->GotoScreen("dlg");

		GotoDlgPanel();
	}

	m_idBgm = cgSoundManager::Get()->PlaySound(10000001);

	return true;
}


bool cgILoveShootingGame::OnGameMessage( cgGameMessage msg, void * pData, int nLen )
{
	if (msg == cgGameMessage_AircraftBeKilled)
	{
		cgAircraft * pkAircraft = (cgAircraft*)pData;
		if (pkAircraft == &m_spMainCraft)
		{
//			cout<<"你被击落了！！！"<<endl;
			++m_nBeKilledNum;
			InitMainCraft();

		}else
		{
			++m_nKillNum;
		/*	int nLvl = m_nKillNum/10+1-m_nBeKilledNum;

			cgAircraftWeaponPtr spWeapon = m_spMainCraft->GetMainWeapon();
			if (nLvl > spWeapon->GetWeaponLvl() && spWeapon->CanLevelup())
			{
				spWeapon->Levelup();
			}*/

		//	cout<<("你击落了：")<<cgStringTable::Get()->UnicodeToAcp(pkAircraft->GetConfig()->strDesc.c_str())<<endl;
		}
	}

	return true;
}


bool cgILoveShootingGame::OnMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	/*if (message == WM_KEYDOWN)
	{
	if (wParam == VK_LEFT)
	{
	m_pkMainCraft->Move(-10, 0);
	}else if (wParam == VK_RIGHT)
	{
	m_pkMainCraft->Move(10, 0);
	}else if (wParam == VK_UP)
	{
	m_pkMainCraft->Move(0, -10);
	}else if (wParam == VK_DOWN)
	{
	m_pkMainCraft->Move(0, 10);
	}
	}*/

	if (message == WM_KEYDOWN)
	{
		if (wParam == 'W')
		{
			cgAircraftWeaponPtr spWeapon = m_spMainCraft->GetMainWeapon();
			if ( spWeapon->CanLevelup())
			{
				spWeapon->Levelup();
			}
		}else if (wParam == 'S')
		{
			cgAircraftWeaponPtr spWeapon = m_spMainCraft->GetMainWeapon();
			if ( spWeapon)
			{
				spWeapon->LevelDown();
			}
			// 减速
		//	cgGameApp::GetGameApp()->SetTimeAccelerate(cgGameApp::GetGameApp()->GetTimeAccelerate()-0.1f);
		}
	}else if (message == WM_KEYUP)
	{
		/*if (wParam == VK_HOME)
		{
			cgGameTools::PostGameCommand(new cgGameCommand_ToggleFps, -1.0f);
		}else if (wParam == 'A')
		{
			cgGameTools::PostGameCommand(new cgGameCommand_ChangeMaxFps(10), 1.0f);
		}else if (wParam == 'D')
		{
			cgGameTools::PostGameCommand(new cgGameCommand_ChangeMaxFps(60), 1.0f);
		}*/
		/*if (wParam == VK_SPACE)
		{
		cgBulletPtr spBullet = cgBullet::CreateBullet(4);
		spBullet->SetCamp(cgFlyObjectCamp_Self);
		cgFlyObjectManager::Get()->AddBullet(spBullet);
		cgScene::Get()->GetSceneRoot()->GetCamera()->StartAction(new cgSpiritAction_Shake(0.0f, 10.0f, 30.0f, 0.5));
		}*/
		if (wParam == 'P')
		{
			srand(::GetTickCount());
			TCHAR szName[CG_SHORT_TEXT_BUFF_LEN];
			cgSprintf(szName, CG_SHORT_TEXT_BUFF_LEN, TEXT("cgILoveShooting_%d_%d.png"), ::GetTickCount(), rand()%10000);
			cgRender::Get()->ScreenShot(szName, cgScreenShotImageFormat_PNG);
		}
	}
	return false;
}

void cgILoveShootingGame::Update( float fDeltaTime )
{
	if (cgFlyObjectManager::Get())
		cgFlyObjectManager::Get()->Update(fDeltaTime);

	if (cgBattleManager::Get())
		cgBattleManager::Get()->Update(fDeltaTime);

	if (m_spMainCraft)
	{
		m_spMainCraft->StopAction("move");

		bool bMove = false;
		cgVector v;
		if (cgXIsKeyPressed(VK_LEFT))
		{
			v.x = -1;
			bMove = true;
		}else if (cgXIsKeyPressed(VK_RIGHT))
		{
			v.x = 1;
			bMove = true;
		}

		if (cgXIsKeyPressed(VK_UP))
		{
			v.y = -1;
			bMove = true;
		}else if (cgXIsKeyPressed(VK_DOWN))
		{
			v.y = 1;
			bMove = true;
		}
		if (bMove)
		{
			v *= m_spMainCraft->GetConfig()->nBasicSpeed;

			cgMove * pkMove = new cgMove(v.x, v.y);
			pkMove->SetName("move");
			m_spMainCraft->StartAction(pkMove);
		}

//		cgScene::Get()->GetSceneRoot()->GetCamera()->SetCenter(m_spMainCraft->GetCenterX(), m_spMainCraft->GetCenterY());

		
	}

	
}

void cgILoveShootingGame::Render()
{
//	m_spBkImage->DrawToPoint(0, 0);

	//if (cgFlyObjectManager::Get())
	//	cgFlyObjectManager::Get()->Render();
	cgRectF rect(GetWidth()/2-300, 0, 600, GetHeight());
	cgRender::Get()->DrawBox(rect, 0xff008f00);
#ifdef _DEBUG
	if (cgFlyObjectManager::Get())
	{
		int nAircraftNum = cgFlyObjectManager::Get()->GetAircraftCount();
		int nBulletNum = cgFlyObjectManager::Get()->GetBulletCount();

		TCHAR szText[CG_SHORT_TEXT_BUFF_LEN];
		cgSprintf(szText, CG_SHORT_TEXT_BUFF_LEN, TEXT("kill:%d, bekilled: %d, craft: %d, bullet: %d, obj: %d"), 
			m_nKillNum, m_nBeKilledNum, nAircraftNum, nBulletNum, cgRefObject::GetTotalObjectNum());
		cgRender::Get()->RenderString(szText, cgStrLen(szText), 10, 50, 0, 0xff008f00);

		if (m_spMainCraft)
		{
			cgSprintf(szText, CG_SHORT_TEXT_BUFF_LEN, TEXT("weapon lvl = %d"), m_spMainCraft->GetMainWeapon()->GetWeaponLvl() );
			cgRender::Get()->RenderString(szText, cgStrLen(szText), 10, 100, 0, 0xff008f00);
		}
		if (cgBattleManager::Get())
		{
				cgString strName = cgBattleManager::Get()->GetCurBattleConfig()->strName;
				cgString strDesc = cgBattleManager::Get()->GetCurBattleConfig()->strDesc;
			cgRender::Get()->RenderString(strName.c_str(), strName.length(), 10, 150, 2, 0xff008f00);
			cgRender::Get()->RenderString(strDesc.c_str(), strDesc.length(), cgRectF(10, 200, 200, 200), 0, 5, 0xff008f00, DT_LEFT);
		}
	}

#endif

}


bool cgILoveShootingGame::Start()
{
	cgFlyObjectManager::Create()->Initialize();

	InitMainCraft();

	cgBattleManager::Create()->Initialize();
	cgBattleManager::Get()->SetCurBattle(1);
	cgGameMessageListenerManager::Get()->AddListener(cgBattleManager::Get());

	return true;
}

// ----------------------------------------------------------------------------------------------------------

cgUIWidgetPtr cgILoveShootingGame::LoadScreen( const char * pcScreen )
{
	cgUIWidget * pkDlg = new cgUIWidget;
	pkDlg->SetSize(400, 300);
	pkDlg->SetPosition((GetWidth()-pkDlg->GetWidth())/2, (GetHeight()-pkDlg->GetHeight())/2);
	pkDlg->SetName(pcScreen);
	pkDlg->SetDrawBackColor(true);
	pkDlg->SetDrawBorder(true);

	// 文字
	cgUIWidget * pkText = new cgUIWidget;
	pkText->SetSize(400, 200);
	pkText->SetPosition(pkDlg->GetX(), pkDlg->GetY());
	pkText->SetFont(1);
	pkText->SetText(TEXT("少年，喜欢打飞机吗？现在来一发如何？"));
	pkText->SetName("text");
	pkDlg->AddChild(pkText);


	// 按钮
	cgUIButton * pkOKBtn = new cgUIButton;
	pkOKBtn->SetName("okbtn");
	pkOKBtn->SetSize(100, 50);
	pkOKBtn->SetPosition(pkDlg->GetX()+(pkDlg->GetWidth()-pkOKBtn->GetWidth())/2, pkDlg->GetY()+pkText->GetHeight());
	pkOKBtn->SetFont(1);
	pkOKBtn->SetText(TEXT("好啊"));
//	pkOKBtn->SetBackColor(0x8f0000ff);
	pkOKBtn->SetDrawBackColor(true);
	pkOKBtn->SetDrawBorder(true);
	pkDlg->AddChild(pkOKBtn);

	return pkDlg;
}

// 本来应该从配置读取的，手动创建吧，体力活！！！
bool cgILoveShootingGame::LoadAllUIs( cgUIWidgetPtr spRoot, int w, int h, cgHwnd hWnd )
{
	
	// 加载对话框
	{
		cgUIWidget * pkDlg = new cgUIWidget;
		pkDlg->SetSize(400, 300);
		pkDlg->SetPosition((w-pkDlg->GetWidth())/2, (h-pkDlg->GetHeight())/2);
		pkDlg->SetName("dlg");
		spRoot->AddChild(pkDlg);

		// 文字
		cgUIWidget * pkText = new cgUIWidget;
		pkText->SetSize(400, 200);
		pkText->SetPosition(pkDlg->GetX(), pkDlg->GetY());
		pkText->SetFont(1);
		pkText->SetText(TEXT("少年，喜欢打飞机吗？现在来一发如何？"));
		pkText->SetName("text");
		pkDlg->AddChild(pkText);


		// 按钮
		cgUIButton * pkOKBtn = new cgUIButton;
		pkOKBtn->SetName("okbtn");
		pkOKBtn->SetSize(100, 50);
		pkOKBtn->SetPosition(pkDlg->GetX()+(pkDlg->GetWidth()-pkOKBtn->GetWidth())/2, pkDlg->GetY()+pkText->GetHeight());
		pkOKBtn->SetFont(1);
		pkOKBtn->SetText(TEXT("好啊"));
		pkOKBtn->SetBackColor(0x8f0000ff);
		pkOKBtn->SetDrawBackColor(true);
		pkDlg->AddChild(pkOKBtn);

	}

	return true;
}

// ---------------------------------------------------------------------------------------------------------
// 对话面板
static const int cgILoveShootingGame_DlgNum = 4;
static const LPCTSTR cgILoveShootingGame_lpctDlgs[cgILoveShootingGame_DlgNum][2]=
{
	{TEXT("骚年，喜欢打飞机吗？"), TEXT("喜欢！")},
	{TEXT("现在来一发如何？"), TEXT("好啊！")},
	{TEXT("打飞机之旅即将开始，骚年可否准备好了？"), TEXT("走你！")},
	{TEXT("走个屁啊，等等我？"), TEXT("赶紧的！")}
};

bool cgILoveShootingGame::GotoDlgPanel()
{
	cgUIWidgetPtr ptr = cgUIManager::Get()->FindComponent("root.dlg");
	if (!ptr)
		return false;

	// 记录当前播放到第几个了。
	ptr->SetCustomValue(0);
	ShowDlg();
	return true;
}

bool cgILoveShootingGame::ShowDlg()
{
	cgUIWidgetPtr spDlg = cgUIManager::Get()->FindComponent("root.dlg");
	if (!spDlg)
		return false;

	int nValue = spDlg->GetCustomValue();
	if (nValue >= cgILoveShootingGame_DlgNum)
		return false;

	cgUIWidgetPtr spText = spDlg->FindChild("text");
	cgUIWidgetPtr spBtn = spDlg->FindChild("okbtn");
	if (!spText || !spBtn)
		return false;

	spText->SetText(cgILoveShootingGame_lpctDlgs[nValue][0]);
	spBtn->SetText(cgILoveShootingGame_lpctDlgs[nValue][1]);

	spDlg->SetCustomValue(nValue+1);

	return true;
}

// ---------------------------------------------------------------------------------------------------------

bool cgILoveShootingGame::GotoSelPanel()
{

	cgUIWidgetPtr spDlg = cgUIManager::Get()->FindComponent("root.dlg");
	if (spDlg)
		spDlg->SetVisible(false);

	
	return Start();

	cgUIWidgetPtr spSelPanel = cgUIManager::Get()->FindComponent("root.selpanel");
	if (!spSelPanel)
		return false;

	return true;
}

// ---------------------------------------------------------------------------------------------------------

bool cgILoveShootingGame::GotoGamePanel()
{
	cgUIWidgetPtr spSelPanel = cgUIManager::Get()->FindComponent("root.selpanel");
	if (spSelPanel)
		spSelPanel->SetVisible(false);

	return true;
}

// ----------------------------------------------------------------------------------------------------------------------
bool cgILoveShootingGame::OnUIEvent( cgUIWidgetPtr spComponent,
	cgUIEvent enmEvent, unsigned wparam, unsigned lparam )
{
	switch (enmEvent)
	{
	case cgUIEvent_OnClick:
		return OnClick(spComponent, wparam, lparam);
		break;
	}
	return false;
}

bool cgILoveShootingGame::OnClick( cgUIWidgetPtr spComponent, unsigned wparam, unsigned lparam )
{
	if (!spComponent)
		return false;
	string strPath;
	spComponent->GetPath(strPath);

	if (strPath == "root.dlg.okbtn")
	{
		if (!ShowDlg())
			GotoSelPanel();
	}

	return true;
}

bool cgILoveShootingGame::OnMouseIn( cgUIWidgetPtr spComponent, unsigned wparam, unsigned lparam )
{
	return true;
}

int cgILoveShootingGame::GetWidth()
{
	return m_nWidth;
}

int cgILoveShootingGame::GetHeight()
{
	return m_nHeight;
}

cgAircraftPtr cgILoveShootingGame::GetMainCraft()
{
	return m_spMainCraft;
}

void cgILoveShootingGame::InitMainCraft()
{
	m_spMainCraft = cgAircraft::CreateAircraft(1, 0);
	m_spMainCraft->SetCamp(cgFlyObjectCamp_Self);
	m_spMainCraft->SetWorldPosition(0.0f, GetHeight()/2-100);
	cgFlyObjectManager::Get()->AddAircraft(m_spMainCraft);
}

// ----------------------------------------------------------------------------------------------------------
