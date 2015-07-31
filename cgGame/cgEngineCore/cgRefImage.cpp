#include "StdAfx.h"
#include "cgRefImage.h"

cgRefImage::cgRefImage( const cgImagePtr &spParent, const cgRectF &kClipRect ):m_spParentImage(spParent)
{
	m_kClipRect = kClipRect;
}

cgRefImage::~cgRefImage()
{
}

void cgRefImage::Draw(const cgRectF & kSrcRect,const cgRectF & kDestRect,
	cgColor color )
{
	m_spParentImage->Draw(cgRectF( kSrcRect.x+m_kClipRect.x, kSrcRect.y+m_kClipRect.y, kSrcRect.w, kSrcRect.h),
		kDestRect, color);
}

float cgRefImage::GetWidth()const
{
	return m_kClipRect.w;
}

float cgRefImage::GetHeight()const
{
	return m_kClipRect.h;
}

bool cgRefImage::PointToFinalTextureCoordinate( float x, float y, float &u, float &v)
{
	return m_spParentImage->PointToFinalTextureCoordinate(x+m_kClipRect.x, y+m_kClipRect.y, u, v);
}

cgID cgRefImage::GetTextureID()
{
	return m_spParentImage->GetTextureID();
}
