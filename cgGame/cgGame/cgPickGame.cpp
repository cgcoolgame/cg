#include "StdAfx.h"
#include "cgPickGame.h"
#include <cgGameObject.h>
#include <cgGameSprite.h>
#include <cgMove.h>
#include <cgMath.h>
#include <cgGameLayer.h>
#include <cgRender.h>
#include <cgActionSequence.h>
#include <cgScaleBy.h>
#include <cgDestroy.h>
#include <cgSceneManager.h>
#include <cgBlink.h>
#include <cgRotateBy.h>
#include <cgEngineTools.h>
#include <cgScaleTo.h>
#include <cgGameText.h>
#include <cgCursorManager.h>
#include <cgWindow.h>
#include <cgGameUIManager.h>
#include <cgUIObject.h>
#include <cgButton.h>
#include <cgRotate.h>
#include <cgVisible.h>
#include <cgDeactive.h>
#include <cgActionBundle.h>
#include <cgAlphaTo.h>
#include <cgMoveTo.h>
#include <cgSoundManager.h>


cgPickGame::cgPickGame(void)
{
}


cgPickGame::~cgPickGame(void)
{
	
}

bool cgPickGame::DoInitGame()
{
	cgGameLayerPtr spLayer = cgSceneManager::Get()->GetSceneRoot();
	spLayer->AttachChild( new cgGameSprite(TEXT("./res/back.jpg")));
	m_spCamera = spLayer->GetCamera();

	m_spPickGameRoot = spLayer->AttachChild(new cgGameObject);

	cgCursorManager::Get()->SetDefaultCursor("default");
	ShowFPS(false);
	SetTitle(TEXT("打倒杨玲玲！！"));

	cgSoundManager::Get()->PlaySound(10000001);

	InitUI();

	StartGame();

	return true;
}

void cgPickGame::InitUI()
{
	cgGameText * pkText1 = new cgGameText(TEXT("打倒杨玲玲！！为黄屿立同志报仇！！！"), 0, 0xffff0000);
	pkText1->SetSize(400, 100);
//	pkText1->Move(-GetAppWidth()/2+260, -GetAppHeight()/2+60);
	cgGameUIManager::Get()->GetUIRoot()->AttachChild(pkText1);

	cgUIObject * pkUI = new cgUIObject("taskPanel");
	pkUI->SetSize(600, 200);
	pkUI->SetDrawFlag(cgUIObjectDrawFlag_DrawBorder|cgUIObjectDrawFlag_DrawBackGround);
	pkUI->SetActive(false);
	cgGameUIManager::Get()->GetUIRoot()->AttachChild(pkUI);

	cgUIObject * pkImage = new cgUIObject("image");
	pkImage->SetLocalPosition(-170.0f, -27.0f);
	pkImage->SetBackImage(TEXT("./res/image/2.png"), true);
	pkUI->AttachChild(pkImage);

	cgGameText * pkText = new cgGameText(TEXT("胜败乃兵家常事，请大侠重新来过！"), 2, 0xff00ff00);
	pkText->SetSize(300, 100);
	pkText->Move(20.0f, -50.0f);
	pkUI->AttachChild(pkText);

	cgButton * pkBtn = new cgButton("retry", cgVector(60.0f, 70.0f), cgSizeF(100.0f, 50.0f));
	pkBtn->SetText(TEXT("重试"));
	pkBtn->SetDrawFlag(cgUIObjectDrawFlag_DrawBorder|cgUIObjectDrawFlag_DrawBackGround);
	pkBtn->SetEventListener(this);
	pkBtn->GetTextObject()->SetFont(2);
	pkBtn->GetTextObject()->SetColor(0xff00ff00);
	pkUI->AttachChild(pkBtn);

	cgButton * pkBtn1 = new cgButton("quit", cgVector(-60.0f, 70.0f), cgSizeF(100.0f, 50.0f));
	pkBtn1->SetText(TEXT("退出"));
	pkBtn1->SetDrawFlag(cgUIObjectDrawFlag_DrawBorder|cgUIObjectDrawFlag_DrawBackGround);
	pkBtn1->SetEventListener(this);
	pkBtn1->GetTextObject()->SetFont(2);
	pkBtn1->GetTextObject()->SetColor(0xff00ff00);
	pkUI->AttachChild(pkBtn1);

	m_spGameOver = pkUI;
}


bool cgPickGame::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_LBUTTONUP:
		{
			float x = LOWORD(lParam);
			float y = HIWORD(lParam);

			if (m_eState == eRun)
				CheckPick(x, y);

			cgSoundManager::Get()->PlaySound(0);

		}break;

	case WM_MOUSEWHEEL:
		{
			if (m_spCamera->FindAction("cgScaleTo") == NULL && m_spCamera->FindAction("cgScaleBy") == NULL)
			{
				if (!cgXIsKeyPressed(VK_CONTROL))
				{
					short delta = (short)(HIWORD(wParam));
					m_spCamera->StartAction(
						new cgScaleBy(delta/1200.0f*m_spCamera->GetWorldScale().x, 
							delta/1200.0f*m_spCamera->GetWorldScale().y, 0.01f));
				}else
				{
					m_spCamera->StartAction(new cgScaleTo(1.0f, 1.0f, 0.3f));
				}
			}
		}break;
	case WM_MOUSEMOVE:
		{
			float x = LOWORD(lParam);
			float y = HIWORD(lParam);

			cgGameObjectPtr pick = cgGameObject::Root()->Pick(x, y, true);
			if (pick)
			{
				cgCursorManager::Get()->SetCursor("pick");
			}else
			{
				cgCursorManager::Get()->Reset();
			}
		}
		break;
	default:
		break;
	}
	return false;
}

void cgPickGame::DoUpdateGame( float fDeltaTime )
{
	if (m_eState == eRun)
	{
		UpdatePickGame(fDeltaTime);
	}else if (m_eState == eRestart)
	{
		StartGame();
	}
}

void cgPickGame::DoRenderGame()
{
	DrawScore();
}

void cgPickGame::StartGame()
{
	m_fCurRefreshTimeSpace = PickGameInitRefreshTimeSpace;
	m_fTime = 0;
	m_nLevel = 1;
	m_nTotal = 0;
	m_nPickTotal = 0;
	m_nEscapeTotal = 0;
	m_fCurMoveSpeed = PickGameObjectMoveSpeed;

	srand(::GetTickCount());

	m_eState = eRun;
}


void cgPickGame::StopGame()
{
	size_t childCount = m_spPickGameRoot->GetChildCount();
	for ( size_t i = 0; i < childCount; ++i)
	{
		cgGameObjectPtr sp = m_spPickGameRoot->GetChild(i);
		sp->StopAllActions();
	}

	m_spGameOver->SetActive(true);
	m_spGameOver->SetLocalScale(0.0f, 0.0f);
//	m_spGameOver->SetAlpha(0.0f);
	m_spGameOver->SetWorldPosition(-GetAppWidth()/2, -GetAppHeight()/2);
	cgActionBundle * pkBundle = new cgActionBundle;
	pkBundle->Add(new cgScaleTo(1.0f, 1.0f, 0.5f));
	pkBundle->Add(new cgMoveTo(0.0f, 0.0f, 0.5f));
//	pkBundle->Add(new cgAlphaTo(1.0f, 0.3f));
	m_spGameOver->StartAction(pkBundle);
	m_eState = eEndMenu;

	cgSoundManager::Get()->PlaySound(3);
}


void cgPickGame::Restart()
{
	cgActionBundle * pkBundle = new cgActionBundle;
	pkBundle->Add(new cgScaleTo(0.0f, 0.0f, 0.5f));
	pkBundle->Add(new cgMoveTo(-GetAppWidth()/2, -GetAppHeight()/2, 0.5f));

	cgActionSequence * pkSequence = new cgActionSequence;
	pkSequence->Add(pkBundle);
	pkSequence->Add(new cgDeactive);
	m_spGameOver->StartAction(pkSequence);
	//m_spGameOver->SetActive(false);
	m_spPickGameRoot->DetachAllChild();
	m_eState = eRestart;
}

void cgPickGame::UpdatePickGame(float fDeltaTime)
{
	m_fTime += fDeltaTime;

	CheckEscape();
	CheckRefreshNew();
	CheckDirection();

	if (m_nEscapeTotal >= PickGame_Lose_Count)
	{
		StopGame();
	}
}

void cgPickGame::CheckEscape()
{
	size_t childCount = m_spPickGameRoot->GetChildCount();
	for ( size_t i = 0; i < childCount; ++i)
	{
		cgGameObjectPtr sp = m_spPickGameRoot->GetChild(i);
		if (sp->IsPickable() && sp->GetActiveTime() >= PickGameObjectLifeTime)
		{
			++m_nEscapeTotal;
			sp->SetPickable(false);

			cgActionSequence * pkSequence = new cgActionSequence;
			pkSequence->Add(new cgBlink(5.0f, 1.0f));
			pkSequence->Add(new cgScaleTo(0.1f, 0.1f, 0.1f));
			pkSequence->Add(new cgDestroy);
			sp->StartAction(pkSequence);

			break;
		}
	}
}

void cgPickGame::CheckRefreshNew()
{
	if (m_fTime >= m_fCurRefreshTimeSpace)
	{
		m_fTime -= m_fCurRefreshTimeSpace;
		cgGameObject * pkNew = new cgGameSprite(TEXT("./res/yll.jpg"));

		cgSizeF viewSize = m_spCamera->GetViewSize();

		pkNew->SetWorldPosition(cgMath::Random(-viewSize.w/2, viewSize.w/2), 
			cgMath::Random(-viewSize.h/2, viewSize.h/2));

		pkNew->SetWorldScale(0.0f, 0.0f);
		pkNew->StartAction(new cgScaleTo(1.0f, 1.0f, 0.2f));
		pkNew->StartAction(new cgMove( cgMath::RandomOnCircle(m_fCurMoveSpeed)));
		pkNew->SetPickable(true);

		/*	cgGameText * pkTxt = new cgGameText(TEXT("白日依山尽，黄河入海流！"), 2);
		pkTxt->SetSize(100, 100);
		pkTxt->SetColor(0xff00ff00);
		pkTxt->SetBackColor(0x4f000000);
		pkNew->AttachChild(pkTxt);*/

		m_spPickGameRoot->AttachChild(pkNew);

		++m_nTotal;
	}
}

void cgPickGame::CheckDirection()
{
	cgSizeF viewSize = m_spCamera->GetViewSize();

	size_t childCount = m_spPickGameRoot->GetChildCount();
	for ( size_t i = 0; i < childCount; ++i)
	{
		cgGameObjectPtr sp = m_spPickGameRoot->GetChild(i);
		cgVector center = sp->GetWorldPosition();
		cgMovePtr spMove = (cgMove*)sp->FindAction("cgMove");
		if (spMove)
		{
			cgVector speed = spMove->GetSpeed();
			if ( (center.x <  -viewSize.w/2 && speed.x < 0) || (center.x > viewSize.w/2 && speed.x > 0))
			{
				speed.x = -speed.x;
			}

			if ((center.y < -viewSize.h/2 && speed.y < 0) || (center.y >viewSize.h/2 && speed.y > 0))
			{
				speed.y = -speed.y;
			}
			spMove->SetSpeed(speed);
		}
	}
}

void cgPickGame::CheckPick( float x, float y )
{
	cgGameObject * pkPick = cgGameObject::Root()->Pick(x, y, true);
	if (pkPick)
	{
		cgSoundManager::Get()->PlaySound(1);
		pkPick->SetPickable(false);
		pkPick->AttachChild(new cgGameSprite(TEXT("./res/effect.bmp")));

		cgActionSequence * pkSequence = new cgActionSequence;
		pkSequence->Add(new cgScaleBy(0.4f, 0.4f, 0.05f));
		pkSequence->Add(new cgScaleBy(-0.9f, -0.9f, 0.05f));
		pkSequence->Add(new cgDestroy);
		pkPick->StartAction(pkSequence);

		++m_nPickTotal;
		OnPickTotalChanged();
	}
}

void cgPickGame::OnPickTotalChanged()
{
	int lvl = m_nPickTotal/10+1;

	if (lvl != m_nLevel)
	{
		m_nLevel = lvl;
		m_fCurRefreshTimeSpace *= 0.9f;
	}
}

void cgPickGame::DrawScore()
{
	TCHAR szString[MAX_PATH];
	cgSprintf(szString, MAX_PATH, 
		TEXT("等级:%d \n 总数:%d \n 击中:%d \n 逃脱:%d"),
		m_nLevel, m_nTotal, m_nPickTotal, m_nEscapeTotal, m_spPickGameRoot->GetChildCount());

	cgRender::Get()->RenderString(szString, cgStrLen(szString), 
		cgRectF(10, 10, 300, 100), 2, 5, 0xffff0000, DT_LEFT);
}

// ---------------------------------------------------------------------------
int cgPickGame::OnMouseDown( cgUIObject* eventSrc )
{
	if (eventSrc->GetName() == "retry")
	{
		Restart();
	}else if (eventSrc->GetName() == "quit")
	{
		Stop();
	}
	return 0;
}
