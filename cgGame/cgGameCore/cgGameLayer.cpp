#include "StdAfx.h"
#include "cgGameLayer.h"

cgGameLayer::cgGameLayer(void)
{
	m_pkCamera = (cgGameCamera*)AttachChild(new cgGameCamera);
}

cgGameLayer::cgGameLayer( const string &strName ):cgGameObject(strName)
{
	m_pkCamera = (cgGameCamera*)AttachChild(new cgGameCamera);
}

cgGameLayer::~cgGameLayer(void)
{
}

void cgGameLayer::Render()
{
	cgCamera * pkOld = cgCamera::SetRenderCamera(m_pkCamera);
// -----------------------------------------------------------------------
	cgGameObject::Render();
// -----------------------------------------------------------------------
	cgCamera::SetRenderCamera(pkOld);
}

cgGameObject* cgGameLayer::Pick( float pointX, float pointY, bool bScreenPoint )
{
	// 如果是屏幕坐标，则用当前相机转换成世界坐标，否则不转换
	if (bScreenPoint)
		m_pkCamera->ScreenToWorld(pointX, pointY);

	return cgGameObject::Pick(pointX, pointY, false);
}

cgGameCamera * cgGameLayer::GetCamera()
{
	return m_pkCamera;
}
