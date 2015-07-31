#include "StdAfx.h"
#include "cgUIManager.h"
#include "cgUIRender.h"
#include "cgEngineTools.h"
#include "cgMath.h"

// ---------------------------------------------------------------------------------

#ifdef _DEBUG
//#define _DEBUG_LOG_CGUIMANAGER_
#endif

cgUIManager::cgUIManager()
{
	m_hWnd = NULL;
	m_bInEditMode = false;

	m_pkUILoader = NULL;
}


cgUIManager::~cgUIManager(void)
{
	m_spFocusComponent = NULL;
	m_spMouseComponent = NULL;
	m_spRoot = NULL;
}

bool cgUIManager::Initialize( cgHwnd hWnd, int nWidth, int nHeight )
{
	// render必须在这之前初始化
	if (!cgUIRender::GetRender())
		return false;

	m_hWnd = hWnd;
	
	m_kBound.Set(0.0f, 0.0f, nWidth, nHeight);

	CalcClientToWinOff();
	CalcUIToWinOff();
	// 创建root
	m_spRoot = new cgUIWidget;
	m_spRoot->SetName("root");
	m_spRoot->SetRect(0, 0, nWidth, nHeight);
	m_spRoot->SetStatic(true);

	// 第一次重绘所有UI
	SetDirty();

	return true;
}

// -----------------------------------------------------------------------------------------------
bool cgUIManager::OnMessage( cgUIMsg msg, unsigned wparam, unsigned lparam )
{
	int x = LOWORD(lparam);
	int y = HIWORD(lparam);

	ClientPointToUI(x, y);
	switch (msg)
	{
	case WM_MOUSEMOVE:
		{
			if (m_spFocusComponent
				&& m_spFocusComponent->IsClickDown()
				&& m_spFocusComponent->OnMessage(msg, wparam, lparam))
			{
				return true;
			}

			cgUIWidgetPtr spMouseComponent = m_spRoot->Pick(x, y);
			if (spMouseComponent != m_spMouseComponent)
			{
				if (m_spMouseComponent)
					m_spMouseComponent->OnMessage(cgUIMsg_MouseOut, wparam, lparam);

				m_spMouseComponent = spMouseComponent;

				if (m_spMouseComponent && m_spMouseComponent->IsEnable())
					m_spMouseComponent->OnMessage(cgUIMsg_MouseIn, wparam, lparam);
			}

			if (spMouseComponent)
				return spMouseComponent->OnMessage(msg, wparam, lparam);

		}break;
	case WM_LBUTTONDOWN:
		{
			cgUIWidgetPtr spMouseComponent = m_spRoot->Pick(x, y);
			if (spMouseComponent != m_spFocusComponent)
			{
				if (m_spFocusComponent)
					m_spFocusComponent->OnMessage(cgUIMsg_LostFocus, wparam, lparam);

				m_spFocusComponent = NULL;

				if (spMouseComponent && spMouseComponent->IsEnable())
				{
					m_spFocusComponent = spMouseComponent;
					m_spFocusComponent->OnMessage(cgUIMsg_GainFocus, wparam, lparam);
				}

			}
			if (spMouseComponent && spMouseComponent->IsEnable())
				return spMouseComponent->OnMessage(WM_LBUTTONDOWN, wparam, lparam);

		}break;

	case WM_LBUTTONDBLCLK:
		{
			if (m_spFocusComponent && m_spFocusComponent->IsEnable())
				return m_spFocusComponent->OnMessage(WM_LBUTTONDBLCLK, wparam, lparam);

		}break;
	case WM_LBUTTONUP:
		{
			if (m_spFocusComponent && m_spFocusComponent->IsClickDown())
				return m_spFocusComponent->OnMessage(WM_LBUTTONUP, wparam, lparam);

			cgUIWidgetPtr spMouseComponent = m_spRoot->Pick(x, y);
			if (spMouseComponent)
				return spMouseComponent->OnMessage(WM_LBUTTONUP, wparam, lparam);

		}break;
	case WM_KEYDOWN:
		{
#ifdef _DEBUG
			if (m_spMouseComponent && m_bInEditMode)
			{
				int nOff = 1;
				if (::GetKeyState(VK_CONTROL) < 0)
					nOff = 50;

				switch (wparam)
				{
				case VK_LEFT:
					{
						m_spMouseComponent->Move(-nOff, 0);
					}break;
				case VK_RIGHT:
					{
						m_spMouseComponent->Move(nOff, 0);
					}break;

				case VK_UP:
					{
						m_spMouseComponent->Move(0, -nOff);
					}break;
				case VK_DOWN:
					{
						m_spMouseComponent->Move(0, nOff);
					}break;
				}

				string path;
				m_spMouseComponent->GetPath(path);
				cout<<path.c_str()<<":\n("
					<<m_spMouseComponent->GetX()<<","
					<<m_spMouseComponent->GetY()<<","
					<<m_spMouseComponent->GetWidth()<<","
					<<m_spMouseComponent->GetHeight()<<")"
					<<endl;

			}
#endif
			if (!ParseShortCut(wparam, lparam) && m_spFocusComponent)
			{
				return m_spFocusComponent->OnMessage(WM_KEYDOWN, wparam, lparam);
			}

		}break;
	case WM_CHAR:
		{
			if (m_spFocusComponent)
			{
				return m_spFocusComponent->OnMessage(WM_CHAR, wparam, lparam);
			}
		}break;
	default:
		return m_spRoot->OnMessage(msg, wparam, lparam);
	}

	return false;
}

bool cgUIManager::ParseShortCut( unsigned wparam, unsigned lparam )
{
	if ( GetKeyState(VK_CONTROL) < 0)
	{
		switch (wparam)
		{
		case 'C':
			{
				if (m_spFocusComponent)
					return m_spFocusComponent->OnMessage(cgUIMsg_Copy, wparam, lparam);
			}break;
		case 'V':
			{
				if (m_spFocusComponent)
					return m_spFocusComponent->OnMessage(cgUIMsg_Paste, wparam, lparam);
			}break;
		case 'X':
			{
				if (m_spFocusComponent)
					return m_spFocusComponent->OnMessage(cgUIMsg_Cut, wparam, lparam);
			}break;
#ifdef _DEBUG
		case '2':
			{
				m_bInEditMode = !m_bInEditMode;
				SetDirty();
			}break;
#endif
		default:
			break;
		}
	}

	return false;
}

void cgUIManager::OnUIEvent( cgUIWidgetPtr spComponent, cgUIEvent enmEvent, unsigned wparam, unsigned lparam )
{
#ifdef _DEBUG_LOG_CGUIMANAGER_
	string path;
	spComponent->GetPath(path);
	cout<<path.c_str()<<" : "<<cgUIEventName[enmEvent]<<endl;

#endif

	cgUIEventListenerList::iterator it = m_kUIEventListnerList.begin();
	for (; it != m_kUIEventListnerList.end(); ++it)
	{
		cgUIEventListenerEx * pkListener = *it;
		if (pkListener)
			pkListener->OnUIEvent(spComponent, enmEvent, wparam, lparam);
	}
}


void cgUIManager::AddUIEventListener( cgUIEventListenerEx * pkListener )
{
	m_kUIEventListnerList.push_back(pkListener);
}


bool cgUIManager::DelUIEventListener( cgUIEventListenerEx * pkListener )
{
	cgUIEventListenerList::iterator it = m_kUIEventListnerList.begin();
	for (; it != m_kUIEventListnerList.end(); ++it)
	{
		if (*it == pkListener)
		{
			it = m_kUIEventListnerList.erase(it);
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------
void cgUIManager::CalcClientToWinOff()
{
	RECT kWinRectInScreen;
	GetWindowRect(m_hWnd, &kWinRectInScreen);

	POINT kClientOrgionInScreen = {0, 0};
	ClientToScreen(m_hWnd, &kClientOrgionInScreen);

	m_kClientToWinOff.x = kClientOrgionInScreen.x-kWinRectInScreen.left;
	m_kClientToWinOff.y = kClientOrgionInScreen.y-kWinRectInScreen.top;
}

void cgUIManager::CalcUIToWinOff()
{
	RECT kWinRectInScreen;
	GetWindowRect(m_hWnd, &kWinRectInScreen);

	POINT kClientOrgionInScreen = {0, 0};
	ClientToScreen(m_hWnd, &kClientOrgionInScreen);

	m_kUIToWinOff.x = kClientOrgionInScreen.x-kWinRectInScreen.left;
	m_kUIToWinOff.y = kClientOrgionInScreen.y-kWinRectInScreen.top;
}

void cgUIManager::ClientPointToUI( int & x, int & y )
{
	x += m_kClientToWinOff.x-m_kUIToWinOff.x;
	y += m_kClientToWinOff.y-m_kUIToWinOff.y;
}

void cgUIManager::UIPointToClient( int & x, int & y )
{
	x -= m_kClientToWinOff.x-m_kUIToWinOff.x;
	y -= m_kClientToWinOff.y-m_kUIToWinOff.y;
}

void cgUIManager::UIPointToScreen( int & x, int & y )
{
	RECT rect;
	::GetWindowRect(m_hWnd, &rect);
	x += rect.left+m_kUIToWinOff.x;
	y += rect.top+m_kUIToWinOff.y;

}
// -----------------------------------------------------------------------------------

void cgUIManager::Render(bool bDisplayWhileNoDirty /*= true*/)
{
	assert(cgUIRender::GetRender());

	bool bDirty = IsDirty();
	if (bDirty)
	{
		cgUIRender::GetRender()->BeginRender();
		// -------------------------------
		cgDirtyRectList::iterator it = m_kDirtyRectList.begin();
		for (; it != m_kDirtyRectList.end(); ++it)
		{
			cgRectF& dirtyRect = *it;

			if (cgUIRender::GetRender()->PushClipRect(dirtyRect))
			{
				cgUIRender::GetRender()->ClearRect(dirtyRect);
				m_spRoot->Render(dirtyRect);

				cgUIRender::GetRender()->PopClipRect();
			}
		}
		m_kDirtyRectList.clear();
		// -------------------------------
		cgUIRender::GetRender()->EndRender();
	}

	if (bDirty || bDisplayWhileNoDirty)
		cgUIRender::GetRender()->Display();
}

// -------------------------------------------------------------------------------------

void cgUIManager::Update( float fTime )
{
	assert(m_spRoot);
	m_spRoot->Update(fTime);
}

// -------------------------------------------------------------------------------------

bool cgUIManager::IsInEditMode()
{
	return m_bInEditMode;
}

// -----------------------------------------------------------------------------------
bool cgUIManager::AddDirtyRect( const cgRectF& rect )
{
	bool bNeedAdd = true;
	cgDirtyRectList::iterator it = m_kDirtyRectList.begin();
	while (it != m_kDirtyRectList.end())
	{
		cgRectF & old = *it;
		cgRectCmpResult enmResult = cgXCompareRect(rect, old);

		if (enmResult == cgRectCmpResult_Equal 
			|| enmResult == cgRectCmpResult_BeContained)
		{
			// 如果新矩形被包含，则不放入
			bNeedAdd = false;
			break;
		}else if (enmResult == cgRectCmpResult_Contain)
		{
			// 如果新矩形包含了旧矩形，则删掉旧矩形
			it = m_kDirtyRectList.erase(it);
		}else
		{
			++it;
		}
	}

	if (bNeedAdd)
	{
		cgRectF finalRect;
		if (cgXGetIntersectRect(rect, m_kBound, finalRect))
			m_kDirtyRectList.push_back(finalRect);
		else
			bNeedAdd = false;
	}

	return bNeedAdd;
}

unsigned cgUIManager::GetDirtyRectNum()
{
	return m_kDirtyRectList.size();
}

bool cgUIManager::IsDirty()
{
	return GetDirtyRectNum()>0;
}

void cgUIManager::SetDirty()
{
	AddDirtyRect(m_kBound);
}
// -----------------------------------------------------------------------------------

void cgUIManager::SetUILoader( cgUILoader * pkLoader )
{
	m_pkUILoader = pkLoader;
}

// 切换屏幕
bool cgUIManager::GotoScreen( const char * pcScreen )
{
	// 先删除旧的screen
	if (m_spCurrentScreen)
	{
		m_spCurrentScreen->SetVisible(false);
		m_spCurrentScreen = NULL;
	}

	// 先找下这一屏是否已经加载过了
	m_spCurrentScreen = m_spRoot->FindChild(pcScreen);

	// 如果没加载过，则加载新的screen
	if (!m_spCurrentScreen && m_pkUILoader)
	{
		m_spCurrentScreen =  m_pkUILoader->LoadScreen(pcScreen);
		if (m_spCurrentScreen)
			m_spRoot->AddChild(m_spCurrentScreen);
	}

	if (m_spCurrentScreen)
	{
		m_spCurrentScreen->SetVisible(true);
		OnUIEvent(m_spCurrentScreen, cgUIEvent_OnScreenChanged, NULL, NULL);
	}

	return m_spCurrentScreen ;
}

cgUIWidgetPtr cgUIManager::GetCurrentScreen()
{
	return m_spCurrentScreen;
}

cgUIWidgetPtr cgUIManager::FindComponent( const char * pcID, bool bLoadDynamic /*= false*/ )
{
	cgUIWidgetPtr spFind = m_spRoot->FindComponent(pcID);
	if (!spFind && bLoadDynamic && m_pkUILoader)
	{
		spFind = m_pkUILoader->LoadDynamic(pcID);
		if (spFind && m_spCurrentScreen)
		{
			m_spCurrentScreen->AddChild(spFind);
		}
	}

	return spFind;
}


// -----------------------------------------------------------------------------------
