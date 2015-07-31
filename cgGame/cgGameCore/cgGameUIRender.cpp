#include "StdAfx.h"
#include "cgGameUIRender.h"
#include "cgSrcImageManager.h"
#include "cgIDImageManager.h"
#include "cgImage.h"
#include "cgRender.h"
#include <cgEngineTools.h>


cgGameUIRender::cgGameUIRender(void)
{
	m_hWnd = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	m_pkImageStorage = NULL;
}


cgGameUIRender::~cgGameUIRender(void)
{
	delete m_pkImageStorage;
}

bool cgGameUIRender::Initialize( cgHwnd hWnd, int w, int h )
{
	if (!cgUIRender::Initialize(hWnd, w, h))
		return false;

	m_spBkImage = cgImage::CreateImage(w, h);

	m_pkImageStorage = new cgImageStorage(1000);

	cgRender::Get()->GetViewPort(m_kCurClipRect);

	return true;
}

bool cgGameUIRender::OnSizeChanged( int w, int h )
{
	m_nWidth = w;
	m_nHeight = h;

	m_spBkImage = cgImage::CreateImage(w, h);
	cgRender::Get()->GetViewPort(m_kCurClipRect);

	return true;
}

cgID cgGameUIRender::LoadImage( LPCTSTR path )
{
	cgImagePtr ptr = cgSrcImageManager::Get()->LoadImage(path);
	if (ptr)
	{
		// 加一次引用计数
		// 非典型用法，很矬，以后纠正 todo
		ptr->IncreaseRef();
		return m_pkImageStorage->Add(&ptr);
	}

	return CG_INVALID_ID;
}
cgID cgGameUIRender::LoadImage( cgID resID )
{
	cgImagePtr ptr = cgIDImageManager::Get()->GetImage(resID);
	if (ptr)
	{
		ptr->IncreaseRef();
		return m_pkImageStorage->Add(&ptr);
	}

	return CG_INVALID_ID;
}

bool cgGameUIRender::ReleaseImage( cgID image )
{
	cgImage * pkImage = m_pkImageStorage->Remove(image);
	if (pkImage)
	{
		pkImage->DecreaseRef();
		return true;
	}
	return false;
}

cgSize cgGameUIRender::GetImageSize( cgID image )
{
	cgImage * pkImage = m_pkImageStorage->Find(image);
	if (pkImage)
	{
		return cgSize(pkImage->GetWidth(), pkImage->GetHeight());
	}

	return cgSize();
}

void cgGameUIRender::DrawImage( cgID image, const cgRectF& srcRect, const cgRectF & destRect )
{
	cgImage * pkImage = m_pkImageStorage->Find(image);
	if (pkImage)
		pkImage->Draw(srcRect, destRect);
}

void cgGameUIRender::DrawLine( const cgPoint& from, const cgPoint& to, cgColor color )
{
	cgRender::Get()->RenderLine(from, to, color);
}

void cgGameUIRender::DrawBox( const cgRectF& rect, cgColor color )
{
	cgRender::Get()->DrawBox(rect, color);
}

void cgGameUIRender::FillRect( const cgRectF& rect, cgColor color )
{
	cgRender::Get()->FillRect(rect, color);
}

void cgGameUIRender::DrawUIText( LPCTSTR lpctText, int nTextLen, 
	const cgRectF& rect, cgID font, int space , cgColor color, int style )
{
	cgRender::Get()->RenderString(lpctText, nTextLen, rect, font, space, color, style);
}

void cgGameUIRender::DrawUIText( LPCTSTR lpctText, int nTextLen, int x, int y, cgID font, cgColor color )
{
	cgRender::Get()->RenderString(lpctText, nTextLen, x, y, font, color);
}


bool cgGameUIRender::PushClipRect( const cgRectF& clipRect )
{
	cgRectF finalRect;
	if (cgXGetIntersectRect(m_kCurClipRect, clipRect, finalRect))
	{
		cgRender::Get()->SetViewPort(finalRect);
		m_kClipRectStack.push(m_kCurClipRect);
		m_kCurClipRect = finalRect;
		return true;
	}

	return false;
}

void cgGameUIRender::PopClipRect()
{
	cgRectF clipRect = m_kClipRectStack.top();
	m_kClipRectStack.pop();
	cgRender::Get()->SetViewPort(clipRect);
	m_kCurClipRect = clipRect;
}

void cgGameUIRender::ClearRect( const cgRectF& rect )
{
	cgRender::Get()->ClearRect(rect);
}

void cgGameUIRender::BeginRender()
{
	cgRender::Get()->PushRenderTarget(m_spBkImage->GetTextureID());
}

void cgGameUIRender::EndRender()
{
	cgRender::Get()->PopRenderTarget();
}

void cgGameUIRender::Display()
{
	m_spBkImage->DrawToPoint(0, 0);
}

cgUISurface * cgGameUIRender::CreateUISurface( int w, int h, int nOpertion /*= 0*/ )
{
	cgRenderSurface * pkSurface = cgRender::Get()->CreateRenderSurface(w, h, nOpertion);
	
	if (!pkSurface)
		return NULL;

	return new cgGameUISurface(pkSurface);
}

bool cgGameUIRender::PresentUISurface( cgUISurface * pkSurface, const cgRectF& srcRect, const cgRectF& destRect )
{
	cgRenderSurface * pkRenderSurface = ((cgGameUISurface*)pkSurface)->GetRenderSurface();
	return cgRender::Get()->PresentRenderSurface(pkRenderSurface,srcRect, destRect);
}

int cgGameUIRender::GetUICharWidth( TCHAR ch, cgID idFont )
{
	return cgRender::Get()->GetRenderCharWidth(ch, idFont);
}

cgSizeF cgGameUIRender::GetUICharSize( TCHAR ch, cgID idFont )
{
	return cgRender::Get()->GetRenderCharSize(ch, idFont);
}


// ----------------------------------------------------------------------------------------------

cgGameUISurface::cgGameUISurface( cgRenderSurface * pkSurface )
{
	m_pkSurface = pkSurface;
}

cgGameUISurface::~cgGameUISurface()
{
	delete m_pkSurface;
}

void * cgGameUISurface::GetContent()
{
	if (m_pkSurface)
		return m_pkSurface->GetContent();

	return NULL;
}

bool cgGameUISurface::ReleaseContent( void * pContent )
{
	if (m_pkSurface)
		return m_pkSurface->ReleaseContent(pContent);

	return false;
}

int cgGameUISurface::GetType()
{
	return 0;
}

cgRenderSurface * cgGameUISurface::GetRenderSurface()
{
	return m_pkSurface;
}
