#include "StdAfx.h"
#include "cgRenderImage.h"
#include "cgRender.h"

cgRenderImage::cgRenderImage( LPCTSTR path )
{
	m_idTex = cgRender::Get()->LoadTexture(path);
	if (m_idTex != CG_INVALID_ID)
	{
		cgSize size = cgRender::Get()->GetTextureSize(m_idTex);
		m_fWidth = static_cast<float>(size.w);
		m_fHeight = static_cast<float>(size.h);
	}
}

cgRenderImage::cgRenderImage( int w, int h )
{
	m_idTex = cgRender::Get()->CreateTexture(w, h);
	m_fWidth = static_cast<float>(w);
	m_fHeight = static_cast<float>(h);
}

cgRenderImage::~cgRenderImage()
{
	cgRender::Get()->ReleaseTexture(m_idTex);
}

cgID cgRenderImage::GetTextureID()
{
	return m_idTex;
}

float cgRenderImage::GetWidth() const
{
	return m_fWidth;
}

float cgRenderImage::GetHeight() const
{
	return m_fHeight;
}

void cgRenderImage::Draw( const cgRectF & srcRect,const cgRectF & destRect, cgColor color )
{
	cgRender::Get()->RenderTexture(m_idTex, srcRect, destRect, color);
}

bool cgRenderImage::PointToFinalTextureCoordinate( float x, float y, float &u, float &v )
{
	u = 0.0f;
	v = 0.0f;

	if (GetWidth() <= 0.0f || GetHeight() <= 0.0f)
		return false;

	u = x/GetWidth();
	v = y/GetHeight();

	return true;
}
