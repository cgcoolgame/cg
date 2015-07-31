#include "StdAfx.h"
#include "cgGameObjectRoot.h"


cgGameObjectRoot::cgGameObjectRoot(void)
{
}


cgGameObjectRoot::~cgGameObjectRoot(void)
{
	cgGameObject::ClearAll();
}

bool cgGameObjectRoot::Initialize()
{
	cgGameObject::Root();
	return true;
}

void cgGameObjectRoot::Update( float deltaTime )
{
	cgGameObject::Root()->Update(deltaTime);
}

void cgGameObjectRoot::Render()
{
	cgGameObject::Root()->Render();
}

cgGameLayerPtr cgGameObjectRoot::CreateLayer( const string & strLayer, float depth )
{
	cgGameLayerPtr spLayer = (cgGameLayer*)cgGameObject::Root()->AttachChild(new cgGameLayer(strLayer));
	spLayer->SetDepth(depth);
	return spLayer;
}

cgGameLayerPtr cgGameObjectRoot::GetLayer( const string & strLayer )
{
	return (cgGameLayer*)cgGameObject::Root()->FindObject(strLayer);
}

bool cgGameObjectRoot::OnRawMessage( UINT msg, WPARAM wParam, LPARAM lParam )
{
	return false;
}

