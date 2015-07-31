#include "StdAfx.h"
#include "cgSceneManager.h"
#include "cgGameObjectRoot.h"


cgSceneManager::cgSceneManager(void)
{
	m_spSceneRoot = NULL;
	m_spSceneCamera = NULL;
}


cgSceneManager::~cgSceneManager(void)
{
}

bool cgSceneManager::Initialize()
{
	m_spSceneRoot = cgGameObjectRoot::Get()->CreateLayer("Scene", cgGameObjectDepth_Scene_Layer);
	m_spSceneCamera = m_spSceneRoot->GetCamera();

	return true;
}

void cgSceneManager::Update( float deltaTime )
{
	
}

bool cgSceneManager::OnMessage( UINT msg, WPARAM wParam, LPARAM lParam )
{
	return false;
}

cgGameLayerPtr cgSceneManager::GetSceneRoot()
{
	return m_spSceneRoot;
}

cgGameCameraPtr cgSceneManager::GetSceneCamera()
{
	return m_spSceneCamera;
}

void cgSceneManager::ScreenToScene( cgVector& v )
{
	m_spSceneCamera->ScreenToWorld(v);
}

void cgSceneManager::SceneToScreen( cgVector& v )
{
	m_spSceneCamera->WorldToScreen(v);
}
