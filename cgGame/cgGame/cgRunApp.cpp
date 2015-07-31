#include "StdAfx.h"
#include "cgRunApp.h"
#include "cgRender.h"
#include "cgAnimation.h"
#include "cgAnimationUtility.h"
#include "cgActor.h"
#include "cgGameTaskManager.h"
#include "cgEngineTools.h"
#include "cgStringTable.h"
#include "cgGameSprite.h"
#include "cgGameCamera.h"
#include <cgGameLayer.h>
#include <cgMove.h>
#include <cgMoveTo.h>
#include <cgMath.h>
#include <cgMoveBy.h>
#include <cgScaleBy.h>
#include <cgScaleTo.h>
#include <cgRotate.h>
#include <cgRotateBy.h>
#include <cgRotateTo.h>
#include <cgRotateAround.h>
#include <cgAlphaBy.h>
#include <cgActionSequence.h>
#include <cgVisible.h>
#include <cgWait.h>
#include <cgDestroy.h>
#include <cgActionBundle.h>
#include <cgSceneManager.h>
#include <cgGameText.h>


cgRunApp::cgRunApp(void)
{
}


cgRunApp::~cgRunApp(void)
{
	cgGameObject::ClearAll();
}

bool cgRunApp::DoInitGame()
{
	SetTitle(TEXT("跑起来！"));

	//ShowFPS(false);
	cgGameMessageListenerManager::Get()->AddListener(this);

	cgGameMessageListenerManager::Get()->DispatchGameMessage(cgGameMessage_GameAppInitialized);

	return true;
}

bool cgRunApp::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	const static float fSpeed = 200.0f;
	if(m_spRole )
	{
		if (message == WM_KEYDOWN)
		{
			if (wParam == VK_LEFT)
			{
				m_spRole->SetDirection(cgLeft);
				m_spRole->StopAction("role_walk");
				cgMove * pkMove = new cgMove(-fSpeed, 0.0f);
				pkMove->SetName("role_walk");
				m_spRole->StartAction(pkMove);
				m_spRole->SetCurAnimation(cgActorAction_Walk);
			}else if (wParam == VK_RIGHT)
			{
				m_spRole->SetDirection(cgRight);
				m_spRole->StopAction("role_walk");
				cgMove * pkMove = new cgMove(fSpeed, 0.0f);
				pkMove->SetName("role_walk");
				m_spRole->StartAction(pkMove);
				m_spRole->SetCurAnimation(cgActorAction_Walk);
			}else if (wParam == VK_UP)
			{
				m_spRole->SetDirection(cgBack);
				m_spRole->StopAction("role_walk");
				cgMove * pkMove = new cgMove(0.0f, -fSpeed);
				pkMove->SetName("role_walk");
				m_spRole->StartAction(pkMove);
				
				m_spRole->SetCurAnimation(cgActorAction_Walk);
			}else if (wParam == VK_DOWN)
			{
				m_spRole->SetDirection(cgFront);

				m_spRole->StopAction("role_walk");
				cgMove * pkMove = new cgMove(0.0f, fSpeed);
				pkMove->SetName("role_walk");
				m_spRole->StartAction(pkMove);

				m_spRole->SetCurAnimation(cgActorAction_Walk);
			}else if (wParam == VK_SPACE)
			{
			//	cgSpiritActionSequence * pkSequence = new cgSpiritActionSequence;
			//	pkSequence->AddAction(new cgSpiritAction_ScaleTo(2.0f, 2.0f, 0.05f));
			//	pkSequence->AddAction(new cgSpiritAction_ScaleTo(1.0f, 1.0f, 0.1f));
			/*	if (!m_spRole->GetAction("main_jump"))
				{
					cgSpiritAction_Jump * pkMainJump = new cgSpiritAction_Jump(420.0f, 2000.0f);
					pkMainJump->SetName("main_jump");
					m_spRole->StartAction(pkMainJump);
				}*/
				

			//	cgScene::Get()->GetSceneRoot()->GetCamera()->SetAction(new cgSpiritAction_Shake(0.0f, 4.0f, 30.0f, 0.6f));
			}
		}else if (message == WM_KEYUP)
		{
			switch(wParam)
			{
			case VK_LEFT:
			case VK_RIGHT:
			case VK_UP:
			case VK_DOWN:
				m_spRole->StopAction("role_walk");
				m_spRole->SetCurAnimation(cgActorAction_Idle);
				break;
			}
		}else if (message == WM_MOUSEMOVE)
		{
		}
		else if (message == WM_LBUTTONDOWN)
		{
			float x = LOWORD(lParam);
			float y = HIWORD(lParam);

			cgSceneManager::Get()->GetSceneCamera()->ScreenToWorld(x, y);

			m_spRole->StopAction("role_walk");
			cgMoveTo * pkMove = new cgMoveTo(x, y, 1.0f);
			pkMove->SetName("role_walk");
			m_spRole->StartAction(pkMove);

			m_spRole->SetCurAnimation(cgActorAction_Walk);

			float vX = x-m_spRole->GetWorldPosition().x;
			float vY = y-m_spRole->GetWorldPosition().y;

			if (vX == 0.0f)
			{
				if (vY > 0)
				{
					m_spRole->SetDirection(cgFront);

				}else
				{
					m_spRole->SetDirection(cgBack);
				}
			}else
			{
				double arc = atan(vY/vX);
				if (vX < 0)
				{
					arc += cgMath::PI;
				}
				double arc8 = cgMath::PI/8;
				if (arc < arc8 && arc > -arc8)
				{
					m_spRole->SetDirection(cgRight);
				}else if (arc < arc8*3 && arc > arc8)
				{
					m_spRole->SetDirection(cgFrontRight);
				}else if (arc < arc8*5 && arc > arc8*3)
				{
					m_spRole->SetDirection(cgFront);
				}else if (arc < arc8*7 && arc > arc8*5)
				{
					m_spRole->SetDirection(cgFrontLeft);
				}else if (arc < arc8*9 && arc > arc8*7)
				{
					m_spRole->SetDirection(cgLeft);
				}else if (arc < arc8*11 && arc > arc8*9)
				{
					m_spRole->SetDirection(cgBackLeft);
				}else if (arc > arc8*11 || arc < arc8*-3)
				{
					m_spRole->SetDirection(cgBack);
				}else if (arc < arc8*-1 && arc > -arc8*3)
				{
					m_spRole->SetDirection(cgBackRight);
				}
			}
		}
		else if (message == WM_RBUTTONDOWN)
		{
			/*float x = LOWORD(lParam);
			float y = HIWORD(lParam);
			cgScene::Get()->GetSceneCamera()->ScreenToWorld(x, y);

			cgGameSpiritPtr spImage = new cgGameSprite(TEXT("./res/block6.bmp"));
			spImage->SetWorldPosition(int(x/64+0.5f)*64, int(y/64+0.5f)*64);
			spImage->SetScale(2, 2);
			cgScene::Get()->GetSceneRoot()->Add(&spImage);*/

		}
		else if (message == WM_MOUSEWHEEL)
		{
			if (!cgXIsKeyPressed(VK_CONTROL))
			{
				short delta = (short)(HIWORD(wParam));
				if (delta > 0)
				{
					cgSceneManager::Get()->GetSceneCamera()->LocalScale(cgSceneManager::Get()->GetSceneCamera()->GetLocalScale().x*0.1f,
						cgSceneManager::Get()->GetSceneCamera()->GetLocalScale().y*0.1f);
				}else
				{
					cgSceneManager::Get()->GetSceneCamera()->LocalScale(cgSceneManager::Get()->GetSceneCamera()->GetLocalScale().x*-0.1f,
						cgSceneManager::Get()->GetSceneCamera()->GetLocalScale().y*-0.1f);
				}
			}else
			{
				cgSceneManager::Get()->GetSceneCamera()->SetLocalScale(1.0f, 1.0f);
			}
			

			CheckLoadMap(cgSceneManager::Get()->GetSceneCamera()->GetWorldPosition().x,
				cgSceneManager::Get()->GetSceneCamera()->GetWorldPosition().y);
		}
		
	}
	// 框架：最后把消息交给框架，可选
	return false;
}

bool cgRunApp::OnGameMessage( cgGameMessage msg, void * pData, int nLen )
{
	switch (msg)
	{
	case cgGameMessage_GameAppInitialized:
		{
			//cgGameTaskManager::Get()->AddGameTask(new cgGameLogoTask);
			cgGameMessageListenerManager::Get()->DispatchGameMessage(cgGameMessage_LogoFinished);
		}break;
	case cgGameMessage_LogoFinished:
		{
		//	cgImageSpiritPtr spBack = new cgImageSpirit(TEXT("res/s5_p.png"));
		//	cgScene::Get()->GetSceneRoot()->Add(&spBack, -100000);
			m_spMap = new cgGameObject;
			m_spMap->SetName("cgRunMapNode");
			cgSceneManager::Get()->GetSceneRoot()->AttachChild(&m_spMap);
			m_spWorld = new cgGameObject();
			cgSceneManager::Get()->GetSceneRoot()->AttachChild(&m_spWorld);

			LoadRole();
			cgGameCameraPtr spCamera = cgSceneManager::Get()->GetSceneCamera();
			spCamera->SetWorldPosition(m_spRole->GetWorldPosition());
			CheckLoadMap(m_spRole->GetWorldPosition().x, m_spRole->GetWorldPosition().y);
		}break;
	}

	return true;
}

void cgRunApp::DoUpdateGame( float fDeltaTime )
{
	if (true && m_spRole)
	{
		if (m_spRole->GetWorldPosition().x < 0)
			m_spRole->SetWorldPosition(0.0f, m_spRole->GetWorldPosition().y);

		if (m_spRole->GetWorldPosition().y < 0)
			m_spRole->SetWorldPosition(m_spRole->GetWorldPosition().x, 0);

		cgGameCameraPtr spCamera = cgSceneManager::Get()->GetSceneCamera();
		spCamera->SetWorldPosition(m_spRole->GetWorldPosition());

		if (m_spRole->GetActionCount())
		{

			CheckLoadMap(m_spRole->GetWorldPosition().x,
				m_spRole->GetWorldPosition().y);
		}

	}
}


void cgRunApp::DoRenderGame()
{
}

cgActorPtr cgRunApp::LoadRole()
{
	cgGameObjectPtr spBack = new cgGameSprite(TEXT("res/s2_p.png"));
	spBack->Move(-300.0f, -100.0f);
	m_spWorld->AttachChild(&spBack);

	spBack = new cgGameSprite(TEXT("res/s3_p2.png"));
	
	m_spWorld->AttachChild(&spBack);

	spBack = new cgGameSprite(TEXT("res/s5_p.png"));
	spBack->Move(500.0f, 0);
	m_spWorld->AttachChild(&spBack);

	m_spRole = cgXLoadActor("res/role/boy3/actor.cga");
	m_spRole->SetName("boy3");
	m_spWorld->AttachChild(&m_spRole);
	m_spRole->SetCurAnimation(cgActorAction_Idle);
	m_spRole->SetDirection(cgFront);

	cgGameText * pkName = new cgGameText(TEXT("嗜魔邪道·仙"), 2, 0xff00cf00);
	pkName->SetSize(200, 20);
	pkName->SetName("cgRoleName");
	pkName->SetLocalPosition(0.0f, -50.0f);
	m_spRole->AttachChild( pkName);

	m_spRole->SetWorldPosition(10, 10);

	for (int i = 0; i < 4; i++)
	{
		static const char * paths[] =
		{
			"res/role/girl/actor.cga",
			"res/role/girl2/actor.cga",
			"res/role/boy/actor.cga",
			"res/role/boy3/actor.cga",
			"res/role/boy2/actor.cga",

		};
		int nValue = rand();
		cgActorPtr spOther = cgXLoadActor(paths[rand()%5]);
		spOther->SetName("girl");
		spOther->SetCurAnimation(rand()%2?cgActorAction_Walk:cgActorAction_Idle);
		spOther->SetDirection(static_cast<cgDirectionEnum>(rand()%4));
		spOther->SetWorldPosition(i%20*100, i/20*100);

		cgGameText * pkName = new cgGameText(TEXT("飞哥媳妇"), 2, 0xff00cf00);
		pkName->SetSize(200, 20);
		pkName->SetName("cgRoleName");
		pkName->SetLocalPosition(0.0f, -50.0f);
		spOther->AttachChild( pkName);

		m_spWorld->AttachChild(&spOther);

	}

	
	return NULL;
}

bool cgRunApp::CheckLoadLine(int x, int y)
{
	bool bLineVisible = false;

	int nWidth = 512;
	int nXOff = x;
	while ( CheckLoadRegion(nXOff, y))
	{
		nXOff += nWidth;
		bLineVisible = true;
	}
	nXOff = x-nWidth;
	while ( CheckLoadRegion(nXOff, y))
	{
		nXOff -= nWidth;
		bLineVisible = true;
	}

	return bLineVisible;
}
void cgRunApp::CheckLoadMap(int x, int y)
{
	CheckVisibleRegion();

	int nHeight = 512;
	int nYOff = y;

	while (CheckLoadLine(x, nYOff))
	{
		nYOff += nHeight;
	}

	nYOff = y-nHeight;
	while ( CheckLoadLine(x, nYOff))
	{
		nYOff -= nHeight;
	}
}

bool cgRunApp::CheckLoadRegion( int x, int y )
{
	if (x < 0 || y < 0)
		return false;

	int nRegionWith = 512;

	cgRectF kRect;
	kRect.x = x-x%nRegionWith;
	kRect.y = y-y%nRegionWith;
	kRect.w = nRegionWith;
	kRect.h = nRegionWith;

	cgRectF kCameraRect = cgSceneManager::Get()->GetSceneCamera()->GetViewRect();

	bool bVisible =cgXIsRectIntersect(kRect, kCameraRect);

	if (bVisible && !FindRegion(x, y) )
	{
		TCHAR szPath[MAX_PATH];
	/*	cgSprintf(szPath, MAX_PATH, TEXT("D:\\Work\\src\\Product\\Maps\\r任务地图\\b边界\\Terrain\\%d_%d.jpg"), kRect.y/nRegionWith, kRect.x/nRegionWith);*/
		cgSprintf(szPath, MAX_PATH, TEXT("F:\\软件备份\\dbl\\src\\Product\\Maps\\2轩辕区\\x轩辕\\Terrain\\%d_%d.jpg"), (int)(kRect.y)/nRegionWith, (int)(kRect.x)/nRegionWith);
		cgGameSpiritPtr spImage = new cgGameSprite(szPath);
//		spImage->SetName(cgStringTable::Get()->UnicodeToAcp(szPath));
		m_spMap->AttachChild(&spImage);
		spImage->SetWorldPosition(kRect.x+kRect.w/2, kRect.y+kRect.h/2);

		cgRunMapRegion kRegion;
		kRegion.idRegion = cgRunAppMakeRegionID(x, y);
		kRegion.spImage = spImage;
		kRegion.rectBound = kRect;
		m_kRegionList[kRegion.idRegion] = kRegion;
	}

	return bVisible;
}

void cgRunApp::CheckVisibleRegion()
{
	if (!m_spMap)
		return ;

	cgRectF kCameraRect = cgSceneManager::Get()->GetSceneCamera()->GetViewRect();

	cgSceneRegionList::iterator it = m_kRegionList.begin();
	while (it != m_kRegionList.end())
	{
		cgRunMapRegion & kRegion = it->second;
		if (!cgXIsRectIntersect(kCameraRect, kRegion.rectBound))
		{
			m_spMap->DetachChild(&kRegion.spImage);
			it = m_kRegionList.erase(it);
		}else
		{
			++it;
		}
	}
}

cgGameSpiritPtr cgRunApp::FindRegion( int x, int y )
{
	cgSceneRegionList::iterator it = m_kRegionList.find(cgRunAppMakeRegionID(x, y));
	if (it != m_kRegionList.end())
		return it->second.spImage;

	return NULL;
}

unsigned cgRunAppMakeRegionID( int x, int y )
{
	x /= 512;
	y /= 512;

	return (x<<16) | y;
}
