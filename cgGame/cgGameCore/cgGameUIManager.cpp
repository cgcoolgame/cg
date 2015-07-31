#include "StdAfx.h"
#include "cgGameUIManager.h"
#include "cgGameObjectRoot.h"


cgGameUIManager::cgGameUIManager(void)
{
}


cgGameUIManager::~cgGameUIManager(void)
{
}

bool cgGameUIManager::Initialize()
{
	m_spUIRoot = cgGameObjectRoot::Get()->CreateLayer("UI", cgGameObjectDepth_UI_Layer);
	m_spUICamera = m_spUIRoot->GetCamera();
	return true;
}


bool cgGameUIManager::OnMessage( UINT msg, WPARAM wParam, LPARAM lParam )
{
	float x = LOWORD(lParam);
	float y = HIWORD(lParam);

	switch(msg)
	{
	case WM_MOUSEMOVE:
		{
			cgGameObjectPtr spPick = m_spUIRoot->Pick(x, y, true);
			if (spPick != m_spPick)
			{
				if (m_spPick)
					m_spPick->SendEvent(cgGameObjectEvent_MouseOut, wParam, lParam);

				m_spPick = spPick;

				if (m_spPick)
					m_spPick->SendEvent(cgGameObjectEvent_MouseEnter, wParam, lParam);
			}

			if (m_spPick)
				return m_spPick->SendEvent(cgGameObjectEvent_MouseMove, wParam, lParam);
			
		}break;
	case WM_LBUTTONDOWN:
		{
			cgGameObjectPtr spFocus = m_spUIRoot->Pick(x, y, true);
			if (spFocus != m_spFocus)
			{
				if (m_spFocus)
					m_spFocus->SendEvent(cgGameObjectEvent_LostFocus, wParam, lParam);
				
				m_spFocus = spFocus;

				if (m_spFocus)
					m_spFocus->SendEvent(cgGameObjectEvent_GainFocus, wParam, lParam);
			}

			if (m_spFocus)
				return m_spFocus->SendEvent(cgGameObjectEvent_MouseDown, wParam, lParam);

		}break;
	case WM_LBUTTONUP:
		{
			if (m_spPick)
				return m_spPick->SendEvent(cgGameObjectEvent_MouseUp, wParam, lParam);
		}break;
	case WM_MOUSEWHEEL:
		{
			if (m_spPick)
				return m_spPick->SendEvent(cgGameObjectEvent_MouseWheel, wParam, lParam);
		}break;
	case WM_LBUTTONDBLCLK:
		{
			if (m_spFocus)
				return m_spFocus->SendEvent(cgGameObjectEvent_DBClick, wParam, lParam);
		}break;
	case WM_CHAR:
		{
			if (m_spFocus)
				return m_spFocus->SendEvent(cgGameObjectEvent_InputChar, wParam, lParam);
		}break;

	default:
		break;
	}
	return false;
}

void cgGameUIManager::Update( float deltaTime )
{

}

cgGameLayerPtr cgGameUIManager::GetUIRoot()
{
	return m_spUIRoot;
}

cgGameCameraPtr cgGameUIManager::GetUICamera()
{
	return m_spUICamera;
}

void cgGameUIManager::ScreenToUI( cgVector& v )
{
	m_spUICamera->ScreenToWorld(v);
}

void cgGameUIManager::UIToScreen( cgVector& v )
{
	m_spUICamera->WorldToScreen(v);
}
