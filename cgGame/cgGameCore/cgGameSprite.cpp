#include "StdAfx.h"
#include "cgGameSprite.h"
#include "cgImageTools.h"
#include "cgSrcImageManager.h"
#include "cgGameCamera.h"
#include "cgRender.h"
#include "cgEngineTools.h"
#include <cgMath.h>


cgGameSprite::cgGameSprite(void)
{
	m_strName = "cgGameSprite";
}


cgGameSprite::cgGameSprite( const string& strName ):cgGameObject(strName)
{

}


cgGameSprite::cgGameSprite( const cgString& strPath )
{
	SetImage(cgSrcImageManager::Get()->LoadImage(strPath.c_str()));
	
	if (m_spImage)
		SetSize(m_spImage->GetWidth(), m_spImage->GetHeight());
}

cgGameSprite::cgGameSprite( cgImagePtr spImage )
{
	SetImage(spImage);

	if (m_spImage)
		SetSize(m_spImage->GetWidth(), m_spImage->GetHeight());
}

void cgGameSprite::SetImage( cgImagePtr spImage )
{
	m_spImage = spImage;
}

void cgGameSprite::SetImage( const cgString& strPath )
{
	SetImage(cgSrcImageManager::Get()->LoadImage(strPath.c_str()));
}

void cgGameSprite::DoRenderSelf(cgCamera * renderCamera)
{
	if (!m_spImage)
		return ;

	cgVector center = GetWorldPosition();
	renderCamera->WorldToScreen(center);

	cgRectF bound;
	if (renderCamera->IsBoundInView(GetBound(bound)))
	{
		m_spImage->DrawEx(center.x,center.y, 
			bound.w*renderCamera->GetViewScale().x,
			bound.h*renderCamera->GetViewScale().y, 
			GetRenderColor(), GetWorldRotation());
	}
}



