#include "StdAfx.h"
#include "cgUIImage.h"
#include "cgUIRender.h"


cgUIImage::cgUIImage( LPCTSTR path )
{
	m_id = cgUIRender::GetRender()->LoadImage(path);
	cgSize size = cgUIRender::GetRender()->GetImageSize(m_id);
	m_nWidth = size.w;
	m_nHeight = size.h;
}

cgUIImage::cgUIImage( cgID srcID )
{
	m_id = cgUIRender::GetRender()->LoadImage(srcID);
	cgSize size = cgUIRender::GetRender()->GetImageSize(m_id);
	m_nWidth = size.w;
	m_nHeight = size.h;
}


cgUIImage::~cgUIImage(void)
{
	cgUIRender::GetRender()->ReleaseImage(m_id);
}

cgID cgUIImage::GetID()
{
	return m_id;
}

int cgUIImage::GetWidth()
{
	return m_nWidth;
}

int cgUIImage::GetHeight()
{
	return m_nHeight;
}

void cgUIImage::Draw( const cgRectF & srcRect, const cgRectF & destRect )
{
	cgUIRender::GetRender()->DrawImage(m_id, srcRect, destRect);
}

void cgUIImage::DrawToRect( const cgRectF & destRect )
{
	cgUIRender::GetRender()->DrawImage(m_id, 
		cgRectF(0, 0, m_nWidth, m_nHeight), destRect);
}

void cgUIImage::DrawToPoint( int x, int y )
{
	cgUIRender::GetRender()->DrawImage(m_id, 
		cgRectF(0, 0, m_nWidth, m_nHeight), 
		cgRectF(x, y, m_nWidth, m_nHeight));
}
