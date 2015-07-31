#include "StdAfx.h"
#include "cgGameCamera.h"
#include "cgGameApp.h"
#include <cgEngineTools.h>


cgGameCamera::cgGameCamera(void)
{
	m_strName = "cgGameCamera";
}

cgGameCamera::cgGameCamera( const string & strName ):cgGameObject(strName)
{

}


cgGameCamera::~cgGameCamera(void)
{
}

cgVector cgGameCamera::GetViewCenter()
{
	return GetWorldPosition();
}

cgVector cgGameCamera::GetViewScale()
{
	return GetWorldScale();
}

cgSizeF cgGameCamera::GetViewSize()
{
	return cgSizeF(GetAppWidth()/GetWorldScale().x,
		GetAppHeight()/GetWorldScale().y);
}


cgRectF cgGameCamera::GetViewRect()
{
	cgSizeF viewSize = GetViewSize();
	cgRectF viewRect(GetWorldPosition().x-viewSize.w/2, GetWorldPosition().y-viewSize.h/2, viewSize.w, viewSize.h);
	return viewRect;
}


bool cgGameCamera::IsBoundInView( const cgRectF& bound )
{
	cgSizeF viewSize = GetViewSize();
	cgRectF viewRect(GetWorldPosition().x-viewSize.w/2, GetWorldPosition().y-viewSize.h/2, viewSize.w, viewSize.h);

	return cgXIsRectIntersect(viewRect, bound);
}


void cgGameCamera::ScreenToWorld( cgVector& v )
{
	ScreenToWorld(v.x, v.y);
}

void cgGameCamera::ScreenToWorld( float & x, float & y )
{
	x = GetWorldPosition().x + (x-GetAppWidth()/2.0f)/GetWorldScale().x;
	y = GetWorldPosition().y + (y-GetAppHeight()/2.0f)/GetWorldScale().y;
}

void cgGameCamera::WorldToScreen( cgVector& v )
{
	WorldToScreen(v.x, v.y);
}

void cgGameCamera::WorldToScreen( float & x, float & y )
{
	x = (x - GetWorldPosition().x)*GetWorldScale().x + GetAppWidth()/2.0f;
	y = (y- GetWorldPosition().y)*GetWorldScale().y + GetAppHeight()/2.0f;
}




