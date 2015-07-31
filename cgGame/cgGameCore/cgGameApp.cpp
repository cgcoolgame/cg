#include "StdAfx.h"
#include "cgGameApp.h"
#include "cgRender.h"
#include "cgSoundPlayer.h"
#include "cgIDImageManager.h"
#include "cgSrcImageManager.h"
#include "cgSoundManager.h"
#include "cgGameCommand.h"
#include "cgGameCommandManager.h"
#include "cgGameTaskManager.h"
#include "cgGameMessageListenerManager.h"
#include "cgSceneManager.h"
#include "cgCursorManager.h"
#include "cgGameUIManager.h"
#include "cgGameObjectRoot.h"

// ---------------------------------------------------------------------------

cgGameApp::cgGameApp(void)
{
	m_fFrameBeginTime = 0.0f;
	m_fLastFrameBeginTime = 0.0f;
	m_fFrameDeltaTime = 0.0f;
	m_fTimeScale = 1.0f;

	m_nMaxFPS = DEFAULT_GAME_MAX_FPS;
	m_nCurFPS = 0;
	m_bShowFPS = true;

	m_bIsInitialized = false;
}

cgGameApp::~cgGameApp(void)
{
	// 反序销毁
	cgGameUIManager::Destroy();
	cgSceneManager::Destroy();
	cgGameObjectRoot::Destroy();
	// 反序销毁
	cgGameMessageListenerManager::Destroy();
	cgGameTaskManager::Destroy();
	cgGameCommandManager::Destroy();
	cgSoundManager::Destroy();
	cgIDImageManager::Destroy();
	cgSrcImageManager::Destroy();
	cgSoundPlayer::Destroy();
	cgRender::Destroy();
}


// ----------------------------------------------------------------------------------
bool cgGameApp::Initialize( int nWidth, int nHeight, int nStyle, int nStyleEx )
{
	// 初始化父类
	if (!cgWinApp::Initialize(nWidth, nHeight, nStyle, nStyleEx))
		return false;

	// 加载render
	if (!cgRender::Create()->Initialize(GetHwnd(), nWidth, nHeight))
		return false;
	
	// 加载声音播放器
	if (!cgSoundPlayer::Create()->Initialize())
		return false;

	// 资源图片管理器
	if (!cgSrcImageManager::Create()->Initialize())
		return false;

	// id资源管理器
	if (!cgIDImageManager::Create()->Initialize())
		return false;

	// 声音管理器
	if (!cgSoundManager::Create()->Initialize())
		return false;

	// 游戏命令管理器
	if (!cgGameCommandManager::Create()->Initialize())
		return false;

	// 游戏任务管理器
	if (!cgGameTaskManager::Create()->Initialize())
		return false;

	// 游戏内部消息分发管理器
	if (!cgGameMessageListenerManager::Create()->Initialize())
		return false;

	if (!cgCursorManager::Create()->Initialize())
		return false;

	if (!cgGameObjectRoot::Create()->Initialize())
		return false;

	if (!cgSceneManager::Create()->Initialize())
		return false;

	if (!cgGameUIManager::Create()->Initialize())
		return false;

	if (!DoInitGame())
		return false;

	m_bIsInitialized = true;

	return m_bIsInitialized;
}

bool cgGameApp::DoInitGame()
{
	return true;
}


bool cgGameApp::OnSizeChanged()
{
	if (cgRender::Get())
		cgRender::Get()->Resize(GetWidth(), GetHeight());

	return true;
}

// ------------------------------------------------------------------------------------
bool cgGameApp::OnRawMessage(UINT message, WPARAM wParam, LPARAM lParam )
{
	if (!m_bIsInitialized)
		return false;

	if (cgCursorManager::Get()->OnMessage(message, wParam, lParam))
		return true;

	if (cgGameUIManager::Get()->OnMessage(message, wParam, lParam))
		return true;

	if (DoProcessRawMessage(message, wParam, lParam))
		return true;

#ifdef _DEBUG
	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_PRIOR)
		{
			// 加速
			SetTimeScale(GetTimeScale()+0.1f);
		}else if (wParam == VK_NEXT)
		{
			// 减速
			SetTimeScale(GetTimeScale()-0.1f);
		}
	}else if (message == WM_KEYUP)
	{
		if (wParam == VK_HOME)
		{
			ShowFPS(!m_bShowFPS);
		}
	}
#endif

	return cgWinApp::OnRawMessage(message, wParam, lParam);
}


bool cgGameApp::DoProcessRawMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
	return false;
}

void cgGameApp::OnIdle()
{
	m_fLastFrameBeginTime = m_fFrameBeginTime;
	m_fFrameBeginTime = cgTime::GetTime();
	m_fFrameDeltaTime = m_fFrameBeginTime-m_fLastFrameBeginTime;

	// 更新
	Update(m_fFrameDeltaTime*m_fTimeScale);

	// 渲染
	Render();

	// 锁定fps
	LockFPS();
}

// ----------------------------------------------------------------------------

void cgGameApp::Update( float fDeltaTime )
{
	cgSoundPlayer::Get()->Update(fDeltaTime);
	cgSrcImageManager::Get()->Update(fDeltaTime);
	cgGameTaskManager::Get()->Update(fDeltaTime);
	cgGameMessageListenerManager::Get()->Update(fDeltaTime);

	// gameobject相关
	cgGameObjectRoot::Get()->Update(fDeltaTime);
	cgSceneManager::Get()->Update(fDeltaTime);
	cgGameUIManager::Get()->Update(fDeltaTime);

	// 更新游戏
	DoUpdateGame(fDeltaTime);
}


void cgGameApp::DoUpdateGame( float fDeltaTime )
{

}

// ----------------------------------------------------------------------------

void cgGameApp::Render()
{
	cgRender * pkRender = cgRender::Get();

	pkRender->ClearBack(0x00000000);
	pkRender->BeginRender();

	cgGameObjectRoot::Get()->Render();

	DoRenderGame();

	DrawFPS();

	pkRender->EndRender();
	pkRender->Present();
}

void cgGameApp::DoRenderGame()
{
}

// ------------------------------------------------------

void cgGameApp::LockFPS()
{
	if (m_nMaxFPS <= 0)
		return ;

	float fDeltalTime = cgTime::GetTime()-m_fFrameBeginTime;
	float fTimePerFrame = (float)(1.0/m_nMaxFPS);

	if (fDeltalTime < fTimePerFrame )
	{
		int nTimeInMS =  (int)((fTimePerFrame-fDeltalTime)*1000);
		Sleep( nTimeInMS );

		m_nCurFPS = m_nMaxFPS;
	}else
	{
		m_nCurFPS = (int)(1.0/fDeltalTime);
	}
}

void cgGameApp::DrawFPS()
{
	if (m_bShowFPS)
	{
#ifdef _DEBUG

		TCHAR szText[CG_LONG_LONG_TEXT_BUFF_LEN];
		cgSprintf(szText, CG_LONG_LONG_TEXT_BUFF_LEN, 
			TEXT("FPS:%d \n TimeScale: x %.2f \n AppTime:%.2f \n TotalRefObject:%d"),
			m_nCurFPS, GetTimeScale(), GetFrameBeginTime(), cgRefObject::GetTotalObjectNum());
	//	cgRender::Get()->FillRect(cgRect(200, 0, 400, 20), 0x4f000000);
		cgRender::Get()->RenderString(szText, cgStrLen(szText), 
			cgRectF(0, 0, 200, 200), 2, 5, 0xff008f00, DT_LEFT);
#else
		static TCHAR szChar[CG_SHORT_TEXT_BUFF_LEN];
		cgSprintf(szChar, CG_SHORT_TEXT_BUFF_LEN, TEXT("FPS: %d"), m_nCurFPS);
		//	cgRender::Get()->FillRect(cgRect(0, 0, 200, 20), 0xff000000);
		cgRender::Get()->RenderString(szChar, cgStrLen(szChar), 0, 0, 2, 0xff008f00);
#endif
	}
}

void cgGameApp::SetMaxFPS( int nFPS )
{
	m_nMaxFPS = nFPS;
}

int cgGameApp::GetMaxFPS()
{
	return m_nMaxFPS;
}

int cgGameApp::GetCurFPS()
{
	return m_nCurFPS;
}

void cgGameApp::ShowFPS( bool bShow )
{
	m_bShowFPS = bShow;
}


bool cgGameApp::IsShowFPS()
{
	return m_bShowFPS;
}

// ---------------------------------------------------------

float cgGameApp::GetFrameBeginTime()
{
	return m_fFrameBeginTime;
}

float cgGameApp::GetLastFrameBeginTime()
{
	return m_fLastFrameBeginTime;
}

float cgGameApp::GetDeltaTime()
{
	return m_fFrameDeltaTime;
}

void cgGameApp::SetTimeScale( float fAccelerate )
{
	m_fTimeScale = fAccelerate;
}

float cgGameApp::GetTimeScale()
{
	return m_fTimeScale;
}

// --------------------------------------------------------------------------

cgGameApp * cgGameApp::GetGameApp()
{
	return (cgGameApp*)cgWinApp::GetApp();
}

// --------------------------------------------------------------------------





